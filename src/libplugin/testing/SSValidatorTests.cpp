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
    void SetUp()
    {
        EXPECT_CALL(fold_backend, fold(_, _))
                .Times(2);
        EXPECT_CALL(str_cmp_backend, compare(_,_))
                .Times(2)
                .WillOnce(Return(.5f))
                .WillOnce(Return(.3f));
    }
    FoldMock fold_backend;
    StructureCmpMock str_cmp_backend;
};

TEST_F(SSValidatorTest, MinSimilitude)
{
    SecStructure str("(...)");
    IQAValidator* validator = new SSValidator<MinSimilitude>(&fold_backend, &str_cmp_backend, str, .4f);
    NucSequence s;

    EXPECT_TRUE(validator->validate(s));
    EXPECT_FALSE(validator->validate(s));

    delete validator;
}

TEST_F(SSValidatorTest, MaxSimilitude)
{
    SecStructure str("(...)");
    IQAValidator* validator = new SSValidator<MaxSimilitude>(&fold_backend, &str_cmp_backend, str, .4f);
    NucSequence s;

    EXPECT_FALSE(validator->validate(s));
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}


