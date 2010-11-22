#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "rna_backends_types.h"


TEST(SecStructureTest, Create)
{
    SecStructure s1("((..(...)..))");
    EXPECT_EQ(s1.to_str(), "((..(...)..))");

    SecStructure s2;
    s2 = "((..(...)..))";
    EXPECT_EQ(s2.to_str(), "((..(...)..))");

    EXPECT_THROW(SecStructure s3("((..(...)..)."), InvalidStructureException);
    SecStructure s4;
    EXPECT_THROW(s4 = "((..(...)..).", InvalidStructureException);
}

TEST(SecStructureTest, Pair)
{
    SecStructure s1("((..(...)..))");
    s1.pair(2,10);
    EXPECT_EQ(s1.to_str(), "(((.(...).)))");
    s1.pair(0, 9);
    EXPECT_EQ(s1.to_str(), "(((.(...)))).");
}

TEST(SecStructureTest, UnPair)
{
    SecStructure s1("((..(...)..))");
    s1.unpair(0);
    EXPECT_EQ(s1.to_str(), ".(..(...)..).");
    s1.unpair(0);
    EXPECT_EQ(s1.to_str(), ".(..(...)..).");
}

TEST(SecStructureTest, ToStr)
{
    SecStructure s1("((..(...)..))");
    EXPECT_EQ(s1.to_str(), "((..(...)..))");
}


TEST(SecStructureTest, IsPaired)
{
    SecStructure s1("((..(...)..))");
    EXPECT_TRUE(s1.is_paired(0));
    EXPECT_FALSE(s1.is_paired(2));
    EXPECT_TRUE(s1.is_paired(4));
}

TEST(SecStructureTest, PairLength)
{
    SecStructure s1("((..(...)..))");
    EXPECT_EQ(s1.pair_length(), 3);

    SecStructure s2(".......");
    EXPECT_EQ(s2.pair_length(), 0);
}
