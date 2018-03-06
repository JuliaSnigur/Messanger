#pragma once

#include <QVector>


enum request{Error, Connection, Registration, Authorization, Message, File, GetNewList,GetID};


namespace StringHandlNamespace {


  //  QString concatenationVec(const QVector<int>&);

    //QString variable(QString& str);
   // QVector<int> separateVec(QString&);


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


  static  QVector<int>separateVec(QString& str)
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


  static  QString concatenationVec(const QVector<int>& vec)
    {
      QString str;

      for (int i=0;i<vec.size();i++)
      {
          str+=QString::number(vec[i])+' ';
      }

      return str;
    }




   }




