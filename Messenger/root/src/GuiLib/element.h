#pragma once

#include<QObject>





class Element : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString login READ login WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int id READ id  NOTIFY idChanged)

public:
    explicit Element(QObject *parent = 0);


    QString color() const;
    void setColor(QString color);
    QString login() const;
    void setText(QString login);
    int id() const;

signals:
    void colorChanged(QString color);
    void textChanged(QString login);
    void idChanged();

private:
    QString m_color;
    QString m_text;
    int m_id;

};


