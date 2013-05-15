#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "vaco-libplugin/testing/QAMutatorMock.h"
#include "vaco-libplugin/testing/QAValidatorMock.h"
#include "vaco-libplugin/QARegion.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Test;


class QARegionTest : public Test
{
protected:
    QAMutatorMock mutator;
    QAValidatorMock validator;
    biopp::NucSequence sequence;
    SeqIndex start;
    SeqIndex end;

    void SetUp()
    {
        string seq = "GGGCCC";
        sequence = biopp::NucSequence(seq);
        start = 1;
        end = 4;
    }
public:
    void fake_mutant(biopp::NucSequence& seq)
    {
        string str = "AAA";
        seq = biopp::NucSequence(str);
    }
};

TEST_F(QARegionTest, AllMutantsPass)
{
    EXPECT_CALL(mutator, set_base_sequence(_))
    .Times(1)
    .WillOnce(Return());

    EXPECT_CALL(mutator, next(_))
    .Times(4)
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(Return(false));

    EXPECT_CALL(validator, validate(_))
    .WillRepeatedly(Return(true));

    IQARegion* region = new QARegion(start, end, 1, &mutator, &validator);
    EXPECT_TRUE(region->validate(sequence));

    delete region;
}

TEST_F(QARegionTest, StopAsSoonAsFail)
{
    EXPECT_CALL(mutator, set_base_sequence(_))
    .Times(1)
    .WillOnce(Return());

    EXPECT_CALL(mutator, next(_))
    .Times(2)
    .WillRepeatedly(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)));

    EXPECT_CALL(validator, validate(_))
    .WillOnce(Return(true))
    .WillOnce(Return(true))
    .WillOnce(Return(false));

    IQARegion* region = new QARegion(start, end, 2, &mutator, &validator);
    EXPECT_FALSE(region->validate(sequence));

    delete region;
}

TEST_F(QARegionTest, AllMutantsPassInDepth)
{
    EXPECT_CALL(mutator, set_base_sequence(_))
    .Times(4)
    .WillRepeatedly(Return());

    EXPECT_CALL(mutator, next(_))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(Return(false)) // ends level 1
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(Return(false))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(Return(false))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(Return(false)) // ends level 2
    .WillRepeatedly(Return(true));

    EXPECT_CALL(validator, validate(_))
    .Times(7)
    .WillRepeatedly(Return(true));

    IQARegion* region = new QARegion(start, end, 2, &mutator, &validator);
    EXPECT_TRUE(region->validate(sequence));

    delete region;
}

TEST_F(QARegionTest, StopAsSoonAsFailInDepth)
{
    EXPECT_CALL(mutator, set_base_sequence(_))
    .Times(2)
    .WillRepeatedly(Return());

    EXPECT_CALL(mutator, next(_))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)))
    .WillOnce(Return(false))
    .WillRepeatedly(DoAll(Invoke(this, &QARegionTest::fake_mutant), Return(true)));

    EXPECT_CALL(validator, validate(_))
    .WillOnce(Return(true))
    .WillOnce(Return(true))
    .WillOnce(Return(true))
    .WillOnce(Return(false)); //first mutant in level 2 will stop validation

    IQARegion* region = new QARegion(start, end, 2, &mutator, &validator);
    EXPECT_FALSE(region->validate(sequence));

    delete region;
}