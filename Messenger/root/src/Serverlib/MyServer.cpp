#include "stdafx.h"
#include "MyServer.h"

#include"parsedata.h"

// ----------------------------------------------------------------------
MyServer::MyServer(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt), m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);
    // захват порта сервера nPort (2323) поиск коннектов если ошибки то закрываем сервер
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + m_ptcpServer->errorString()
                             );
        m_ptcpServer->close();
        return;
    }
    //соединяем слот slotNewConnection() с входящим сигналом newConnection()
    connect(m_ptcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotNewConnection())
           );
    // отображаем информацию о подключении
    //создаем запись и даем возможность только читать из файла
    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true);

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
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


    sendToClient(pClientSocket, ParseData::concatenation1(Connection,"Server Response: Connected!"));
}

// ----------------------------------------------------------------------
void MyServer::slotReadClient()
{
    //преобразование указателя sender к типу QTcpSocket.
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    //цикл обработки частей блоков информации передаваемой и принимаемой по сети
    for (;;)
    {
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
        QString strMessage = time.toString() + " " + "Client has sent - " + str;

        switch ((ParseData::variable(str)).toInt()) {

        case Message:

        m_ptxt->append("MESSAGE");

        break;

        case Registration:

        m_ptxt->append("Registration");
        m_ptxt->append("Server sent-> "+ParseData::concatenationRespond(Registration,true));

        sendToClient(pClientSocket,ParseData::concatenationRespond(Registration,true));

            break;

        case Authorization:
        m_ptxt->append("Authorization");
        break;

        default:
            break;
        }


        //добавляем в виджет strMessage
        m_ptxt->append(strMessage);
        //обнуляем размер блока что бы проводить запись следующего блока
        m_nNextBlockSize = 0;

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
