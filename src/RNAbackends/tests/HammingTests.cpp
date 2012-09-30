#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Hamming.h"
#include "testing/DistanceMatrixProviderMock.h"

using ::testing::Test;
using ::testing::_;
using ::testing::Return;

class HammingTest : public Test
{
protected:
    NucSequence seq1;
    NucSequence seq2;
    NucSequence seq3;

    void SetUp()
    {
        string s1 = "AAACCC";
        seq1 = s1;
        string s2 = "AACATC";
        seq2 = s2;
        string s3 = "AAC";
        seq3 = s3;
    }

public:
    inline void fake_provider(DistanceMatrix& matrix)
    {
        matrix[0][2] = 1.5f; //A->C
        matrix[2][0] = 0.2f; //C->A
        matrix[2][1] = 0.5f; //C->T
    }
};

TEST_F(HammingTest, CompareWithDefaultMatrix)
{
    ISequenceCmp* hamming = new Hamming;
    EXPECT_EQ(hamming->compare(seq1, seq2), 3);

    delete hamming;
}

TEST_F(HammingTest, CompareWithCustomMatrix)
{
    DistanceMatrixProviderMock matrix_provider;
    EXPECT_CALL(matrix_provider, get_distance_matrix(_))
    .Times(1)
    .WillOnce(Invoke(this, &HammingTest::fake_provider));

    ISequenceCmp* hamming = new Hamming(&matrix_provider);
    EXPECT_EQ(hamming->compare(seq1, seq2), 2.2f);

    delete hamming;
}

TEST_F(HammingTest, CompareException)
{
    ISequenceCmp* hamming = new Hamming;
    EXPECT_THROW(hamming->compare(seq1, seq3), RNABackendException);

    delete hamming;
}