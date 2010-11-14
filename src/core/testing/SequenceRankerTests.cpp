#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "testing/SubjectMock.h"
#include "SequenceRanker.h"

using ::testing::Test;

class SequenceRankerTest : public Test
{
protected:
    void SetUp()
    {
        string str_seq = "AAGGCC";
        seq1 = str_seq;
        Score score = 4;
        opt1 = new SequenceOptimization(seq1, score);

        str_seq = "AAGGUU";
        seq2 = str_seq;
        score = 5;
        opt2 = new SequenceOptimization(seq2, score);
    }   
    SubjectMock<SequenceOptimization> subject;
    NucSequence seq1;
    NucSequence seq2;
    SequenceOptimization* opt1;
    SequenceOptimization* opt2;
};

TEST_F(SequenceRankerTest, InsertOptimization)
{
    SequenceRanker ranker(2);
    subject.SubjectAttach(&ranker);
    
    EXPECT_EQ(ranker.size(), 0);
    subject.SubjectNotify(opt1);
    EXPECT_EQ(ranker.size(), 1);

    delete opt2;
}

TEST_F(SequenceRankerTest, KeepBetterOptimizations)
{
    SequenceRanker ranker(1);
    subject.SubjectAttach(&ranker);

    EXPECT_EQ(ranker.size(), 0);
    subject.SubjectNotify(opt1);
    subject.SubjectNotify(opt2);
    EXPECT_EQ(ranker.size(), 1);

    CAutonomousIterator<SequenceRanker> it(ranker);
    while (!it.end())
    {
        EXPECT_TRUE((*it)==opt2);
        ++it;
    }
}
