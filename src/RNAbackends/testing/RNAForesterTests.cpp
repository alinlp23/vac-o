#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "RNAForester.h"

TEST(RNAForesterTest, Compare)
{
    IStructureCmp* forester = new RNAForester;
    SecStructure s1("((....))");
    SecStructure s2("(...)...");

    EXPECT_EQ(forester->compare(s1, s2), -1.4f);
    delete forester;
}
