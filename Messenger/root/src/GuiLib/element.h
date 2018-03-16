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

public:
    explicit Element(QObject *parent = 0);


    QString color() const;
    QString login() const;
    QString time() const;
    QString message() const;
    int idFile() const;

    void setColor(QString color);
    void setLogin(QString login);
    void setMessage(QString mess);
    void setIdFile(int idFile);
    void setTime(QString time);


signals:
    void colorChanged(QString color);
    void loginChanged(QString login);
    void timeChanged(QString time);
    void messageChanged(QString mess);
    void idFileChanged(int idFile);

private:
    QString m_color;
    QString m_login;
    QString m_time;
    QString m_message;
    int m_idFile;

};


