#ifndef PLUGINSLOADER_H
#define PLUGINSLOADER_H
#include <QWidget>
#include "iplugin.h"
#include <vector>


class PluginsLoader
{
public:
    PluginsLoader();
    void load(QString path);
    int count();
protected:
private:
    std::vector< IPlugin *> m_plugins;
};

#endif // PLUGINSLOADER_H
