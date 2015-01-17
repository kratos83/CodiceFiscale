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

pref::pref(QWidget *parent) :
    QDialog(parent), Ui::pref()
{
    setupUi(this);
    setModal(true);
    connect(chiudi,SIGNAL(clicked()),this,SLOT(esci()));
    connect(apply,SIGNAL(clicked()),this,SLOT(applica()));
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(self_update_parse(QNetworkReply*)));
    connect(en_update,SIGNAL(clicked(bool)),this,SLOT(agg_en()));
    connect(ds_update,SIGNAL(clicked(bool)),this,SLOT(agg_dis()));
    connect(update_b,SIGNAL(clicked()),this,SLOT(self_update()));
    settings = new SettingsManager(this);
    menu_pref();
    interface();
    readsettings();
    visagg();
    combo_language();
}


void pref::interface(){
    listWidget->setViewMode(QListView::IconMode);
    listWidget->setIconSize(QSize(84,84));
    listWidget->setMovement(QListView::Static);
    listWidget->setMaximumWidth(128);
    listWidget->setSpacing(12);
    listWidget->setCurrentRow(0);
}

void pref::readsettings(){

    settings->generalValue("Version/version",QVariant()).toString();
    en_update->setChecked(settings->generalValue("Update/agg_en",QVariant()).toBool());
    ds_update->setChecked(settings->generalValue("Update/agg_dis",QVariant()).toBool());


    //FONT APPLICATION
    QFont fnt;
    fnt.fromString(settings->generalValue("Application/font","Verdana,-1,11,5,50,0,0,0,0,0").toString());
    cmbFontName->setFont(fnt);
    spinFontSize->setValue(fnt.pixelSize());

    QFont appfnt;
    appfnt.fromString(settings->generalValue("Application/font","Verdana,-1,11,5,50,0,0,0,0,0").toString());
    cmbApplicationFontName->setFont(appfnt);
    spinApplicationFontSize->setValue(appfnt.pixelSize());

    select_lingua->setCurrentText(settings->generalValue("Language/language",QVariant()).toString());

}

void pref::agg_en(){
    if(en_update->isChecked() == true){
        update_b->setVisible(true);
    }
    else
        agg_dis();
}

void pref::agg_dis(){
    if(ds_update->isChecked() == true){
        update_b->setVisible(false);
    }
    else
        agg_en();
}

void pref::visagg(){

    if(settings->generalValue("Update/agg_en",QVariant()).toBool() == true){
        update_b->setVisible(true);
    }
    else{
        update_b->setVisible(false);
    }

    if(settings->generalValue("Update/agg_dis",QVariant()).toBool() == true){
        update_b->setVisible(false);
    }
    else{
        update_b->setVisible(true);
    }

}

void pref::applica(){

    //Salvataggio
    //FONT
    QFont selFont=cmbFontName->currentFont();
    selFont.setPixelSize(spinFontSize->value());
    settings->setGeneralValue("Application/font",selFont.toString());

    //FONT APPLICATION
    QFont appfnt=cmbApplicationFontName->currentFont();
    appfnt.setPixelSize(spinApplicationFontSize->value());
    settings->setGeneralValue("Application/applicationFont",appfnt.toString());

    settings->setGeneralValue("Update/agg_en",en_update->isChecked());
    settings->setGeneralValue("Update/agg_dis",ds_update->isChecked());

    settings->setGeneralValue("AGGIOR/auto_en",en_update->isChecked());
    settings->setGeneralValue("AGGIOR/auto_ds",ds_update->isChecked());

    settings->setGeneralValue("Language/language",select_lingua->currentText());

    readsettings();
    emit load_plugins();
}

void pref::menu_pref(){

        configButton = new QListWidgetItem(listWidget);
        configButton->setIcon(QIcon(":/images/preferences-system.png"));
        configButton->setText(tr("Impostazioni\ngenerali"));
        configButton->setTextAlignment(Qt::AlignHCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        updateButton = new QListWidgetItem(listWidget);
        updateButton->setIcon(QIcon(":/images/system-software-update.png"));
        updateButton->setText(tr("Aggiornamento"));
        updateButton->setTextAlignment(Qt::AlignHCenter);
        updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        connect(listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void pref::changePage(QListWidgetItem *corrente,QListWidgetItem *indietro){
    if(!corrente)
        corrente = indietro;
    stackedWidget->setCurrentIndex(listWidget->row(corrente));
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
            if( settings->generalValue("Version/version",QVariant()).toString() < versione){
                    QString txtt= "http://www.codelinsoft.it/package/";

                    QMessageBox *box= new QMessageBox(this);
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
                           up_dw(QString::fromLatin1(filelist.data()->toStdString().c_str()),txtt);
                           box->close();
			   exit(0);
                           break;
                         case QMessageBox::Cancel:
                            //Close
                           box->close();
                           break;
                         }
            }
            else if(reply->error()){
                QMessageBox::warning(this,tr("CodiceFiscale"),QString(tr("Errore...\n")).arg(reply->errorString()));
            }
            else{
                    // Update success dialog
                QMessageBox::information(this,tr("CodiceFiscale"),tr("Stai usando la nuova versione"));
            }
}


void pref::up_dw(QString package, QString url){
    process = new QProcess(this);
#if defined(Q_OS_LINUX)
    process->start("./update -u "+url+" -p "+package);
#elif defined(Q_OS_WIN)
    process->start("C:\\CodiceFiscale\\update -u "+url+" -p "+package);
#elif defined(Q_OS_MACX)
    process->start("./update.app/Contents/MacOS/update -u "+url+" -p "+package);
#elif defined(Q_OS_FREEBSD)
    process->start("./update -u "+url+" -p "+package);
#endif
}


void pref::esci()
{
    close();
}

void pref::combo_language()
{
    const QDir lang_dir(":/language/language");
    const QStringList files = lang_dir.entryList(QStringList() << "*.qm");
    foreach (QString lang_file, files) {
        lang_file = lang_file.split('.').first();
        select_lingua->addItem(lang_file);
    }

    default_language = set_language();
    if(files.contains(default_language+".qm"))
        default_language = "Italian";
}

QString pref::set_language()
{
    return QLocale::languageToString(QLocale().language());
}

void pref::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
