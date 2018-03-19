#pragma once

#include <QObject>
#include <QQmlListProperty>

class Element;


namespace Gui {



class MyListModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Element> data READ data NOTIFY dataChanged)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    MyListModel(QObject *parent = 0);

    MyListModel(const MyListModel& obj);
    MyListModel& operator=(const MyListModel& obj);

    QQmlListProperty<Element> data();

     void add( Element* elem);

     void slotGetFriend();

signals:
    void dataChanged();

private:
    static void appendData(QQmlListProperty<Element> *list, Element *value);
    static int countData(QQmlListProperty<Element> *list);
    static Element *atData(QQmlListProperty<Element> *list, int index);
    static void clearData(QQmlListProperty<Element> *list);

    QList<Element*> m_data;
};

}
