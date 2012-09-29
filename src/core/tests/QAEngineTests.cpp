#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "vaco-commons/testing/QARegionMock.h"
#include "vaco-commons/testing/SubjectMock.h"
#include "vaco-commons/testing/ObserverMock.h"
#include "vaco-core/QAEngine.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Test;

class QAEngineTest : public Test
{
protected:
    void SetUp()
    {
        insert_into(regions, &r1);
        insert_into(regions, &r2);
        string str_seq = "AAGGCC";
        seq = NucSequence(str_seq);
        Score score = 5;
        opt = new SequenceOptimization(seq, score);
    }

    QARegionMock r1;
    QARegionMock r2;
    QARegionsCt regions;
    SubjectMock<SequenceOptimization> subject;
    NucSequence seq;
    SequenceOptimization* opt;
};

TEST_F(QAEngineTest, ValidationPass)
{
    ObserverMock<SequenceOptimization> obs;
    QAEngine engine(regions);

    EXPECT_CALL(r1, validate(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(r2, validate(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(obs, update(_))
    .Times(1);

    engine.attach(&obs);
    subject.SubjectAttach(&engine);
    subject.SubjectNotify(opt);

    delete opt;
}

TEST_F(QAEngineTest, ValidationFail)
{
    ObserverMock<SequenceOptimization> obs;
    QAEngine engine(regions);

    EXPECT_CALL(r1, validate(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(r2, validate(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(obs, update(_))
    .Times(0);

    engine.attach(&obs);
    subject.SubjectAttach(&engine);
    subject.SubjectNotify(opt);
}

TEST_F(QAEngineTest, StopValidationAsSoonAsFail)
{
    ObserverMock<SequenceOptimization> obs;
    QAEngine engine(regions);

    EXPECT_CALL(r1, validate(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(r2, validate(_))
    .Times(0);

    engine.attach(&obs);
    subject.SubjectAttach(&engine);
    subject.SubjectNotify(opt);
}
