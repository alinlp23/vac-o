#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "vaco-libplugin/Solution.h"
#include "vaco-libplugin/testing/CombinatoryRegionMock.h"

using ::testing::Test;

class SolutionTest : public Test
{
protected:
    CombinatoryRegionMock r1;
    CombinatoryRegionMock r2;
    CombinatoryRegionsCt regions;
    NucSequence seq;

    void SetUp()
    {
        r1.set_bounds(1, 5);
        r2.set_bounds(6, 9);
        string str = "AAAGGGCCCUUU";
        seq = NucSequence(str);

        insert_into(regions, &r1);
        insert_into(regions, &r2);
    }
};

TEST_F(SolutionTest, DefaultScore)
{
    ISolution* s = new Solution(seq, regions);
    Score score = s->compute_local_score(2);
    EXPECT_EQ(score, 1);

    delete s;
}

TEST_F(SolutionTest, Clone)
{
    ISolution* s = new Solution(seq, regions);
    ISolution* c = s->clone();
    Score score = c->compute_local_score(2);
    EXPECT_EQ(score, 1);

    delete s;
    delete c;
}

TEST_F(SolutionTest, UpdateSolution)
{
    ISolution* s = new Solution(seq, regions);

    string sdelta = "UUUU";
    NucSequence delta(sdelta);
    LocalOptimization op(delta, .3f);

    string scseq = "AUUUUGCCCUUU";
    NucSequence cseq(scseq);
    s->update_solution(0, cseq, op);

    NucSequence seq;
    s->get_sequence(seq);
    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_EQ(seq[1 + i], delta[i]);
    }
    Score score = s->compute_local_score(1);
    EXPECT_EQ(score, .3f);

    score = s->compute_local_score(0);
    EXPECT_EQ(score, 1);

    delete s;
}

TEST_F(SolutionTest, UpdateSolutionException)
{
    ISolution* s = new Solution(seq, regions);

    string sdelta = "UUUU";
    NucSequence delta(sdelta);
    LocalOptimization op(delta, .3f);

    NucSequence cseq;
    EXPECT_THROW(s->update_solution(2, cseq, op), PluginException);

    string str = "AA";
    cseq = NucSequence(str);
    EXPECT_THROW(s->update_solution(0, cseq, op), PluginException);

    delete s;
}