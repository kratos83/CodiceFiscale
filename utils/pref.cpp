#include "pref.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QSettings>
#include <QtXml/QtXml>
#include <QtGui>
#include <QMessageBox>
#include <QGraphicsView>
#include <QSysInfo>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>

pref::pref(QQuickItem *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(self_update_parse(QNetworkReply*)));
}

void pref::self_update(){

#if defined(Q_OS_LINUX) && defined(__x86_64__)
    QUrl url("http://www.codelinsoft.it/package/codicefiscale/codfisc-lin64.xml");
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(self_update_parse(QNetworkReply*)));
#elif defined(Q_OS_LINUX) && defined(__x86)
    QUrl url("http://www.codelinsoft.it/package/codicefiscale/codfisc-lin.xml");
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(self_update_parse(QNetworkReply*)));
#elif defined(_WIN64)
    QUrl url("http://www.codelinsoft.it/package/codicefiscale/codfisc-win64.xml");
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(self_update_parse(QNetworkReply*)));
#elif defined(_WIN32)
    QUrl url("http://www.codelinsoft.it/package/codicefiscale/codfisc-win32.xml");
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(self_update_parse(QNetworkReply*)));
#elif defined(Q_OS_MACX)
    QUrl url("http://www.codelinsoft.it/package/codicefiscale/codfisc-macx.xml");
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(self_update_parse(QNetworkReply*)));
#elif defined(Q_OS_FREEBSD)
    QUrl url("http://www.codelinsoft.it/package/codicefiscale/codfisc-unix.xml");
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(self_update_parse(QNetworkReply*)));
#endif
}

void pref::self_update_parse(QNetworkReply* reply){

            // Check file type
            QDomDocument doc( "XML" );
            if (!doc.setContent(reply->readAll(), true)) {
            return;
            }

            QDomElement root = doc.documentElement();
            if( root.tagName() != "appname" ){
                    return;
            }

            // Loop over main nodes
            versione.clear();
            filelist.clear();
            QDomNode mainnode = root.firstChild();
            while( !mainnode.isNull() ){
                    QDomNode subnode = mainnode.firstChild();
            if( !subnode.isNull() ) {
                // Loop over each elements in subnodes
                while(! subnode.isNull()){
                    QDomElement e = subnode.toElement();
                    if(!e.isNull()){
                        // Start parsing, finally
                                            if( e.tagName() == "version" ){
                                                    versione = e.attribute("value","");

                                            }
                                            else if( e.tagName() == "file" ){
                                                    filelist.push_back(e.attribute("value",""));
                                            }
                                    }
                                    subnode = subnode.nextSibling();
                            }
                    }
                    mainnode = mainnode.nextSibling();
            }

            // Compare current version with the one on the server
            if( getVersione() < versione){
                    QString txtt= "http://www.codelinsoft.it/package/";
                    QMessageBox *box= new QMessageBox(0);
                    box->setWindowTitle("CodiceFiscale");
                    box->setText("Aggiornamento");
                    box->setInformativeText(tr("E' disponibile la nuova versione ")+versione+ tr(",se vuoi aggiornare clicca per aggiornare.\n"
                                            "Se clicchi ok si chiude il programma e si aggiorna il software alla nuova versione"));
                    box->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                    box->setDefaultButton(QMessageBox::Ok);
                    int ret = box->exec();
                    switch(ret){
                         case QMessageBox::Ok:
                           //Open update
                            up_dw(filelist.data()->toStdString().c_str(),txtt);
                            box->close();
                            //exit(0);
                            break;
                         case QMessageBox::Cancel:
                            //Close
                            box->close();
                            break;
                         }
            }
            else if(reply->error()){
                QMessageBox::warning(0,tr("CodiceFiscale"),QString(tr("Errore...\n")).arg(reply->errorString()));
            }
            else{
                    // Update success dialog
                QMessageBox::information(0,tr("CodiceFiscale"),tr("Stai usando la nuova versione"));
            }
}


void pref::up_dw(QString package, QString url){
    process = new QProcess(this);
#if defined(Q_OS_LINUX)
    process->startDetached("./update -u "+url+" -p "+package);
#elif defined(Q_OS_WIN)
    process->start("C:\\CodiceFiscale\\update.exe -u "+url+" -p "+package);
#elif defined(Q_OS_MACX)
    process->start("./update.app/Contents/MacOS/update -u "+url+" -p "+package);
#elif defined(Q_OS_FREEBSD)
    process->start("./update -u "+url+" -p "+package);
#endif
}

void pref::setVersione(const QString &ver)
{
    m_versione = ver;
}
