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
#ifndef UPDATE_H
#define UPDATE_H

#include <QtQuick>
#include <QtGui>
#include <QFile>
#include <QObject>
#include <QQueue>
#include <QTime>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>

/*!
 * La classe update è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QDialog.
 *
 * Ui::update è la parte creata automaticamente da
 * qtcreator in fase di programmazione e realizzazione
 * dell'interfaccia.
 *
 *
 * \brief <b>class update : public QObject</b>
 * \param QObject
 */
class update: public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString testoPkg READ testoPkg WRITE setTestoPkg)
        Q_PROPERTY(QString testoUrl READ testoUrl WRITE setTestoUrl)
        Q_PROPERTY(QString fileDown READ fileDown WRITE setFileDown NOTIFY changeText)
        Q_PROPERTY(QString speedDown READ speedDown WRITE setSpeedDown NOTIFY changeText)
        Q_PROPERTY(double getByteRicevuti READ getByteRicevuti WRITE setByteRicevuti NOTIFY changeText)
        Q_PROPERTY(double getByteTotali READ getByteTotali WRITE setByteTotali NOTIFY changeText)
        Q_PROPERTY(double getInstallPackage READ getInstallPackage WRITE setInstallPackage NOTIFY changeText)
        
public:
    /*!
     * Costruttore <b>explicit update(QQuickItem *parent = 0);</b>
     *
     * Questa classe visualizza una finestra di dialogo
     * con la fase di aggiornamento.
     *
     * \brief <b>explicit update(QQuickItem *parent = 0);</b>
     * \param parent = 0
     */
    explicit update(QQuickItem *parent = 0);
   
    /*!
     * Il costruttore update(QWidget *wig,QString url, QString agg)
     * serve ad avviare la finestra di dialogo con il relativo
     * indirizzo di download e il file da scaricare.
     *
     * \brief <b>update(QQuickItem *wig,QString url, QString agg);</b>
     * \param QWidget *wig;---------[<b>Il parametro wig serve a visualizzare l'oggetto upgrade in fase di aggiornamento</b>]
     * \param QString url;----------[<b>Il parametro url serve a visualizzare l'indirizzo web da dove viene effettuato il download</b>]
     * \param QString agg;----------[<b>Il parametro agg serve a visualizzare il nome del file da scaricare</b>]
     */
    update(QQuickItem *wig,QString url, QString agg);

    //!Distruttore ~update();
    /*!
      Il distruttore ~update() serve a chiudere
      gli eventuali processi attivi
     *\brief <b>~update();</b>
     */
    ~update();

    /*!
     * La stringa txts serve a immagazzinare il nome
     * del file da scaricare.
     *
     * \brief <b>QString txts;</b>
     */
    QString txts, m_txts;
    QString testoPkg() const;
    void setTestoPkg(const QString &pkg);

    /*!
     * La stringa url_up serve a immagazzinare il nome
     *del sito web da dove viene scaricato l'aggiornamento.
     *
     *
     * \brief <b>QString url_up;</b>
     */
    QString url_up, m_url_p;
    QString testoUrl() const;
    void setTestoUrl(const QString &url);
    
    double byte_ricevuti,byte_totali,byte_pack;
    QString f_down,vel;
    Q_INVOKABLE double getByteRicevuti();
    Q_INVOKABLE double getByteTotali();
    Q_INVOKABLE QString fileDown();
    Q_INVOKABLE QString speedDown();
    Q_INVOKABLE double getInstallPackage();
    void setByteRicevuti(quint64 br);
    void setByteTotali(quint64 bt);
    void setFileDown(QString name);
    void setSpeedDown(QString speed);
    void setInstallPackage(double values);
    
private:
 

    /*!
     * Il puntatore *manager serve a connettere l'aggiornamento
     * al  sito internet da dove si scarica il file.
     *
     *
     * \brief <b>QNetworkAccessManager *manager;</b>
     */
    QNetworkAccessManager *manager;

     /*!
     * IL puntatore *currentDownload serve a scaricare il
     * file dal server.
     *
     *
     * \brief <b>QNetworkReply *currentDownload;</b>
     */
    QNetworkReply *currentDownload;

    /*!
     * Il puntatore *mCurrentRequest acquisisce il sito
     * da dove scaricare il file da aggiornare.
     *
     *
     * \brief <b>QNetworkRequest mCurrentRequest;</b>
     */
    QNetworkRequest mCurrentRequest;

    /*!
     * Il puntatore *output serve a creare il file
     * nella cartella temporanea.
     *
     *
     * \brief <b>QFile *output;</b>
     */
    QFile *output;

    /*!
     * downloadedCount serve a creare il pacchetto completo
     * scaricanto tutti i byte/KB/MB/GB ecc.
     *
     *
     * \brief <b>int downloadedCount;</b>
     */
    QTime downloadTime;

    /*!
     * lin_start serve ad avviare i processi su linux
     *
     *
     * \brief <b>QProcess *lin_start</b>
     */
    QProcess *lin_start,
	
    
     /*!
     * win_start serve ad avviare i processi su windows
     *
     *
     * \brief <b>QProcess *win_start</b>
     */
    *win_start, 

    /*!
     * mac_start serve ad avviare i processi su osx
     *
     *
     * \brief <b>QProcess *mac_start</b>
     */
    *mac_start, 

    /*!
     * unix_start serve ad avviare i processi su unix 
     * e derivate
     *
     * \brief <b>QProcess *unix_start</b>
     */
    *unix_start;

    /*!
     * downloadedCount serve a creare il pacchetto completo
     * scaricanto tutti i byte/KB/MB/GB ecc.
     *
     *
     * \brief <b>int downloadedCount;</b>
     */
    int downloadedCount;

    /*!
     * sizepause serve a mettere in pausa il download
     * tenendo conto dei byte scaricati.
     *
     *
     * \brief <b>int sizepause;</b>
     */
    int sizepause;

    /*!
     * Stop serve a fermare il download in attesa del segnale
     * di riavvio.
     *
     * \brief <b>bool stop;</b>
     */
    bool stop,

    /*!
     * Riavvio serve a riavviare il download precedentemente
     * messo in pausa.
     *
     *
     * \brief <b>bool riavvio;</b>
     */
    riavvio;


