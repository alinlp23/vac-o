#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "testing/MutationMatrixProviderMock.h"
#include "RandomMutator.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::DoAll;

inline void fake_provider(MutationMatrix& matrix)
{
    //Force mutations from A to G and from G to A.
    size_t i = 0; //Always A -> G
    for (size_t j = 0; j < MATRIX_SIZE; ++j)
        matrix[i][j] = 3 != j ? 0.f : 1.f;

    i = 3; //Always G -> A
    for (size_t j = 0; j < MATRIX_SIZE; ++j)
        matrix[i][j] = 0 != j ? 0.f : 1.f;

    // C and T uniform to any other
    for (i = 1; i < 3; ++i)
    {
        for (size_t j = 0; j < MATRIX_SIZE; ++j)
            matrix[i][j] = i == j ? 0.f : 1.f / 3.f;
    }

}

TEST(RandomMutatorTest, AllMutationsWithDefaultMatrix)
{
    IQAMutator* mutator = new RandomMutator(4, 10);
    string str = "AAAAAA";
    NucSequence s = str;

    mutator->set_base_sequence(s);
    size_t i = 0;
    NucSequence mutated;
    while (mutator->next(mutated))
        ++i;

    EXPECT_EQ(i, 10);
    delete mutator;
}

TEST(RandomMutatorTest, AllMutationsWithCustomMatrix)
{
    MutationMatrixProviderMock matrix_provider;
    EXPECT_CALL(matrix_provider, get_mutation_matrix(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(fake_provider), Return()));

    IQAMutator* mutator = new RandomMutator(4, 10, &matrix_provider);

    string str = "AAAAAA";
    NucSequence s = str;

    mutator->set_base_sequence(s);
    size_t i = 0;
    NucSequence mutated;
    while (mutator->next(mutated))
    {
        for (size_t idx = 0; idx < mutated.length(); ++idx)
        {
            EXPECT_TRUE(mutated[idx] == 0 || mutated[idx] == 3);
        }
        ++i;
    }

    EXPECT_EQ(i, 10);
    delete mutator;
}
