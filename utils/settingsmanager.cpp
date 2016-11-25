#include <QDir>
#include <QSettings>
#include <QDebug>
#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject *parent): QObject(parent) {

#ifdef Q_WS_WIN
    settingsDir = new QDir(QDir::homePath()+"/codicefiscale/");
#else
    settingsDir = new QDir(QDir::homePath()+"/.codicefiscale/");
#endif

	if(!settingsDir->exists())
		settingsDir->mkdir(settingsDir->path());

        general = new QSettings(settingsDir->path()+"/config.conf",QSettings::IniFormat);

        if(!general->isWritable())
            qDebug() << "Impossibile scrivere";
}

QVariant SettingsManager::generalValue( const QString &key, const QVariant &defaultValue ) const
{
    return general->value(key,defaultValue);
}

void SettingsManager::setGeneralValue(QString const& key,  QVariant const& value ) {
	general->setValue(key,value);
	general->sync();
}

void SettingsManager::clear_file()
{
    general->clear();
}
