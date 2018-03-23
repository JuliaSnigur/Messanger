#include "stdafx.h"
#include "data.h"

/*

QString Data::variable(QString& str)
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



QString Data::concatenationHash(const QHash<int,QString>& hash)
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


QHash<int,QString> Data::separateHash(QString& str)
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

*/

/*

QString Data::concatinationVecUser(const QVector<User>& vec)
{
    QString str;

    for(int i = 0; i<vec.size();i++)
    {
         str += QString::number(vec[i].getID()) + ' ' + vec[i].getLogin() + ' ' + ' ' + vec[i].getStatus();
    }

    return str;
}


QVector<User> Data::separateVecUser(const QString &res)
{
    QString str = res;
    QVector<User> vec;
    QString resID;
    QString resLogin;
    QString resStatus;
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
          ++i;
          resStatus="";
          while(i<str.size() && str[i] != ' ')
          {
              resStatus += str[i];
              ++i;
          }
          vec.push_back(User(resID.toInt(), resLogin, resStatus.toInt()));
      }
      return vec;
}
*/
