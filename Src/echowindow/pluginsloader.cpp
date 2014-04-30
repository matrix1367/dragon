#include "pluginsloader.h"
#include <QDir>
#include <QPluginLoader>
#include "../plugin/echoplugin.h"
#include <qdebug.h>

PluginsLoader::PluginsLoader()
{
}

void PluginsLoader::load(QString path)
{
      QDir pluginsDir(path);

      foreach (QString fileName, pluginsDir.entryList(QDir::Files))
      {
          QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
          QObject *plugin = pluginLoader.instance();
          if (plugin)
          {
              IPlugin * iplugin = qobject_cast<IPlugin *>(plugin);
              if (iplugin)
              {
                  m_plugins.push_back(iplugin);
                  qDebug() << "fff " << iplugin->getName();
              }
          }
          else
          {
              qDebug() << "not is plugin  " << fileName;
          }
      }

      for( int i = 0; i < m_plugins.size(); i++ )
       {
            qDebug() << m_plugins[ i ]->getName() << "\n";
       }
}
