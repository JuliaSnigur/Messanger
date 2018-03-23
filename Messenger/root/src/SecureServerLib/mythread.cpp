#include "stdafx.h"

#include "mythread.h"
#include "data.h"
#include "cryptographicpassword.h"

 Server::MyThread::MyThread(qintptr ID,   std::shared_ptr<DB::DBServerPresenter> db,  std::shared_ptr<QHash<int,QSslSocket*>> hash, QObject *parent)
    : QThread(parent)
    , m_mutexDB()
    , m_mutexHashTab()
    , m_sslClient(nullptr)
    , m_file(nullptr)
    , m_sizeReceiveFile(0)
    , m_db(nullptr)
    , m_hash(nullptr)

{
    this->m_socketDescriptor = ID;
    m_db = db;
    m_hash = hash;
    m_certServer = "-----BEGIN CERTIFICATE-----"
            "MIID2zCCAsOgAwIBAgIJALw0xDUVwv68MA0GCSqGSIb3DQEBBQUAMIGDMQswCQYD"
            "VQQGEwJGUjEPMA0GA1UECAwGRnJhbmNlMQ8wDQYDVQQKDAZHdWlUZUsxHTAbBgNV"
            "BAsMFFF0LVNzbFNlcnZlci1FeGFtcGxlMRIwEAYDVQQDDAkxMjcuMC4wLjExHzAd"
            "BgkqhkiG9w0BCQEWEGFkbWluQGd1aXRlay5uZXQwHhcNMTQwODE2MTY1MjU1WhcN"
            "MjQwODEzMTY1MjU1WjCBgzELMAkGA1UEBhMCRlIxDzANBgNVBAgMBkZyYW5jZTEP"
            "MA0GA1UECgwGR3VpVGVLMR0wGwYDVQQLDBRRdC1Tc2xTZXJ2ZXItRXhhbXBsZTES"
            "MBAGA1UEAwwJMTI3LjAuMC4xMR8wHQYJKoZIhvcNAQkBFhBhZG1pbkBndWl0ZWsu"
            "bmV0MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtZ1MV1GwNcL+c6zz"
            "8n/kII9sZZGUPXo3zj20wDd9SK51vWDhgXK9QTsKF7FSZIV4C2AMVb7za5GEn/c5"
            "ZWOvEavUR5AovHgFau2E/J3UOg/ys/fa4vWeOQWwCZvkjV3ikpYjFzS7lXoMxqj2"
            "/GkPV+x0zqBJdElJ7dVnI5FQWurVDofYrY/SDzC7x5DTpdeNf9nwxUGL7l7Zqzum"
            "cVQpxlOHHjXwVXcHOyt0ifrkFq6Ghmhz6hok+pxBnQ8Np+91ZqD9ePFh+aDeONjx"
            "776srmVAZEXq7737yxjwIbOnvDKhAe/isQ6uLO93XbLfMSqCQB8e6FotZW2vcDWH"
            "HCF7cQIDAQABo1AwTjAdBgNVHQ4EFgQU1UpcmMVlTsRSXkjPOvxdSdJ6P8EwHwYD"
            "VR0jBBgwFoAU1UpcmMVlTsRSXkjPOvxdSdJ6P8EwDAYDVR0TBAUwAwEB/zANBgkq"
            "hkiG9w0BAQUFAAOCAQEABXl/seUVFqrVIo8o4aIC19SnQVgEwKaRLetxBVyFY1Jg"
            "GOadUayRf4mK3lAQFKghGQYNeI33SWM8lNnAILJiJTGRKrodXQuEFbjFD4CF/vTg"
            "WtjS7BQR3KscLjlDwgK5tw+jvYmCVcBJwV6uM+NyeZOdz8QEi7h7vD9dqpp53xB7"
            "PNyHHBLEyUGCTiKV/TbeoQFrdQWQ+LXczNaBUX2imtPDixikaqr4mHRX7YTpH2WB"
            "VQNvID9efhMtDnTotI3puNwqRLXK8LEB6mbj27lPik1Mx7r81zvDAkkd+D/9oNF2"
            "7BppFrbxPgUCg6RV2MXinG1Njt6z25dV2AQUZro9vA=="
            "-----END CERTIFICATE-----";
    m_certClient = "-----BEGIN CERTIFICATE REQUEST-----"
            "MIICojCCAYoCAQAwXTELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUx"
            "ITAfBgNVBAoMGEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDEWMBQGA1UEAwwNMTky"
            "LjE2OC4wLjEwMjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAOC5D8Ie"
            "WCQ6RCY8BqLM6ta0ypFCwU9QVSZ4OYR8NFvW5QIX4B7TMMj1TdXi8Gl7jgwjpSgx"
            "ppS8uv9EDJ+qOZdXppkUEUQURqcHieWja5ROad5wsQpjciuMgknc0IyT5wsoqAjL"
            "VyEqCTEgzBURp1ToaaqTVD7bGpnRUuU227qf+wXg2leyJisjKqDltddzGSY+QD10"
            "e/CgY6ejDumPwjKDAiOAroNo9bDHKGqzrJ+LCVXx7GEiiSeqq/QyUc4saV6ONIJu"
            "oRM63Gs35bPnJPbi3euy4FJRsAPmxXYE8m3vHhrRjtWYwUDe9zBJFAon/yCgm6yX"
            "fwPFtUHzGIxypC8CAwEAAaAAMA0GCSqGSIb3DQEBCwUAA4IBAQCy1cc10LUFFc9o"
            "Py3wr2b+nT5GWVVZrYnikqoF7gbijzj7lxqNbnGjEvyZwdpwPV7g7I9ipBVvBHxu"
            "fzdqLdFNA455l43upEAWXjGU0muXsyFT+iypTm2Qy7eN/GUfthDSQsJiKPzrIc6h"
            "y3jZp/geRzWkoimstUxW2tJZDC0sdQPNKRnddDlsE5xqCEdIX1iyBOlv2a6gB+MV"
            "Q7Cfh/pZftID562OGbmnRRdoXCkvCtmqqiIZomm6jNpDiZ7JLBsx5Of2b97jEtRp"
            "+Xw+3l71J0cMXBsgYKPV/TdHWanS6TSjYbPwQ+m+3K4+bKnmHtibO5XtzppCBkFA"
            "gJ0gRAns"
            "-----END CERTIFICATE REQUEST-----";
    m_serverKey = "-----BEGIN PRIVATE KEY-----"
            "MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQC1nUxXUbA1wv5z"
            "rPPyf+Qgj2xlkZQ9ejfOPbTAN31IrnW9YOGBcr1BOwoXsVJkhXgLYAxVvvNrkYSf"
            "9zllY68Rq9RHkCi8eAVq7YT8ndQ6D/Kz99ri9Z45BbAJm+SNXeKSliMXNLuVegzG"
            "qPb8aQ9X7HTOoEl0SUnt1WcjkVBa6tUOh9itj9IPMLvHkNOl141/2fDFQYvuXtmr"
            "O6ZxVCnGU4ceNfBVdwc7K3SJ+uQWroaGaHPqGiT6nEGdDw2n73VmoP148WH5oN44"
            "2PHvvqyuZUBkRervvfvLGPAhs6e8MqEB7+KxDq4s73ddst8xKoJAHx7oWi1lba9w"
            "NYccIXtxAgMBAAECggEAdyb1MBCrEAqXkGL3RbE8hVQzpMuHO3JU7J21WarOKoIz"
            "QwUtzhTuL77BV1wCF2stoCDq1tLJt1gocB7t7CQjdu+J/U2KPGRuAYJFjsspstJF"
            "xGcnl2HX5cdigFtj7o+bF9siuJXjQCVr/mZabK2s4F2FIQ8uQfnXZA9vdHlhA9QU"
            "3QBhPMq90Y9hrBTb/eSN93yxc7554czxSplR2D0tFGtYVFjvjaUkROIAYXzjSv6a"
            "3/u9b05CrQHkb8RaN5GWfiBFqQP20sJHvn+FqNlYe/3EaLCnBVUhKrLA3+I7o8xL"
            "P2Kk728Qff/EHvBmLnxxnzUDrA2HOMUeCPyhbhFmAQKBgQDdiI8aFReeGNrDNEiX"
            "A+29dUiF65N7uuWUdFb80+3F0flGj3Ar0xyQJOZvxRwsYX1hs7VasRXbgXhuEh4f"
            "3D6dOVKEq1eMajtkV3ZL8U2IW81oUP8mxzVCLnoDrzhfu1SkAWyjvPuUmJ1LiQFd"
            "yQNPkswgrXOEst628X6FDeuj4QKBgQDR3s7z4ESOIFnw3Lz/mDMCwyiwRrPJhs47"
            "Zi/4iVXOks6lg5DR9KJppJcRW85JQGyzlpRR/7ZVKLwsFE4N0nq6oqpS89PERAT0"
            "UVvcKpD5tWKAKcafQZHBD6gZ47ljpzOllrTdJGiNAFpf/qdFH8848VBhSm13M29F"
            "9GPLNb7JkQKBgQCMQSz4gmoVef7mn29lzOLzlBF6WA9jwowfVRjNsQ9Usv9zINUP"
            "qfTnfbU3BkA0CPTsqm4jIQKJmoq4hVf1K+eoeuY3gJNJHujDOmx24CsKLbT6Wm1w"
            "C6c4Y1x0gLbcRSntO8mgUMGm7oiHjhIDYoRqGLKL7cS5OtWuVW6YppuNgQKBgQCL"
            "muYZrkaMMJMDuSJz939/R+jqEa4I0YagVqJ0do7AwkF6MmGEeHINSjI/ls1LRvLI"
            "J9N0FGDqlxVNURh281s2iXw5f/6PYRvWlcRAWYRkxzbFwIRibdCSF2MgDa7FznR5"
            "ox2euVhe6ywzDQeh4L4Mx+FLRqI4l9teMmqrw42tMQKBgQDbRFQFc0l8Pl/QnpS2"
            "IpCPqqTjD09K56V5hK9naEWlXRwX30i/cECz7W2q0DJB2SsjN7q58DpjuOjdiYvD"
            "EYKnRAehS39kAw0o1byn6KkYWPM3Nktjvz6piTkqeHSKrjba/Qbe/E58QoLYrqPT"
            "DKFdnoWRZ7T9mhny4HKKKCi4Vg=="
            "-----END PRIVATE KEY-----";
}

