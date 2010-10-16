#include <dlfcn.h>
#include "exceptions.h"
#include "PluginAdmin.h"

IPlugin* PluginAdmin::load(const Path& file) throw(PluginException)
{
    IPlugin* plg;
    char* const fileName = strdup(file.c_str());

    handle = dlopen(fileName, RTLD_LAZY);

    bool success(handle != NULL);
    if (success)
    {
        typedef IPlugin*(*CreatePlugin)();

        CreatePlugin create_plugin = (CreatePlugin) dlsym(handle, "create_plugin");

        if (create_plugin == NULL)
        {
            dlclose(handle);
            success = false;
        }
        else
            plg = create_plugin();
    }

    if (!success)
        throw  PluginException(dlerror());

    free(fileName);
    return plg;
}

void PluginAdmin::unload(IPlugin* plg)
{
    plg->unload();
    dlclose(handle);
}
