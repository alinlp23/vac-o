#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "IPlugin.h"
#include "PluginAdmin.h"

TEST(PluginAdminTest, LoadRightPlugin)
{    
    PluginAdmin plg_admin;    
    IPlugin* plg = plg_admin.load("core/testing/libtesting_right_plg.so");

    EXPECT_EQ(plg->get_ranking_size(), 0);
    plg_admin.unload(plg);   
}

TEST(PluginAdminTest, LoadWrongPlugin)
{
    PluginAdmin plg_admin;
    EXPECT_THROW(plg_admin.load("core/testing/libtesting_wrong_plg.so"), PluginException);
}

TEST(PluginAdminTest, LoadWrongPath)
{
    PluginAdmin plg_admin;
    EXPECT_THROW(plg_admin.load("not/existing/plugin.so"),PluginException);
}