void  Server::MyThread::run()
{
    qDebug() << " Thread started";
    m_sslClient = std::shared_ptr<QSslSocket>(new QSslSocket());
    if(!m_sslClient->setSocketDescriptor(this->m_socketDescriptor))
    {
        qDebug()<<"Error with descriptor";
        emit error(m_sslClient->error());
        return;
    }
   /* QSslCertificate certSever(m_certServer.toLatin1());
    QSslCertificate certClient(m_certClient.toLatin1());
    QSslKey key(m_serverKey.toLatin1(), QSsl::Rsa, QSsl::Pem);

    m_sslClient->addCaCertificate(certClient);// certificates client
    m_sslClient->setLocalCertificate("../secure/sslserver.pem");// certificates server
    m_sslClient->setPrivateKey("../secure/sslserver.key",QSsl::Rsa, QSsl::Pem);
    m_sslClient->setProtocol(QSsl::TlsV1_2);
    m_sslClient->startServerEncryption();
*/
    QFile certificateFile("../../secure/client.crt");
    if (!certificateFile.open(QIODevice::ReadOnly))
      return;
    QSslCertificate cert(certificateFile.readAll());
    certificateFile.close();
    m_sslClient->addCaCertificate(cert);
    m_sslClient->setLocalCertificate("../../secure/sslserver.pem");
    m_sslClient->setPrivateKey("../../secure/sslserver.key",QSsl::Rsa, QSsl::Pem,"password");
    m_sslClient->setProtocol(QSsl::TlsV1_2);
    m_sslClient->startServerEncryption();

    connect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReadyRead, Qt::DirectConnection);
    connect(m_sslClient.get(), &QSslSocket::disconnected, this, &MyThread::slotDisconnect);
    connect(m_sslClient.get(), &QSslSocket::destroyed, this, &MyThread::slotDisconnect);
    //connect(m_sslClient.get(), &QSslSocket::sslErrors, this, &MyThread::slotError);
    sendToClient(m_sslClient.get(), QString::number(Data::Connection) + " Hello Client");
    exec();
}

