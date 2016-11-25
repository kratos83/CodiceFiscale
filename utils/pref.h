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
 *Classi QT
 *************************/
#include <QBuffer>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtQuick>
#include <QLocale>
#include <QProcess>
#include <QVector>

/*!
 * La classe pref è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QDialog.
 *
 * Ui::pref è la parte creata automaticamente da
 * qtcreator in fase di programmazione e realizzazione
 * dell'interfaccia.
 *
 *
 * \brief <b>class pref : public QObject</b>
 * \param QDialog, Ui::pref
 */
class pref : public QObject
{
    /*!
     * Macro Qt
     *
     *
     * \brief Q_OBJECT
     */
    Q_OBJECT
    Q_PROPERTY(QString getVersione READ getVersione WRITE setVersione)


public:
    /*!
     * Costruttore <b>explicit pref(QQuickItem *parent = 0);</b>
     *
     * Questa classe visualizza le impostazioni.
     *
     *
     * \brief <b>explicit pref(QQuickItem *parent = 0);</b>
     * \param parent = 0
     */
    explicit pref(QQuickItem *parent = 0);
    

    /*!
     * QBuffer legge i dati da un file
     * xml.
     *
     * \brief <b>QBuffer xmldata;</b>
     */
    QBuffer xmldata;

     /*!
     * getRequestId serve a leggere l'ID del
     * download.
     *
     *
     * \brief <b>int getRequestId</b>
     */
    int getRequestId;

    /*!
     * filedownloaded serve a scaricare il file
     * di aggiornamento.
     *
     * \brief <b>int filedownloaded</b>
     */
    int filedownloaded;

    /*!
     * Visualizza la versione del programma
     *
     *
     * \brief <b>QString versione;</b>
     */
    QString versione;

    /*!
     * filelist serve è un vettore che acquisisce
     * tutto il file in download.
     *
     *
     * \brief <b>std::vector<QString> filelist;</b>
     */
    QVector<QString> filelist; // The list of files to be downloaded

     /*!
     * manager serve a collegarsi al network per
     * il download dell'aggiornamento.
     *
     * \brief <b>QNetworkAccessManager *manager</b>
     */
    QNetworkAccessManager *manager;

     /*!
     * process serve ad avviare le istanze di terze parti
     * del programma.
     *
     *
     * \brief <b>QProcess *process</b>
     */
    QProcess *process;
    QString m_versione;
    QString getVersione() const { return m_versione; };
    void setVersione(const QString &ver);

private:

public slots:
    /*!
     * La funzione self_update() serve a creare
     * un collegamento con il network e se trova
     * l'aggiornamento passa i dati alla funzione
     * self_update_parse(QNetworkReply *reply);
     *
     *
     * \brief <b>void self_update()</b>
     */
    Q_INVOKABLE void self_update();

    /*!
     * La funzione self_update_parse(QNetworkReply *reply) serve
     * a leggere il file xml caricato sul serve e verificare
     * se la versione del programma installato è aggiornato
     * oppure no.
     *
     *
     * \brief <b>void self_update_parse(QNetworkReply *reply);</b>
     * \param QNetworkReply *reply;
     */
    void self_update_parse(QNetworkReply *reply);

    /*!
     * Se il programma di aggiornamento verifica l'esistenza
     * di una nuova versione, automaticamente avvia la finestra
     * di download, mediante la funzione up_dw(QString package, QString url).
     *
     *
     * \brief <b>void up_dw(QString package, QString url);</b>
     * \param QString package;------------[<b>package passa il parametro al gestore di aggiornamento</b>]
     * \param QString url;-----------[<b>url passa il paramentro al gestore di aggiornamento</b>]
     */
    void up_dw(QString package, QString url);
};

#endif // PREF_H
