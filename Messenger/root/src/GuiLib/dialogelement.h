#pragma once

#include<QObject>
#include<QQmlListProperty>

namespace Gui {



    class DialogElement: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
        Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
        Q_PROPERTY(int idFile READ idFile WRITE setIdFile NOTIFY idFileChanged)
        Q_PROPERTY(QString stateMess READ stateMessage WRITE setStateMessage NOTIFY stateMessageChanged)
        Q_PROPERTY(bool flag READ flag WRITE setFlag NOTIFY flagChanged)

    public:
        explicit DialogElement(QObject *parent );


        QString time() const;
        QString message() const;
        int idFile() const;
        QString stateMessage() const;
        bool flag() const;

        void setMessage(const QString& mess);
        void setIdFile(const int& idFile);
        void setTime(const QString& time);
        void setStateMessage(const QString& stateMess);
        void setFlag(const bool& flag);


        static void appendData(QQmlListProperty<DialogElement> *list, DialogElement *value);
        static int countData(QQmlListProperty<DialogElement> *list);
        static DialogElement* atData(QQmlListProperty<DialogElement> *list, int index);
        static void clearData(QQmlListProperty<DialogElement> *list);




    signals:
        void timeChanged(const QString& time);
        void messageChanged(const QString& mess);
        void idFileChanged(const int& idFile);
        void stateMessageChanged(const QString& stateMess);
        void flagChanged(const bool& flag);

    private:
        QString m_time;
        QString m_message;
        int m_idFile;
        QString m_stateMess;
        bool m_flag;
    };

}
