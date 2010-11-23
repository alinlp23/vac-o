#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SimulatedAnnealing.h"
#include "testing/NeighborhoodMock.h"
#include "testing/SolutionMock.h"
#include "testing/StrategyMock.h"

using ::testing::Test;
using ::testing::AtMost;

class SimulatedAnnealingTest : public Test
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
        size_t i=0;
        while (i<4 && !done)
        {
            neighbor = new SolutionMock;
            done = nei.SubjectNotify(neighbor);
            ++i;
        }
    }
};

TEST_F(SimulatedAnnealingTest, RunAllIterations)
{
    IStrategy* strategy = new SimulatedAnnealing(&nei, 3, 3, 1, .9f, 2.f, 0.f);
    nei.SubjectSet(strategy);
    strategy->set_scorer(&scorer);

    EXPECT_CALL(scorer, evaluate(_))
            .WillOnce(Return(5))//init
            .WillOnce(Return(6))//iteration 1
            .WillOnce(Return(4))
            .WillOnce(Return(7))
            .WillOnce(Return(5))
            .WillOnce(Return(8))//iteration 2
            .WillOnce(Return(6))
            .WillOnce(Return(7))
            .WillOnce(Return(9))
            .WillOnce(Return(9))//iteration 3
            .WillOnce(Return(6))
            .WillOnce(Return(10))
            .WillOnce(Return(8));

    EXPECT_CALL(nei, explore(_))
            .Times(AtMost(3))
            .WillRepeatedly(Invoke(this, &SimulatedAnnealingTest::fake_explore));
    
    EXPECT_CALL(observer, update(_,_))
            .Times(AtMost(3))
            .WillRepeatedly(Return());
    
    strategy->run(initial, &observer);
    delete strategy;
}


TEST_F(SimulatedAnnealingTest, NoNeighbors)
{
    IStrategy* strategy = new SimulatedAnnealing(&nei, 5, 3, 1, .9f, 2.f, 0.f);
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

TEST_F(SimulatedAnnealingTest, LowTemp)
{
    IStrategy* strategy = new SimulatedAnnealing(&nei, 5, 3, 1, .1f, 2.f, .3f);
    nei.SubjectSet(strategy);
    strategy->set_scorer(&scorer);

    EXPECT_CALL(scorer, evaluate(_))
            .WillOnce(Return(5))
            .WillOnce(Return(6))
            .WillOnce(Return(7))
            .WillOnce(Return(3))
            .WillOnce(Return(4));

    EXPECT_CALL(observer, update(_,_))
            .Times(AtMost(1))
            .WillRepeatedly(Return());

    EXPECT_CALL(nei, explore(_))
            .Times(1)
            .WillRepeatedly(Invoke(this, &SimulatedAnnealingTest::fake_explore));

    strategy->run(initial, &observer);
    delete strategy;
}