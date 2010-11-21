#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "FirstImprovement.h"
#include "testing/NeighborhoodMock.h"
#include "testing/SolutionMock.h"
#include "testing/StrategyMock.h"

using ::testing::Test;

class FirstImprovementTest : public Test
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
        bool done;
        do{            
            neighbor = new SolutionMock;
            done = nei.SubjectNotify(neighbor);
        } while(!done);        
    }
};

TEST_F(FirstImprovementTest, RunAllIterations)
{
    IStrategy* strategy = new FirstImprovement(&nei, 5, 3);
    nei.SubjectSet(strategy);
    strategy->set_scorer(&scorer);

    EXPECT_CALL(scorer, evaluate(_))            
            .WillOnce(Return(5))//init
            .WillOnce(Return(6))//iteration 1
            .WillOnce(Return(5))
            .WillOnce(Return(7))//iteration 2
            .WillOnce(Return(7))//iteration 3
            .WillOnce(Return(8))//iteration 4
            .WillOnce(Return(10));//iteration 5

    EXPECT_CALL(nei, explore(_))
            .Times(5)
            .WillRepeatedly(Invoke(this, &FirstImprovementTest::fake_explore));

    EXPECT_CALL(observer, update(_,6))
            .WillOnce(Return());

    EXPECT_CALL(observer, update(_,7))
            .WillOnce(Return())
            .WillOnce(Return());

    EXPECT_CALL(observer, update(_,8))
            .WillOnce(Return());

    EXPECT_CALL(observer, update(_,10))
            .WillOnce(Return());

    strategy->run(initial, &observer);
    delete strategy;
}

TEST_F(FirstImprovementTest, RunUntilIdle)
{
    IStrategy* strategy = new FirstImprovement(&nei, 5, 3);
    nei.SubjectSet(strategy);
    strategy->set_scorer(&scorer);

    EXPECT_CALL(scorer, evaluate(_))
            .WillOnce(Return(5))//init
            .WillOnce(Return(6))//iteration 1
            .WillOnce(Return(6))//iteration 2
            .WillOnce(Return(6))//iteration 3
            .WillOnce(Return(6));//iteration 4

    EXPECT_CALL(nei, explore(_))
            .Times(4)
            .WillRepeatedly(Invoke(this, &FirstImprovementTest::fake_explore));

    EXPECT_CALL(observer, update(_,6))
            .Times(4)
            .WillRepeatedly(Return());

    strategy->run(initial, &observer);
    delete strategy;
}

TEST_F(FirstImprovementTest, NoNeighbors)
{
    IStrategy* strategy = new FirstImprovement(&nei, 5, 3);
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