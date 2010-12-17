#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "testing/FoldMock.h"
#include "testing/StructureCmpMock.h"
#include "SSValidator.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Test;

class SSValidatorTest : public Test
{
protected:
    FoldMock fold_backend;
    StructureCmpMock str_cmp_backend;
public:
    Fe fake_fold(const NucSequence& seq, SecStructure& str, bool circ)
    {
        str = "((...))";
        return -3.f;
    }
    Fe fake_bad_fold(const NucSequence& seq, SecStructure& str, bool circ)
    {
        str = ".......";
        return 0.f;
    }
};

TEST_F(SSValidatorTest, MinSimilitude)
{
    EXPECT_CALL(fold_backend, fold(_, _, false))
    .Times(2)
    .WillRepeatedly(Invoke(this, &SSValidatorTest::fake_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .Times(2)
    .WillOnce(Return(.5f))
    .WillOnce(Return(.3f));

    SecStructure str(".(...).");
    IQAValidator* validator = new SSValidator<MinSimilitude>(&fold_backend, &str_cmp_backend, str, .4f, false);
    NucSequence s;

    EXPECT_TRUE(validator->validate(s));
    EXPECT_FALSE(validator->validate(s));

    delete validator;
}

TEST_F(SSValidatorTest, MaxSimilitude)
{
    EXPECT_CALL(fold_backend, fold(_, _, false))
    .Times(2)
    .WillRepeatedly(Invoke(this, &SSValidatorTest::fake_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .Times(2)
    .WillOnce(Return(.5f))
    .WillOnce(Return(.3f));

    SecStructure str(".(...).");
    IQAValidator* validator = new SSValidator<MaxSimilitude>(&fold_backend, &str_cmp_backend, str, .4f, false);
    NucSequence s;

    EXPECT_FALSE(validator->validate(s));
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}

TEST_F(SSValidatorTest, BadFold)
{
    EXPECT_CALL(fold_backend, fold(_, _, true))
    .Times(2)
    .WillOnce(Invoke(this, &SSValidatorTest::fake_fold))
    .WillOnce(Invoke(this, &SSValidatorTest::fake_bad_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .Times(1)
    .WillOnce(Return(.3f));

    SecStructure str(".(...).");
    IQAValidator* validator = new SSValidator<MaxSimilitude>(&fold_backend, &str_cmp_backend, str, .4f, true);
    NucSequence s;

    EXPECT_TRUE(validator->validate(s));
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}
