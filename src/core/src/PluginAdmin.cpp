#include "PluginAdmin.h"

/**
 * This is temporal until we `really` load the .so
 */
#include "libplugin.h"

IPlugin* PluginAdmin::load(const Path& file) const throw(PluginException)
{
    IPlugin* plg = new DevPlugin;
    return plg;
}

