/****************************************************************************
**
** Copyright (C) 2006-2014 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
**
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
#ifndef PREF_H
#define PREF_H
/******************************
 *Classi pref
 *************************/
#include "ui_pref.h"
#include "settingsmanager.h"

/******************************
 *Classi QT
 *************************/
#include <QBuffer>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtGui>
#include <QProcess>
#include <QVector>


class QPluginLoader;

using namespace std;

class pref : public QDialog, public Ui::pref
{
    Q_OBJECT
//static const QString VERSION; // Current version

public:
    explicit pref(QWidget *parent = 0);
    void readsettings();
    // Self Update
    QBuffer xmldata;
    int getRequestId;
    int filedownloaded;
    QString versione;
    QVector<QString> filelist; // The list of files to be downloaded
    QNetworkAccessManager *manager;
    QListWidgetItem *configButton,*updateButton;
    SettingsManager *settings;
    QProcess *process;

protected:
    void changeEvent(QEvent *e);

signals:
    void load_plugins();
    void menu_mod();

private:

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void menu_pref();
    void interface();
    void applica();
    void self_update();
    void self_update_parse(QNetworkReply *reply);
    void agg_en();
    void agg_dis();
    void visagg();
    void up_dw(QString package, QString url);
    void esci();
};

#endif // PREF_H
