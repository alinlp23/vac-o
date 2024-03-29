#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <biopp/biopp.h>
#include "vaco-libplugin/testing/MutationMatrixProviderMock.h"
#include "vaco-libplugin/RandomMutator.h"

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
    IQAMutator* const mutator = new RandomMutator(4, 10);
    const std::string str = "AAAAAA";
    biopp::NucSequence s(str);

    mutator->set_base_sequence(s);
    size_t i = 0;
    biopp::NucSequence mutated;
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

    const std::string str = "AAAAAA";
    biopp::NucSequence s(str);

    mutator->set_base_sequence(s);
    size_t i = 0;
    biopp::NucSequence mutated;
    while (mutator->next(mutated))
    {
        for (size_t idx = 0; idx < mutated.length(); ++idx)
        {
            EXPECT_TRUE(mutated[idx] == static_cast<biopp::Nucleotide::Alpha>(0) || mutated[idx] == static_cast<biopp::Nucleotide::Alpha>(3));
        }
        ++i;
    }

    EXPECT_EQ(i, 10);
    delete mutator;
}
