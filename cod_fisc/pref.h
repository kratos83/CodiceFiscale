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
#include <QLocale>
#include <QProcess>
#include <QVector>

/*!
 * Uso della classe QPluginLoader
 *
 * \brief <b>class QPluginLoader</b>
 */
class QPluginLoader;

/*!
 * Uso gli ogetti standard del c++.
 *
 * \brief <b>using namespace std</b>
 */
using namespace std;



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
 * \brief <b>class pref : public QDialog, public Ui::pref</b>
 * \param QDialog, Ui::pref
 */
class pref : public QDialog, public Ui::pref
{
    /*!
     * Macro Qt
     *
     *
     * \brief Q_OBJECT
     */
    Q_OBJECT


public:
    /*!
     * Costruttore <b>explicit pref(QWidget *parent = 0);</b>
     *
     * Questa classe visualizza le impostazioni.
     *
     *
     * \brief <b>explicit pref(QWidget *parent = 0);</b>
     * \param parent = 0
     */
    explicit pref(QWidget *parent = 0);

    /*!
     * La funzione readsettings() serve a
     * leggere le impostazioni scritte nel file
     * di sistema.
     *
     *
     * \brief <b>void readsettings();</b>
     */
    void readsettings();
    

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
     * configButton serve a modifificare le impostazioni del programma.
     *
     *
     * \brief <b>QListWidgetItem *configButton</b>
     */
    QListWidgetItem *configButton,
    /*!
     * updateButton serve a visualizzare la scheda per l'aggiornamento
     * del programma.
     *
     *
     * \brief <b>QListWidgetItem *updateButton</b>
     */
    *updateButton;

    /*!
     * settings serve a i paramentri di impostazione
     * del programma.
     *
     *
     * \brief <b>SettingsManager *settings</b>
     */
    SettingsManager *settings;

     /*!
     * process serve ad avviare le istanze di terze parti
     * del programma.
     *
     *
     * \brief <b>QProcess *process</b>
     */
    QProcess *process;

    /*!
     * default_language serve a impostare la lingua
     * al programma.
     *
     *
     * \brief <b>QString default_language</b>
     */
    QString default_language;

protected:
    /*!
     * Funzione per cambiare la
     * traduzione della lingua.
     *
     * \brief <b>void changeEvent(QEvent *e);</b>
     * \param QEvent *e;
     */
    void changeEvent(QEvent *e);

signals:
    /*!
     * La funzione load_plugins() serve a poter emettere
     * un segnale per impostare la configurazione all'interno
     * del file di sistema.
     *
     * \brief <b>void load_plugins();</b>
     */
    void load_plugins();
   
    /*!
     * La funzione menu_mod() serve a poter emettere
     * un segnale per impostare il menu.
     *
     * \brief <b>void menu_mod()</b>
     */
    void menu_mod();

private:

public slots:
     /*!
     * La funzione changePage(QListWidgetItem *current, QListWidgetItem *previous)
     * serve a cambiare pagina nella finestra di dialogo delle impostazioni.
     *
     *
     * \brief <b>void changePage(QListWidgetItem *current, QListWidgetItem *previous);</b>
     * \param QListWidgetItem *current;------------[<b>current serve a tenere la pagina corrente delle preferenze</b>]
     * \param QListWidgetItem *previous;-----------[<b>previous serve tornare indietro la pagina delle preferenze</b>]
     */
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

    /*!
     * La funzione menu_pref() visualizza le finestre
     * di configurazione del software.
     *
     *
     * \brief <b>void menu_pref()</b>
     */
    void menu_pref();

    /*!
     * La funzione interfaccia() visualizza una
     * QListWidget all'interno della finestra di dialogo.
     *
     *
     * \brief <b>void interfaccia()</b>
     */
    void interfaccia();
   
    /*!
     * La funzione applica() serve ad impostare i paramentri
     * di configurazione all'interno del file di sistema.
     *
     *
     * \brief <b>void applica();</b>
     */
    void applica();


    /*!
     * La funzione self_update() serve a creare
     * un collegamento con il network e se trova
     * l'aggiornamento passa i dati alla funzione
     * self_update_parse(QNetworkReply *reply);
     *
     *
     * \brief <b>void self_update()</b>
     */
    void self_update();

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
     * La funzione agg_en() serve ad abilitare l'aggiornamento
     * automatico del software e il relativo bottone per avviare
     * il download manualmente.
     *
     *
     * \brief <b>void agg_en();</b>
     */
    void agg_en();

    /*!
     * La funzione agg_en() serve a disabilitare l'aggiornamento
     * automatico del software e il relativo bottone per avviare
     * il download manualmente.
     *
     *
     * \brief <b>void agg_dis()</b>
     */
    void agg_dis();

    /*!
     * La funzione visagg() serve a leggere i parametri
     * booleani per la gestione degli aggiornamenti
     *
     * \brief <b>void visagg()</b>
     */
    void visagg();

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

    /*!
     * La funzione esci() serve a far uscire 
     * la finestra di dialogo delle prefenze.
     *
     * \brief <b>void esci()</b>
     */
    void esci();

    /*!
     * Funzione per cambiare la
     * traduzione della lingua.
     *
     * \brief <b>void combo_language();</b>
     */
    void combo_language();

    /*!
     * set_language serve a settare la lingua
     * al programma.
     *
     *
     * \brief <b>QString set_language</b>
     */
    QString set_language();
};

#endif // PREF_H
