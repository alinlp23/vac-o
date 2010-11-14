#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "testing/PluginMock.h"
#include "testing/StrategyMock.h"
#include "testing/ObserverMock.h"

#include "CombinatoryEngine.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Test;

TEST(CombinatoryEngineTest, RunForest)
{
    PluginMock plg;
    StrategyMock strategy;    

    EXPECT_CALL(strategy, set_scorer(_))
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(plg, get_strategy())
            .Times(1)
            .WillOnce(Return(&strategy));

    CombinatoryEngine engine(&plg);
    ObserverMock<SequenceOptimization> obs;
    engine.attach(&obs);
    
    EXPECT_CALL(strategy, run(_, &engine))
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(plg, get_initial_solution())
            .Times(1);
    
    engine.run_forest();
}