bool  Server::MyThread::sendToClient(QSslSocket* pSocket, const QString& message)
{
    if (pSocket != nullptr)
    {
        qDebug()<<"Server sent-> "<< message;
        pSocket->write(message.toLocal8Bit());
        return true;
    }
    else
    {
        qDebug() << "Invalid socket ptr";
        return false;
    }
}




void  Server::MyThread::slotReadyRead()
{
    QString fileName;
    if(m_sslClient==nullptr)
    {
        qDebug()<<"Read: m_sslClient=nullptr";      
        return;
    }
    QString mess = m_sslClient->readAll();    // Read message
    qDebug() << "Client has sent -" << mess;
    switch ((Data::variable(mess)).toInt())
    {
    case Data::Error:
        qDebug()<<"Upss..";
        break;

    case Data::Message:
        qDebug()<<"MESSAGE\n";
        message(mess);
        break;

    case Data::Registration:
        qDebug()<<"Registration\n";
        registration(mess);
        break;

    case Data::Authorization:
        qDebug()<<"Authorization\n";
        authorization(mess);
        break;

    case Data::GetListOfFriends:
        qDebug()<<"GetNewList";
        sendList();
        break;

    case Data::File:
        qDebug()<<"SendFile";
        fileName = Data::variable(mess);
        m_sizeReceiveFile = Data::variable(mess).toULong();
        receiveFile(fileName);
        break;

    default:
        break;
    }

}

