#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "RNAFold.h"

TEST(RNAFoldTest, Fold)
{
    NucSequence seq("CGCAGGGAUCG");

    IFold* fold = new RNAFold;
    SecStructure structure;
    EXPECT_EQ(fold->fold(seq, structure, false), -10.8f);

    string expected = "(.(.....).)";
    EXPECT_EQ(structure.to_str(), expected);

    delete fold;
}
