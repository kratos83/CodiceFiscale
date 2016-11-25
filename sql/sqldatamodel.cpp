/****************************************************************************
**
** Copyright (C) 2006-2014 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
 *
 *
** This file is part of the project CodiceFiscale
**
** LGPLv3 License
**
**  You may use this file under the terms of the LGPLv3 license as follows:
*
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Codelinsoft and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#include "sqldatamodel.h"
#include <QDebug>

SqlDataModel *dat = 0;

SqlDataModel::SqlDataModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    dat = this;
}

QString SqlDataModel::executeQuery()
{
    return exQuery;
}

void SqlDataModel::setExcecuteQuery(const QString &query)
{
    exQuery = query;
    setQuery(exQuery);
    roleNames();
}

QVariant SqlDataModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
       int columnIdx = role - Qt::UserRole - 1;
       QModelIndex modelIndex = this->index(index.row(), columnIdx);
       value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

QHash<int, QByteArray> SqlDataModel::roleNames() const
{
    QHash<int,QByteArray> hash;
    for( int i = 0; i < record().count(); i++) {
       hash.insert(Qt::UserRole + i + 1, QByteArray(record().fieldName(i).toLatin1()));
    }
    return hash;
}

QString SqlDataModel::valore() const
{
    return mVal;
}

void SqlDataModel::setValore(const QString &val)
{
    mVal = val;
}

QString SqlDataModel::setQueryModel(const QString &query)
{
    QString value;
    QSqlQuery mQuery;
    mQuery.prepare(query);
    if(mQuery.exec())
    {
        if(mQuery.next())
        {
            value = mQuery.value(0).toString();
        }
    }
    qDebug() <<  value;
    return value;
}
