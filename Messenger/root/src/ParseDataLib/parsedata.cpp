#include "stdafx.h"
#include "parsedata.h"

#include<QtDebug>

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




   QString ParseData::variable(QString& str)
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





    QString ParseData::concatenationRespond(request req,bool flag,const QString& str)
    {
        return QString::number(req)+' '+QString::number(flag)+' '+str;
    }




