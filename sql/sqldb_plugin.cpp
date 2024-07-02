#include "sqldb_plugin.h"
#include "sqldatabase.h"
#include "sqldatamodel.h"
#include <qqml.h>
#include <QtQml>

void SqlDBPlugin::registerTypes(const char *uri)
{
    // @uri SqlDBPlugin
    qmlRegisterType<SqlDatabase>(uri, 1, 0, "SqlDatabase");
    qmlRegisterType<SqlDataModel>(uri,1, 0,"SqlDataModel");
}
