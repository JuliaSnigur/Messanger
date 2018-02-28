#include "stdafx.h"
#include "MyServer.h"

// ----------------------------------------------------------------------
MyServer::MyServer(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt), m_nNextBlockSize(0)
{

    m_ptcpServer = new QTcpServer(this);
    // захват порта сервера nPort (27015) (для ssl порт на 1 больше) поиск коннектов если ошибки то закрываем сервер
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + m_ptcpServer->errorString()
                             );
        m_ptcpServer->close();
        return;
    }else {
            m_ptxt->append("Порт TCP прослушивается");
    }

    //соединяем слот slotNewConnection() с входящим сигналом newConnection()
    connect(m_ptcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotNewConnection())
           );
    // отображаем информацию о подключении
    //создаем запись и даем возможность только читать из файла
    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true);

    SSLServer = new SslServer(this);
    connect(SSLServer, SIGNAL(newConnection()), SLOT(acceptConnection()));
    //Задаем сертификат сервера и его закрытый ключ
    SSLServer->setSslLocalCertificate("sslserver.crt");
    SSLServer->setSslPrivateKey("sslserver.key");
    //Задаем версию TLS 2.1
    SSLServer->setSslProtocol(QSsl::TlsV1_2);
    //Запускаем прослушивание порта на +1 больше TCP
    bool listen = SSLServer->listen(QHostAddress::Any, (nPort+1));
    if (listen){
        m_ptxt->append("Порт SSL прослушивается");
    }else{SSLServer->close();}
    //Layout setup - настройки окна отображения !!!- View -!!!
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
    //connectDB();
}


//показать кто подключен
void MyServer::updateStatus(){
    QStringList List;
    if (SSLServer->isListening()){
        int count = ClientList.count();
        List << QString("Сервер запущен, подключено клиентов: %1").arg(count);
    }
    else List << "Сервер выключен";
    qDebug() << List.join("\n");
}
// Функция обработки входящих соединений
void MyServer::acceptConnection(){
    //Новый сокет
    sslConn = new QSslSocket(this);
    //TCP-соединение, на основе которого построится SSL-соединение
    QTcpSocket * temp = SSLServer->nextPendingConnection();
    //Текущая конфигурация
    QSslConfiguration config = sslConn->sslConfiguration();
        //Задаем протокол TLS 1.2
        config.setProtocol(QSsl::TlsV1_2);
    //Задаем новую конфигурацию
    sslConn->setSslConfiguration(config);
    //Новый SSL-сокет на основе созданного TCP-сокета
    sslConn = qobject_cast<QSslSocket*>(temp);
    //Десткиптор сокета
    int idusersocs = sslConn->socketDescriptor();

    //Добавляем полученный дескриптор и сокет в ассоциативный массив
    SClients[idusersocs] = sslConn;
    //Устанавливаем связь сигнала "получено сообщение" с функцией его обработки
    connect(SClients[idusersocs], SIGNAL(readyRead()), this, SLOT(readMessage()));
    //Если не удалось установить SSL-соединение, выходим из функции
    if (!sslConn){
        qDebug() << "Error: TCP connection\n";
        return;
    }
}
void MyServer::readMessage(){
    QSslSocket* clientSocket = (QSslSocket*)sender();
    int idusersocs = clientSocket->socketDescriptor();
    QByteArray message = clientSocket->readAll();
    qDebug() << message;
    int typeOfMess = getTypeOfMess(message, clientSocket);
    switch (typeOfMess){
    case 1:
        registerQuery(message);
        break;
    case 2:
        getMessage(message);
        break;
    case 3:
        loginQuery(message, clientSocket);
        break;
    case 4:
        addClient(message);
        break;
    case 5:
        addClientQuery(message, clientSocket);
        break;
    case 6:
        logOff(message, clientSocket);
    default:
        break;
    }
}




// ----------------------------------------------------------------------
/*virtual*/ void MyServer::slotNewConnection()
{
    //возврат сокета nextPendingConnection, посредством которого можно осуществлять дальнейшую связь с клиентом
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    //дисконектим пользователя
    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
           );
    //При поступлении запросов от клиентов
    //отправляется сигнал readyToRead ( ) , который мы соединяем со слотом slotReadClient().
    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
           );

    sendToClient(pClientSocket, "Server Response: Connected!");
}

// ----------------------------------------------------------------------
void MyServer::slotReadClient()
{
    //преобразование указателя sender к типу QTcpSocket.
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    //цикл обработки частей блоков информации передаваемой и принимаемой по сети
    for (;;) {
        if (!m_nNextBlockSize) { //в if проверяем размер блока не менее 2 байт и m_nNextBlockSize (размер блока) неизвестен

            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize; //считываем вносим данные
        }
        //если размер полученных данных менее размера блока данных то данные не записываем
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        //если размер данных для чтения равен или более размера блока
        //тогда данные считываются из потока в time и str
        QTime   time;
        QString str;
        in >> time >> str;
        // преобразуем time в строку и вместе с str записываем в strMessage
        QString strMessage =
            time.toString() + " " + "Client has sent - " + str;
        //добавляем в виджет strMessage
        m_ptxt->append(strMessage);
        //обнуляем размер блока что бы проводить запись следующего блока
        m_nNextBlockSize = 0;
        //передаем клиенту что нам удалось успешно прочитать данные
        sendToClient(pClientSocket,
                     "Server Response: Received \"" + str + "\""
                    );
    }
}

// ----------------------------------------------------------------------
void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str)
{ //формируем данные клиенту
    // поскольку размер файла должен быть выслан первым перед блоком информации то создаем arrBlock с значением ноль
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_3);
    //определяем значение первого бита в памяти текущего блока данных и начинаем записывать данные
    out << quint16(0) << QTime::currentTime() << str;
    //ищем созданное нами нулевое значение что бы определить начало блока (перенос указателя в начало блока)
    out.device()->seek(0);
    //вычисляем размер блока данных
    out << quint16(arrBlock.size() - sizeof(quint16));
    //записываем созданный блок
    pSocket->write(arrBlock);
}
