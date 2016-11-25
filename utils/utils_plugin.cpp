#include "utils_plugin.h"
#include "pref.h"
#include "settingsmanager.h"
#include "saveimage.h"
#include "Mobile.h"
#include <qqml.h>
#include <QtQml>

void UtilsPlugin::registerTypes(const char *uri)
{
    // @uri UtilsPlugin
    qmlRegisterType<SettingsManager>(uri, 1, 0, "SettingsManager");
    qmlRegisterType<pref>(uri, 1, 0, "Preferences");
    qmlRegisterType<SaveImage>(uri, 1, 0, "SaveImage");
    qmlRegisterType<Mobile>(uri, 1, 0, "Mobile");
}
