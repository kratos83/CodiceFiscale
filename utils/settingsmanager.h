#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QtCore>

class SettingsManager: public QObject
{
    Q_OBJECT
public:
	SettingsManager(QObject *parent=0);
    Q_INVOKABLE QVariant generalValue(QString const &key, QVariant const &defaultValue = QVariant()) const;
    Q_INVOKABLE void setGeneralValue( QString const &key, QVariant const &value);
    Q_INVOKABLE void clear_file();
	
    QDir *settingsDir;
private:
	QSettings *general;
};

#endif
