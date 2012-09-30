#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "vaco-commons/IPlugin.h"
#include "vaco-core/PluginAdmin.h"

TEST(PluginAdminTest, LoadRightPlugin)
{
    PluginAdmin plg_admin;
    IPlugin* plg = plg_admin.load(string(INSTALL_LIB_DIR) + "/libvaco-test-right-plugin.so");

    EXPECT_EQ(plg->get_ranking_size(), 0);
    plg_admin.unload(plg);
}

TEST(PluginAdminTest, LoadWrongPlugin)
{
    PluginAdmin plg_admin;
    EXPECT_THROW(plg_admin.load(string(INSTALL_LIB_DIR) + "/libvaco-test-wrong-plugin.so"), PluginException);
}

TEST(PluginAdminTest, LoadWrongPath)
{
    PluginAdmin plg_admin;
    EXPECT_THROW(plg_admin.load("not/existing/plugin.so"), PluginException);
}
