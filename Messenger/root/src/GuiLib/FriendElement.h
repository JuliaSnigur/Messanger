#pragma once

#include<QObject>
#include<QQmlListProperty>

namespace Gui {

    class FriendElement : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)

    public:
        explicit FriendElement(QObject *parent = 0);

        QString login() const;
        void setLogin(const QString& login);


        static void appendData(QQmlListProperty<FriendElement> *list, FriendElement *value);
        static int countData(QQmlListProperty<FriendElement> *list);
        static FriendElement *atData(QQmlListProperty<FriendElement> *list, int index);
        static void clearData(QQmlListProperty<FriendElement> *list);

    signals:

         void loginChanged(const QString& login);

    private:

        QString m_login;
    };

}
