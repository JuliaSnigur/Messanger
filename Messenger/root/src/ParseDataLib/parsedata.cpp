#include "stdafx.h"
#include "parsedata.h"

/*

QString StringHandlNamespace::variable(QString& str)
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


QVector<int> StringHandlNamespace::separateVec(QString& str)
{
    QVector<int> vec;
    QString res;
    int i=0;
    for(;i<str.size();i++)
    {
        res="";
        while(i<str.size() && str[i]!=' ')
        {
            res+=str[i];
            i++;
        }

        vec.push_back(res.toInt());
    }

    return vec;
}


QString StringHandlNamespace::concatenationVec(const QVector<int>& vec)
{
  QString str;

  for (int i=0;i<vec.size();i++)
  {
      str+=QString::number(vec[i])+' ';
  }

  return str;
}

*/
