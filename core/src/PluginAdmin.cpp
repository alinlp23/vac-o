/*
 * File:   PluginAdmin.cpp
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 10, 2010, 4:26 PM
 *
 * Copyright (C) 2010  Santiago Videla, FuDePAN
 *
 * This file is part of vac-o
 *
 * vac-o is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * vac-o is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vac-o.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
        *(void**)(&create_plugin) = dlsym(handle, "create_plugin");

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
