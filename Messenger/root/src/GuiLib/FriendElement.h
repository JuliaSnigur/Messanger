#pragma once

#include<QObject>
#include<QQmlListProperty>

namespace Gui {

    class FriendElement : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
        Q_PROPERTY(int id READ id WRITE setID NOTIFY idChanged)
        Q_PROPERTY(bool status READ status WRITE setStatus NOTIFY statusChanged)

    public:
         FriendElement(QObject *parent );
         FriendElement();


        QString login() const;
        void setLogin(const QString& login);
        int id() const;
        void setID(const int& id);
        bool status() const;
        void setStatus(const bool& id);


        static void appendData(QQmlListProperty<FriendElement> *list, FriendElement *value);
        static int countData(QQmlListProperty<FriendElement> *list);
        static FriendElement *atData(QQmlListProperty<FriendElement> *list, int index);
        static void clearData(QQmlListProperty<FriendElement> *list);

    signals:

         void loginChanged(const QString& login);
         void idChanged(const int& id);
         void statusChanged(const bool& status);

    private:

        QString m_login;
        int m_id;
        bool m_status;
    };

}
