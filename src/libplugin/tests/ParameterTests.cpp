#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Parameter.h"

using ::testing::Test;

class ParameterTest : public Test
{
protected:
    IParameter* float_param;
    IParameter* int_param;
    IParameter* string_param;
    float fp;
    int ip;
    string sp;

    void SetUp()
    {
        fp = 0;
        ip = 0;
        sp = "";
        float_param = new Parameter<float>("float value", fp);
        int_param = new Parameter<int>("int value", ip);
        string_param = new Parameter<string>("string value", sp);
    }
    void TearDown()
    {
        delete float_param;
        delete int_param;
        delete string_param;
    }
};

TEST_F(ParameterTest, GetName)
{
    string text;
    float_param->get_name(text);
    EXPECT_EQ(text, "float value");

    int_param->get_name(text);
    EXPECT_EQ(text, "int value");

    string_param->get_name(text);
    EXPECT_EQ(text, "string value");
}

TEST_F(ParameterTest, SetValue)
{
    EXPECT_TRUE(float_param->set_value("6.5"));
    EXPECT_EQ(fp, 6.5f);

    EXPECT_TRUE(int_param->set_value("5"));
    EXPECT_EQ(ip, 5);

    EXPECT_TRUE(string_param->set_value("something"));
    EXPECT_EQ(sp, "something");
}

TEST_F(ParameterTest, SetBadValue)
{
    EXPECT_FALSE(float_param->set_value("NaN"));
    EXPECT_EQ(fp, 0);

    EXPECT_FALSE(int_param->set_value("NaN"));
    EXPECT_EQ(ip, 0);
}

TEST_F(ParameterTest, CastValue)
{
    EXPECT_TRUE(int_param->set_value("4.5"));
    EXPECT_EQ(ip, 4);
}