#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "AllMutator.h"

TEST(AllMutatorTest, AllMutations)
{
    IQAMutator* mutator = new AllMutator(5, 2);

    string str = "AAAAA";
    NucSequence s = str;
    mutator->set_base_sequence(s);

    size_t i = 0;
    NucSequence mutated;
    while (mutator->next(mutated))
        ++i;

    EXPECT_EQ(i, 105); //5*3^1 + 10*3^2
    delete mutator;
}


