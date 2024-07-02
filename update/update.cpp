#include "update.h"
#include <QtNetwork/QNetworkRequest>
#include <QDir>
#include <QQmlComponent>
#include <QStringList>

update::update(QQuickItem *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

update::update(QQuickItem *wig, QString url, QString agg):
    QObject(wig), downloadedCount(0), sizepause(0)
{
    manager = new QNetworkAccessManager(this);
    setTestoUrl(url);
    setTestoPkg(agg);
}

void update::download(){

    //Avvia processo di cambio permessi su linux e freebsd
    QProcess *lin_start = new QProcess(this);
#if defined (Q_OS_LINUX)
    lin_start->start("pkexec chmod 777 /opt/codicefiscale");
#elif defined(Q_OS_FREEBSD)
    lin_start->start("sudo chmod 777 /opt/codicefiscale");
#endif

    QUrl url(testoUrl()+testoPkg());
    QString filename = QFileInfo(url.path()).fileName();
    sizepause =0;
    mCurrentRequest = QNetworkRequest(url);
    output = new QFile(filename+".part");
    output->open(QIODevice::ReadWrite);
    QString dw = tr("Scaricamento in corso di:  ");
    QString w = filename;
    QString files_down = dw+" "+w;
    setFileDown(files_down);
    startNextDownload(mCurrentRequest);
    riavvio = true;
    stop = false;
}

QString update::download(QString av_dw){

   return av_dw;
}

void update::startNextDownload(QNetworkRequest& request){

        currentDownload = manager->get(request);

        connect(currentDownload, SIGNAL(finished()),SLOT(downloadFinished()));
        connect(currentDownload, SIGNAL(readyRead()),SLOT(downloadReadyRead()));
        connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),SLOT(downloadProgress(qint64,qint64)));
        connect(currentDownload, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(error(QNetworkReply::NetworkError)));

        // prepare the output
        downloadTime.start();
}

void update::downloadProgress(qint64 bytesReceived, qint64 bytesTotal){

        setByteRicevuti(bytesReceived);
        setByteTotali(bytesTotal);
        
        // calcolo la velocità di download
        double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
        QString unit;
        if (speed < 1024) {
            unit = "bytes/sec";
        } else if (speed < 1024*1024) {
            speed /= 1024;
            unit = "kB/s";
        } else {
            speed /= 1024*1024;
            unit = "MB/s";
        }

        //Calcolo la dimensione del file da scaricare
        double peso = bytesReceived;

        QString dt;
        if (peso < 1024) {
            dt = "bytes";
        } else if (peso < 1024*1024) {
            peso /= 1024;
            dt = "kB";
        } else {
            peso /= 1024*1024;
            dt = "MB";
        }

        int secs = downloadTime.elapsed()/1000;
        int mins = (secs/60)%60;
        int hours = (secs/3600);
        secs = secs%60;

        QString ts = QString::fromLatin1("%1 %2").arg(speed, 3, 'f', 1).arg(unit);
        QString ts1 = QString::fromLatin1("%1 %2").arg(peso,3,'f',1).arg(dt);
        setSpeedDown(QString::fromUtf8(tr("Velocità di scaricamento: ").toStdString().c_str())+ts+tr("  Dimensione: ")+ts1+tr(" Tempo stimato: ")+QString("%1:%2:%3").arg(hours,2,10, QLatin1Char('0')).arg(mins,2,10, QLatin1Char('0')).arg(secs,2,10, QLatin1Char('0')));
}

void update::downloadFinished(){
                output->close();
                QUrl url(testoUrl()+testoPkg());
                QString filename = QFileInfo(url.path()).fileName();
                QDir *direct = new QDir( QCoreApplication::applicationDirPath() );
#if defined(Q_OS_LINUX)
                QString fileNames=direct->currentPath()+"/"+filename+".part";
#elif defined(Q_OS_MACX)
                QString fileNames=direct->currentPath()+"/"+filename+".part";
#elif defined(Q_OS_WIN)
                QString fileNames=direct->currentPath()+"\\"+filename+".part";
#elif defined(Q_OS_FREEBSD)
                QString fileNames=direct->currentPath()+"/"+filename+".part";
#endif
                if(currentDownload->error()){
                    QString ts = tr("Download fallito: ")+currentDownload->errorString();
                    setFileDown(ts);
                    output->remove(fileNames);
                }
                else{
                    output->rename(fileNames,filename);
                    downloadReadyRead();
                    ++downloadedCount;
                    QString txs = tr("Scaricamento completato");
                    setFileDown(txs);
                    emit finished();
                    install_package();
                }

}

