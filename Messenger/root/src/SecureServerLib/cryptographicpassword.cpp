#include"stdafx.h"

#include "cryptographicpassword.h"

QByteArray Server::encryptedPassword(const QString& pass)
{
    return QCryptographicHash::hash(pass.toLocal8Bit(), QCryptographicHash::Md5);
}
