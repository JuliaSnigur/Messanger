#include "stdafx.h"
#include "parsedata.h"

ParseData::ParseData()
{

}

 ParseData::~ParseData(){}


 QString  ParseData::concatenationVec(request req,std::vector<QString>& vec)
{
    QString res=QString::number(req)+' ';

    for(std::size_t i=0;i<vec.size();i++)
        res+=vec[i]+' ';

    return res;
}

  QString ParseData::concatenation2(request req,const QString& str1,const QString& str2)
 {
     return QString::number(req)+' '+str1+' '+str2;
 }

  QString ParseData::concatenation1(request req,const QString& str)
  {
      return QString::number(req)+' '+str;
  }


   std::queue<QString> ParseData::separetionQStr(QString str)
   {
       QString st;
       QTextStream stream(&str);
       std::queue<QString> q;

       while(!stream.atEnd())
       {
           stream>>st;
           q.push(st);
       }
       return q;
   }


    std::queue<QByteArray> ParseData::separetionQByte(QString str)
    {
        QString st;
        QTextStream stream(&str);
        std::queue<QByteArray> q;

        while(!stream.atEnd())
        {
            stream>>st;
            q.push(st.toLatin1());
        }
        return q;
    }






