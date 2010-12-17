#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "BestImprovement.h"
#include "testing/NeighborhoodMock.h"
#include "testing/SolutionMock.h"
#include "testing/StrategyMock.h"

using ::testing::Test;

class BestImprovementTest : public Test
{
protected:
    NeighborhoodMock nei;
    ISolution* initial;
    ISolution* neighbor;
    SolutionObserverMock observer;
    SolutionScorerMock scorer;

    void SetUp()
    {
        initial = new SolutionMock;
    }
public:
    void fake_explore(const ISolution* const s)
    {
        bool done(false);
        size_t i = 0;
        while (i < 4 && !done)
        {
            neighbor = new SolutionMock;
            done = nei.SubjectNotify(neighbor);
            ++i;
        }
    }
};

TEST_F(BestImprovementTest, RunAllIterations)
{
    IStrategy* strategy = new BestImprovement(&nei, 3, 2);
    nei.SubjectSet(strategy);
    strategy->set_scorer(&scorer);

    EXPECT_CALL(scorer, evaluate(_))
    .WillOnce(Return(5))//init
    .WillOnce(Return(6))//iteration 1
    .WillOnce(Return(5))
    .WillOnce(Return(7))
    .WillOnce(Return(7))
    .WillOnce(Return(8))//iteration 2
    .WillOnce(Return(6))
    .WillOnce(Return(9))
    .WillOnce(Return(5))
    .WillOnce(Return(9))//iteration 3
    .WillOnce(Return(5))
    .WillOnce(Return(10))
    .WillOnce(Return(9));

    EXPECT_CALL(nei, explore(_))
    .Times(3)
    .WillRepeatedly(Invoke(this, &BestImprovementTest::fake_explore));

    EXPECT_CALL(observer, update(_, 7))
    .WillOnce(Return());

    EXPECT_CALL(observer, update(_, 9))
    .WillOnce(Return());

    EXPECT_CALL(observer, update(_, 10))
    .WillOnce(Return());

    strategy->run(initial, &observer);
    delete strategy;
}

TEST_F(BestImprovementTest, RunUntilIdle)
{
    IStrategy* strategy = new BestImprovement(&nei, 5, 3);
    nei.SubjectSet(strategy);
    strategy->set_scorer(&scorer);

    EXPECT_CALL(scorer, evaluate(_))
    .WillOnce(Return(5))//init
    .WillOnce(Return(6))//iteration 1
    .WillOnce(Return(5))
    .WillOnce(Return(4))
    .WillOnce(Return(5))
    .WillOnce(Return(4))//iteration 2
    .WillOnce(Return(5))
    .WillOnce(Return(6))
    .WillOnce(Return(3))
    .WillOnce(Return(4))//iteration 3
    .WillOnce(Return(6))
    .WillOnce(Return(5))
    .WillOnce(Return(6))
    .WillOnce(Return(4))//iteration 4
    .WillOnce(Return(5))
    .WillOnce(Return(3))
    .WillOnce(Return(6));

    EXPECT_CALL(nei, explore(_))
    .Times(4)
    .WillRepeatedly(Invoke(this, &BestImprovementTest::fake_explore));

    EXPECT_CALL(observer, update(_, 6))
    .Times(4)
    .WillRepeatedly(Return());

    strategy->run(initial, &observer);
    delete strategy;
}

TEST_F(BestImprovementTest, NoNeighbors)
{
    IStrategy* strategy = new BestImprovement(&nei, 5, 3);
    nei.SubjectSet(strategy);
    strategy->set_scorer(&scorer);

    EXPECT_CALL(scorer, evaluate(_))
    .WillOnce(Return(5));

    EXPECT_CALL(nei, explore(_))
    .Times(3)
    .WillRepeatedly(Return());

    strategy->run(initial, &observer);
    delete strategy;
}