void  Server::MyThread::registration(QString& req)
{
    int id = 0;
    QString log = Data::variable(req);
    QString pass = Data::variable(req);

    // insert user into db
    qDebug() << "User: " << log << ", " << pass;

    m_mutexDB.lock();

    if(!m_db->insertUser(User(log, Server::encryptedPassword(pass), true)))
      {
        m_mutexDB.unlock();

        sendToClient(m_sslClient.get(), QString::number(Data::Error) + " The user's already existed with that login");
        return;
      }

     m_mutexDB.unlock();

     id = m_db->searchID(log);

    if(id == 0)
    {
        qDebug() << "The id doesn't exist";
    }
    else
    {
         m_mutexHashTab.lock();

         qDebug() << "ID: " << id;
         m_hash->insert(id, m_sslClient.get());

         m_mutexHashTab.unlock();

        sendToClient(m_sslClient.get(), QString::number(Data::Registration) + ' ' + QString::number(id));
    }
}

void  Server::MyThread::authorization(QString& req)
{
    QString log = Data::variable(req);
    QString pass = Data::variable(req);

    // search user into db
    qDebug() << "User: " << log << ", " << pass;

    User* us = m_db->searchUser(log);

    if(us == nullptr)
    {
        sendToClient(m_sslClient.get(), QString::number(Data::Error) + " The user didn't exist with that login");
        return;
    }

    if(us->getPassword() != Server::encryptedPassword(pass))
    {
         sendToClient(m_sslClient.get(), QString::number(Data::Error) + " The wrong password");
         return;
    }

    if(m_hash->contains(us->getID()))
    {
         sendToClient(m_sslClient.get(),QString::number(Data::Error) + " The account is already used");
         return;
    }
    // send message to client
    sendToClient(m_sslClient.get(), QString::number(Data::Authorization) + " " + QString::number(us->getID()));

   // std::unique_lock<QMutex> lock(m_mutexHashTab);
    m_mutexHashTab.lock();

    qDebug() << "ID: " << us->getID();
    m_hash->insert(us->getID(), m_sslClient.get());

    m_mutexHashTab.unlock();

    // update Status
    m_mutexDB.lock();
    if(!m_db->updateStatus(us->getID(),true))
    {
        qDebug()<<"The status doesn't update";
    }
    m_mutexDB.unlock();
}

