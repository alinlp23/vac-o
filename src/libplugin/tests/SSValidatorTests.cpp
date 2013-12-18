#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <biopp/biopp.h>
#include "fideo/FideoStructureParser.h"

#include "vaco-rna-backends/testing/FoldMock.h"
#include "vaco-rna-backends/testing/StructureCmpMock.h"
#include "vaco-libplugin/SSValidator.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Test;
using namespace biopp;
using namespace fideo;

class SSValidatorTest : public Test
{
protected:
    FoldMock fold_backend;
    StructureCmpMock str_cmp_backend;
public:
    fideo::Fe fake_fold(const NucSequence& /*seq*/,  bool /*circ*/, SecStructure& str)
    {
        fideo::ViennaParser::parseStructure("((...))", str);
        return -3.f;
    }
    fideo::Fe fake_bad_fold(const NucSequence& /*seq*/, bool /*circ*/, SecStructure& str)
    {
        fideo::ViennaParser::parseStructure(".......", str);
        return 0.f;
    }
};

TEST_F(SSValidatorTest, MinSimilitude)
{
    EXPECT_CALL(fold_backend, fold(_, false, _))
    .Times(2)
    .WillRepeatedly(Invoke(this, &SSValidatorTest::fake_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .Times(2)
    .WillOnce(Return(.5f))
    .WillOnce(Return(.3f));

    SecStructure str;
    fideo::ViennaParser::parseStructure(".(...).", str);

    IQAValidator* validator = new SSValidator<MinSimilitude>(&fold_backend, &str_cmp_backend, str, .4f, false);
    NucSequence s;

    EXPECT_TRUE(validator->validate(s));
    EXPECT_FALSE(validator->validate(s));

    delete validator;
}

TEST_F(SSValidatorTest, MaxSimilitude)
{
    EXPECT_CALL(fold_backend, fold(_, false, _))
    .Times(2)
    .WillRepeatedly(Invoke(this, &SSValidatorTest::fake_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .Times(2)
    .WillOnce(Return(.5f))
    .WillOnce(Return(.3f));

    SecStructure str;
    fideo::ViennaParser::parseStructure(".(...).", str);

    IQAValidator* validator = new SSValidator<MaxSimilitude>(&fold_backend, &str_cmp_backend, str, .4f, false);
    NucSequence s;

    EXPECT_FALSE(validator->validate(s));
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}

TEST_F(SSValidatorTest, BadFold)
{
    EXPECT_CALL(fold_backend, fold(_, true, _))
    .Times(2)
    .WillOnce(Invoke(this, &SSValidatorTest::fake_fold))
    .WillOnce(Invoke(this, &SSValidatorTest::fake_bad_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .Times(1)
    .WillOnce(Return(.3f));

    SecStructure str;
    fideo::ViennaParser::parseStructure(".(...).", str);

    IQAValidator* validator = new SSValidator<MaxSimilitude>(&fold_backend, &str_cmp_backend, str, .4f, true);
    NucSequence s;

    EXPECT_TRUE(validator->validate(s));
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}
