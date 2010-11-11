#include <dlfcn.h>
#include "exceptions.h"
#include "PluginAdmin.h"

IPlugin* PluginAdmin::load(const Path& file) throw(PluginException)
{
    IPlugin* plg;

    handle = dlopen(file.c_str(), RTLD_LAZY);
    
    bool success(handle != NULL);
    if (success)
    {
        typedef IPlugin*(*CreatePlugin)();
        CreatePlugin create_plugin;
        /**
         * Writing:
         * create_plugin = (CreatePlugin) dlsym(handle, "create_plugin");
         * would seem more natural, but the C99 standard leaves
         * casting from "void *" to a function pointer undefined.
         * The assignment used below is the POSIX.1-2003 (Technical
         * Corrigendum 1) workaround; see the Rationale for the
         * POSIX specification of dlsym()
         */
        *(void **) (&create_plugin) = dlsym(handle, "create_plugin");

        if (create_plugin == NULL)
        {
            const string err = dlerror();
            dlclose(handle);
            throw  PluginException(err);
        }
        else
            plg = create_plugin();
    }
    else
        throw  PluginException(dlerror());
    
    return plg;
}

void PluginAdmin::unload(IPlugin* plg)
{
    plg->unload();
    dlclose(handle);
}