void  Server::MyThread::sendList()
{
    QVector<User*> vec = m_db->getListOfUser();
    qDebug()<<"Vector: " + Data::concatinationVecUser(vec);
    sendToClient(m_sslClient.get(),QString::number(Data::GetListOfFriends)+' '+Data::concatinationVecUser(vec));
}

void  Server::MyThread::message(QString& str)
{
    int myID = Data::variable(str).toInt();
    int friendID = Data::variable(str).toInt();
    bool flag;

    qDebug()<<"myID="<<myID<<" friendID"<<friendID;

    flag = sendToClient((*m_hash)[friendID], QString::number(Data::Message) + ' ' + QString::number(myID) + ' ' +QString::number(0) + ' ' + str);

    if(!flag)
    {
        sendToClient((*m_hash)[myID], QString::number(Data::Error) + " The message doesn't send");
    }

}

void  Server::MyThread::receiveFile(const QString& fileName)
{
    m_file = std::shared_ptr<QFile>( new QFile(/*"Download/" + */fileName));
    m_file->open(QIODevice::WriteOnly|QIODevice::Append);
    sendToClient(m_sslClient.get(), QString::number(Data::File));
    disconnect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReadyRead);
    connect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReceiveFile);
}

void  Server::MyThread::slotReceiveFile()
{
    static quint64 sizeReceivedData;

       QByteArray buff =  m_sslClient->readAll();

       // char buff[1024] = "";
        //sizeReceivedData +=  m_sslClient->read(buff, 1024);
        if(m_file != nullptr)
        {
            // ошибка
            sizeReceivedData += m_file->write(buff);
            qDebug()<<"Write: " << sizeReceivedData ;
            buff.clear();
        }
        else
        {
            disconnect(m_sslClient.get(), SIGNAL(readyRead()), this, SLOT(slotReceiveFile()));
            connect(m_sslClient.get(), SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
            return;
        }
        if(sizeReceivedData == m_sizeReceiveFile)
        {
          m_file->close();
          m_file = nullptr;
          m_sizeReceiveFile = 0;
          sizeReceivedData = 0;
          qDebug() << "Finished";
          disconnect(m_sslClient.get(), SIGNAL(readyRead()), this, SLOT(slotReceiveFile()));
          connect(m_sslClient.get(), SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
       // сообщить клиента, что файл отпрален

        }
}

void  Server::MyThread::slotDisconnect()
{
   //std::unique_lock<QMutex> lockHash (m_mutexHashTab);

    QHash<int,QSslSocket*>::iterator iter=m_hash->begin();

    qDebug()<<"Disconnect: size of hash="<<m_hash->size();
        while(iter != m_hash->end())
        {
            if(iter.value() == m_sslClient.get())
            {
                qDebug()<<"Dissconect: id="<<iter.key();

                //std::unique_lock<QMutex> lockDB(m_mutexDB);
                m_mutexDB.lock();
                m_db->updateStatus(iter.key(),false);
                m_mutexDB.unlock();
                m_mutexHashTab.lock();
                m_hash->erase(iter);
                m_mutexHashTab.unlock();
                qDebug()<<" Size of hash="<<m_hash->size();
                break;
            }
             ++iter;
        }

     m_sslClient->disconnect();
     m_sslClient->deleteLater();

     iter=m_hash->begin();
     while(iter!=m_hash->end())
     {
         sendToClient(iter.value(), QString::number(Data::Error) + " You should refresh list of clients");
         ++iter;
     }

}
