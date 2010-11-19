#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Neighborhood.h"
#include "testing/CombinatoryRegionMock.h"
#include "testing/SolutionMock.h"
#include "testing/StrategyMock.h"

using ::testing::Test;
using ::testing::_;

class NeighborhoodTest : public Test
{
protected:
    CombinatoryRegionMock r1;
    CombinatoryRegionMock r2;
    StrategyMock strategy;
    SolutionMock solution;
    SolutionMock clone;
    CombinatoryRegionsCt regions;
    NucSequence seq;

    void SetUp()
    {
        r1.set_bounds(1, 5);
        r2.set_bounds(6, 9);
        string str = "AAAGGGCCCUUU";
        seq = str;

        insert_into(regions, &r1);
        insert_into(regions, &r2);

        EXPECT_CALL(solution, get_sequence(_))
            .Times(1)
            .WillOnce(Return());

        EXPECT_CALL(r1, set_base_sequence(_))
                .Times(1)
                .WillOnce(Return());

        EXPECT_CALL(solution, compute_local_score(0))
                .Times(1)
                .WillOnce(Return(0.7f));

        EXPECT_CALL(r2, set_base_sequence(_))
                .Times(1)
                .WillOnce(Return());

        EXPECT_CALL(solution, compute_local_score(1))
                .Times(1)
                .WillOnce(Return(0.6f));
    }  
};


TEST_F(NeighborhoodTest, FullExplore)
{
    INeighborhood* nei = new Neighborhood(regions, 0.3f, 2);
    nei->set(&strategy);

    EXPECT_CALL(r1, generate(_,_))
            .Times(2)
            .WillRepeatedly(Return(0.6f));

    EXPECT_CALL(r2, generate(_,_))
            .Times(2)
            .WillRepeatedly(Return(0.7f));

    EXPECT_CALL(solution, clone())
            .Times(4)
            .WillRepeatedly(Return(&clone));

    EXPECT_CALL(clone, update_solution(0,_,_))
            .Times(2)
            .WillRepeatedly(Return());

    EXPECT_CALL(clone, update_solution(1,_,_))
            .Times(2)
            .WillRepeatedly(Return());

    EXPECT_CALL(strategy, update(_))
            .Times(4)
            .WillRepeatedly(Return(false));

    nei->explore(&solution);
    delete nei;
}

TEST_F(NeighborhoodTest, LowScoreInRegion1)
{
    INeighborhood* nei = new Neighborhood(regions, 0.3f, 2);
    nei->set(&strategy);
    

    EXPECT_CALL(r1, generate(_,_))
            .Times(2)
            .WillRepeatedly(Return(0.3f));

    EXPECT_CALL(r2, generate(_,_))
            .Times(2)
            .WillRepeatedly(Return(0.7f));

    EXPECT_CALL(solution, clone())
            .Times(2)
            .WillRepeatedly(Return(&clone));

    EXPECT_CALL(clone, update_solution(1,_,_))
            .Times(2)
            .WillRepeatedly(Return());

    EXPECT_CALL(strategy, update(_))
            .Times(2)
            .WillRepeatedly(Return(false));

    nei->explore(&solution);
    delete nei;
}

TEST_F(NeighborhoodTest, StopFromStrategy)
{
    INeighborhood* nei = new Neighborhood(regions, 0.3f, 2);
    nei->set(&strategy);
    
    EXPECT_CALL(r1, generate(_,_))
            .Times(2)
            .WillRepeatedly(Return(0.6f));

    EXPECT_CALL(r2, generate(_,_))
            .Times(1)
            .WillRepeatedly(Return(0.7f));

    EXPECT_CALL(solution, clone())
            .Times(3)
            .WillRepeatedly(Return(&clone));

    EXPECT_CALL(clone, update_solution(0,_,_))
            .Times(2)
            .WillRepeatedly(Return());

    EXPECT_CALL(clone, update_solution(1,_,_))
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(strategy, update(_))
            .Times(3)
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true));

    nei->explore(&solution);
    delete nei;
}