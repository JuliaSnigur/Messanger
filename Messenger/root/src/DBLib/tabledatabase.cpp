#include"stdafx.h"
#include "tabledatabase.h"


TableDataBase::TableDataBase():m_name(""){}

TableDataBase::~TableDataBase(){}



TableDataBase::TableDataBase(QString n):m_name(n){}


QString TableDataBase::getName(){return m_name;}
void TableDataBase::setName(QString n){m_name=n;}