void update::downloadReadyRead(){
    output->write(currentDownload->readAll());    
}

void update::pause(){


    QString p_s = tr("Scaricamento annullato");
    setFileDown(p_s);

    if( currentDownload == 0 ) {
        setFileDown(tr("Errore scaricamento"));
    }

    disconnect(currentDownload,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
    disconnect(currentDownload,SIGNAL(finished()),this,SLOT(downloadFinished()));

    currentDownload->abort();
    output->remove();
}

void update::install_package(){

   QUrl url(testoUrl()+testoPkg());
   QString filename = QFileInfo(url.path()).fileName();

   QDir *direct = new QDir( QCoreApplication::applicationDirPath() );
   QString file_dir=direct->currentPath()+"/"+filename;
   QStringList fileNames=direct->entryList( QStringList("*.zip"), QDir::Files, QDir::Name);
   fileNames << filename;
#if defined(Q_OS_LINUX)
    lin_start = new QProcess(this);
    connect(lin_start,SIGNAL(readyReadStandardOutput()),this,SLOT(display_progress_bar()));
    lin_start->start("pkexec unzip -o "+file_dir+" -d /opt/codicefiscale/");
#elif defined(Q_OS_WIN)
    win_start = new QProcess(this);
    connect(win_start,SIGNAL(readyReadStandardOutput()),this,SLOT(display_progress_bar()));
    win_start->start("C:\\CodiceFiscale\\windows\\unzip -o "+file_dir+" -d C:\\CodiceFiscale");
#elif defined(Q_OS_MAC64)
    mac_start = new QProcess(this);
    connect(mac_start,SIGNAL(readyReadStandardOutput()),this,SLOT(display_progress_bar()));
    mac_start->start("unzip -o "+file_dir+" -d /Applications/CodiceFiscale/");
#elif defined(Q_OS_FREEBSD)
   unix_start = new QProcess(this);
   connect(unix_start,SIGNAL(readyReadStandardOutput()),this,SLOT(display_progress_bar()));
   unix_start->start("sudo unzip -o "+file_dir+" -d /opt/codicefiscale/");
#endif
}

void update::display_progress_bar()
{
#if defined (Q_OS_LINUX)
    int val = lin_start->readLine().toInt();
#elif defined(Q_OS_WIN)
    int val = win_start->readLine().toInt();
#elif defined(Q_OS_MAC64)
    int val = mac_start->readLine().toInt();
#elif defined(Q_OS_FREEBSD)
    int val = unix_start->readLine().toInt();
#endif
    for(val=0;val <= 100; val++){
        setInstallPackage(val);
    }
}

void update::error(QNetworkReply::NetworkError code){
    setFileDown(tr("Download fallito "));
}

QString update::testoPkg() const
{
    return m_txts;
}

void update::setTestoPkg(const QString& pkg)
{
    m_txts = pkg;
    emit changeText();
}

void update::setTestoUrl(const QString& url)
{
    m_url_p = url;
    emit changeText();
}

QString update::testoUrl() const
{
    return m_url_p;
}

QString update::fileDown()
{
    return f_down;
}

double update::getByteRicevuti()
{
    return byte_ricevuti;
}

double update::getByteTotali()
{
    return byte_totali;
}

void update::setByteRicevuti(quint64 br)
{
    byte_ricevuti = br;
    emit changeText();
}

void update::setByteTotali(quint64 bt)
{
    byte_totali = bt;
    emit changeText();
}

void update::setFileDown(QString name)
{
    f_down = name;
    emit changeText();
}

void update::setSpeedDown(QString speed)
{
    vel = speed;
    emit changeText();
}

QString update::speedDown()
{
    return vel;
}

double update::getInstallPackage()
{
    return byte_pack;
}

void update::setInstallPackage(double values)
{
    byte_pack = values;
    emit changeText();
}

update::~update()
{
}
