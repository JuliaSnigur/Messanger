#pragma once

#include <QVector>
#include <QHash>
#include <QDebug>

#include "DBLib/user.h"



namespace Data {

enum request {Error, Connection, Registration, Authorization, Message, File, GetListOfFriends,GetID, GetFriend};

enum stateMessage {Send, Get};

/*
   static QString variable(QString& str);
   static QHash<int,QString> separateHash(QString& str);
   static QString concatenationHash(const QHash<int,QString>& hash);
*/

static QString concatinationVecUser(const QVector<User*>& vec)
{
    QString str;

    for(int i = 0; i<vec.size();i++)
    {
         str += QString::number(vec[i]->getID()) + ' ' + vec[i]->getLogin() + ' ' + ' ' + QString::number(vec[i]->getStatus()) +' ';
    }

    return str;
}

static QVector<User*> separateVecUser( QString& str)
{
    QVector<User*> vec;
    QString resID;
    QString resLogin;
    QString resStatus;
    int i = 0;

      for(; i<str.size();)
      {
          resID="";
          while(i<str.size() && str[i] != ' ')
          {
              resID += str[i];
              ++i;
          }
          while(i<str.size() && str[i] == ' ')
            ++i;
          resLogin="";
          while(i<str.size() && str[i] != ' ')
          {
              resLogin += str[i];
              ++i;
          }
          while(i<str.size() && str[i] == ' ')
            ++i;
          resStatus="";
          while(i<str.size() && str[i] != ' ')
          {
              resStatus += str[i];
              ++i;
          }
          while(i<str.size() && str[i] == ' ')
            ++i;
          vec.push_back(new User(resID.toInt(), resLogin, resStatus.toInt()));
      }
      return vec;
}

  static QString variable(QString& str)
   {
       QString res;
       QString st;
       int i=0;

       while(i<str.size() && str[i]!=' ')
       {
           res+=str[i];
           i++;
       }
        if(str[i]==' ')
            i++;

       for(;i<str.size();i++)
           st+=str[i];

       str=st;

       return res;
   }



  static QString concatenationHash(const QHash<int,QString>& hash)
   {
     QString str;

     QHash<int,QString>::const_iterator iter=hash.begin();

       while(iter != hash.end())
       {
          str += QString::number(iter.key()) + ' ' + iter.value() + ' ';
          ++iter;
       }

     return str;
   }


  static QHash<int,QString> separateHash(QString& str)
   {
     QHash<int,QString> hash;

       QString resID,resLogin;
       int i = 0;
       for(; i<str.size(); i++)
       {
           resID="";
           while(i<str.size() && str[i] != ' ')
           {
               resID += str[i];
               ++i;
           }
           ++i;
           resLogin="";
           while(i<str.size() && str[i] != ' ')
           {
               resLogin += str[i];
               ++i;
           }
           hash.insert(resID.toInt(),resLogin);
       }

       return hash;
   }



}