public slots:
   
    /*!
     * La funzione download(QString av_dw) serve a
     * verificare il nome dell'aggiornamento.
     *
     * \brief <b>QString download(QString av_dw);</b>
     * \param QString av_dw;---------[<b>Ritorna il nome del file scaricato.</b>]
     * \return <b>av_dw</b>
     */
    Q_INVOKABLE QString download(QString av_dw);

     /*!
     * La funzione startNextDownload(QNetworkRequest& request) serve
     * a connettere il segnale di download e scaricare il programma
     * tramite le funzioni:<p>
     * void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
     * <p> void error(QNetworkReply::NetworkError code); <p>
     * void downloadFinished(); <p>
     * void downloadReadyRead();
     *
     *
     * \brief <b>void startNextDownload(QNetworkRequest& request);</b>
     * \param QNetworkRequest& request;-------------[<b>Il parametro request acquisisce il dato da scaricare lanciando il download.</b>]
     */
    Q_INVOKABLE void startNextDownload(QNetworkRequest& request);

    /*!
     * La funzione downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
     * serve a leggere i byte in ingresso e in uscita per la scittura del file
     * scaricato.
     *
     *
     * \brief <b>void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);</b>
     * \param qint64 bytesReceived;-----------[<b>Il parametro bytesReceived serve a leggere i byte ricevuti.</b>]
     * \param qint64 bytesTotal;--------------[<b>Il parametro bytesTotal serve a scrivere il totale dei byte scaricati.</b>]
     */
    Q_INVOKABLE void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    /*!
     * La funzione error(QNetworkReply::NetworkError code)
     * serve a generare l'errore se fallisce il download
     * dell'aggiornamento.
     *
     *
     * \brief <b>void error(QNetworkReply::NetworkError code);</b>
     * \param QNetworkReply::NetworkError code;-----------[<b>Il parametro code visualizza un'eventuale errore durante lo scaricamento.</b>
     */
    Q_INVOKABLE void error(QNetworkReply::NetworkError code);

    /*!
     * La funzione downloadFinished() serve a chiudere
     * la connessione al server e generare il file tramite
     * la funzione downloadReadyRead().
     *
     *
     * \brief <b>void downloadFinished();</b>
     */
    Q_INVOKABLE void downloadFinished();

    /*!
     * La funzione downloadReadyRead() serve a leggere
     * i byte scaricati e scrivere il file di aggiornamento
     * per poi installarlo.
     *
     *
     * \brief <b>void downloadReadyRead();</b>
     */
    Q_INVOKABLE void downloadReadyRead();

    /*!
     * La funzione pause() serve a mettere il download
     * in sospensione per poi riprenderlo in qualsiasi
     * momento.
     *
     *
     * \brief <b>void pause();</b>
     */
    Q_INVOKABLE void pause();

    /*!
     * La funzione install_package() serve a installare
     * l'aggiornamento in maniera silent senza esserci
     * il bisogno di chiudere l'applicazione.
     *
     *
     * \brief <b>void install_package();</b>
     */
    Q_INVOKABLE void install_package();

    /*!
     * La funzione download() serve a lanciare il
     * download dal server.
     *
     * \brief <b>void download();</b>
     */
    Q_INVOKABLE void download();

    /*!
     * La funzione display_progress_bar() serve a 
     * visualizzare la barra di avanzamento dello stato
     * di aggiornamento
     *
     * \brief <b>void display_progress_bar();</b>
     */
    Q_INVOKABLE void display_progress_bar();


signals:

    /*!
     * La funzione finished() emette un segnale
     * di arresto al termine del download o nel caso
     * si metta in pause lo scaricamento.
     *
     * \brief <b>void finished()</b>
     */
    void finished();
    void changeText();
};
#endif // UPDATE_H
