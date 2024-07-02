#ifndef SQLDB_PLUGIN_H
#define SQLDB_PLUGIN_H

#include <QQmlExtensionPlugin>

class UtilsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
    
public:
    void registerTypes(const char *uri);
};

#endif // SQLDB_PLUGIN_H

