#pragma once

#include<QObject>

class Element : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(int idFile READ idFile WRITE setIdFile NOTIFY idFileChanged)
    Q_PROPERTY(QString stateMess READ stateMessage WRITE setStateMessage NOTIFY stateMessageChanged)

public:
    explicit Element(QObject *parent = 0);


    QString color() const;
    QString login() const;
    QString time() const;
    QString message() const;
    int idFile() const;
    QString stateMessage() const;

    void setColor(QString color);
    void setLogin(QString login);
    void setMessage(QString mess);
    void setIdFile(int idFile);
    void setTime(QString time);
    void setStateMessage(QString stateMess);


signals:
    void colorChanged(QString color);
    void loginChanged(QString login);
    void timeChanged(QString time);
    void messageChanged(QString mess);
    void idFileChanged(int idFile);
    void stateMessageChanged(QString stateMess);

private:
    QString m_color;
    QString m_login;
    QString m_time;
    QString m_message;
    int m_idFile;
    QString m_stateMess;

};


