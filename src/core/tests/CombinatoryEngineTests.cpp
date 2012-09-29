#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "vaco-commons/testing/PluginMock.h"
#include "vaco-commons/testing/StrategyMock.h"
#include "vaco-commons/testing/SolutionMock.h"
#include "vaco-commons/testing/ObserverMock.h"

#include "vaco-core/CombinatoryEngine.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::DoAll;
using ::testing::Test;

class CombinatoryEngineTest : public Test
{
protected:
    StrategyMock strategy;
    PluginMock plg;
public:
    void fake_strategy_runner(const ISolution* /*init*/, ISolutionObserver* obs)
    {
        SolutionMock sol;
        EXPECT_CALL(sol, get_sequence(_)).Times(1);
        obs->update(&sol, (strategy.scorer)->evaluate(&sol));
    }

    void fake_observer_update(const SequenceOptimization* opt)
    {
        EXPECT_EQ(opt->second, 10);
        delete opt;
    }
};

TEST_F(CombinatoryEngineTest, RunForest)
{
    EXPECT_CALL(strategy, set_scorer(_))
    .Times(1);

    EXPECT_CALL(plg, get_strategy())
    .Times(1)
    .WillOnce(Return(&strategy));

    CombinatoryEngine engine(&plg);
    ObserverMock<SequenceOptimization> obs;
    engine.attach(&obs);

    EXPECT_CALL(strategy, run(_, &engine))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &CombinatoryEngineTest::fake_strategy_runner), Return()));

    EXPECT_CALL(plg, get_initial_solution())
    .Times(1);

    EXPECT_CALL(plg, evaluate_solution(_))
    .Times(1)
    .WillOnce(Return(10));

    EXPECT_CALL(obs, update(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &CombinatoryEngineTest::fake_observer_update), Return()));

    engine.run_forest();
}


