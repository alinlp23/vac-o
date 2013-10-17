#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <biopp/biopp.h>
#include "fideo/FideoStructureParser.h"

#include "vaco-rna-backends/testing/FoldMock.h"
#include "vaco-rna-backends/testing/StructureCmpMock.h"
#include "vaco-libplugin/testing/QAValidatorMock.h"
#include "vaco-libplugin/IQAValidator.h"
#include "vaco-libplugin/QAWholeRegion.h"
#include "vaco-libplugin/RecombValidator.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Test;
using namespace biopp;
using namespace fideo;


class RecombValidatorTest : public Test
{
protected:
    FoldMock fold_backend;
    QAValidatorMock validatorMock;
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

    bool okValidate(const NucSequence& /*seq*/)
    {
        return true;
    }
};

TEST_F(RecombValidatorTest, WithoutRecombinantInfo)
{
    const fideo::Similitude similitude = .5f;
    SecStructure wt_struct;
    fideo::ViennaParser::parseStructure(std::string("....((((((.......((.....))....))).))).."), wt_struct);
    RecombinantInfo recombinantInfo;
    IQAValidator* validator = new RecombValidator<MaxSimilitude>(recombinantInfo, fold_backend, str_cmp_backend, wt_struct, similitude);

    NucSequence s;
    EXPECT_TRUE(validator->validate(s));

    delete validator;
};


TEST_F(RecombValidatorTest, QAWholeRegion)
{

    EXPECT_CALL(validatorMock, validate(_))
    .WillOnce(Invoke(this, &RecombValidatorTest::okValidate));
    IQARegion* qARegion = new QAWholeRegion(&validatorMock);
    NucSequence s;
    EXPECT_TRUE(qARegion->validate(s));
    delete qARegion;
};

TEST_F(RecombValidatorTest, QAWholeRegionEmpty)
{

    EXPECT_CALL(validatorMock, validate(NucSequence()))
    .WillOnce(Invoke(this, &RecombValidatorTest::okValidate));
    IQARegion* qARegion = new QAWholeRegion(&validatorMock);
    NucSequence s;
    EXPECT_TRUE(qARegion->validate(s));
    delete qARegion;
};

TEST_F(RecombValidatorTest, QAWholeRegionNonEmpty)
{

    EXPECT_CALL(validatorMock, validate(NucSequence("CGCGCAG")))
    .WillOnce(Invoke(this, &RecombValidatorTest::okValidate));
    IQARegion* qARegion = new QAWholeRegion(&validatorMock);
    NucSequence s("CGCGCAG");
    EXPECT_TRUE(qARegion->validate(s));
    delete qARegion;
};

TEST_F(RecombValidatorTest, WithRecombinantInfo)
{
    EXPECT_CALL(fold_backend, fold(_, false, _))
    .WillRepeatedly(Invoke(this, &RecombValidatorTest::fake_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .WillRepeatedly(Return(.3f));

    const fideo::Similitude similitude = .5f;
    SecStructure wt_struct;
    fideo::ViennaParser::parseStructure(std::string("((...))"), wt_struct);
    RecombinantInfo recomb;
    RecombinantInfo::RecombinantSequenceInfo recombinantSequenceInfo;
    recombinantSequenceInfo.sequence = NucSequence("CGCGCAG");
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(1, 2));
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(4, 7));

    recomb.recombinantSequences.push_back(recombinantSequenceInfo);

    recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(1, 2));
    recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(4, 7));

    IQAValidator* validator = new RecombValidator<MaxSimilitude>(recomb, fold_backend, str_cmp_backend, wt_struct, similitude);

    NucSequence s("CGCGCAG");
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}

TEST_F(RecombValidatorTest, WithRecombinantInfoButWithoutCandidateRegions)
{
    EXPECT_CALL(fold_backend, fold(_, false, _))
    .WillRepeatedly(Invoke(this, &RecombValidatorTest::fake_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .WillRepeatedly(Return(.3f));

    const fideo::Similitude similitude = .5f;
    SecStructure wt_struct;
    fideo::ViennaParser::parseStructure(std::string("((...))"), wt_struct);
    RecombinantInfo recomb;
    RecombinantInfo::RecombinantSequenceInfo recombinantSequenceInfo;
    recombinantSequenceInfo.sequence = NucSequence("CGCGCAG");
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(1, 2));
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(4, 7));

    recomb.recombinantSequences.push_back(recombinantSequenceInfo);

    //recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(1, 2));
    //recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(4, 7));

    IQAValidator* validator = new RecombValidator<MaxSimilitude>(recomb, fold_backend, str_cmp_backend, wt_struct, similitude);

    NucSequence s("CGCGCAG");
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}

TEST_F(RecombValidatorTest, WithRecombinantInfoButWithoutRegions)
{
    EXPECT_CALL(fold_backend, fold(_, false, _))
    .WillRepeatedly(Invoke(this, &RecombValidatorTest::fake_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .WillRepeatedly(Return(.3f));

    const fideo::Similitude similitude = .5f;
    SecStructure wt_struct;
    fideo::ViennaParser::parseStructure(std::string("((...))"), wt_struct);
    RecombinantInfo recomb;
    RecombinantInfo::RecombinantSequenceInfo recombinantSequenceInfo;
    recombinantSequenceInfo.sequence = NucSequence("CGCGCAG");

    recomb.recombinantSequences.push_back(recombinantSequenceInfo);

    recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(1, 2));
    recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(4, 7));

    IQAValidator* validator = new RecombValidator<MaxSimilitude>(recomb, fold_backend, str_cmp_backend, wt_struct, similitude);

    NucSequence s("CGCGCAG");
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}

TEST_F(RecombValidatorTest, WithRecombinantInfoBadFold)
{
    EXPECT_CALL(fold_backend, fold(_, false, _))
    .WillRepeatedly(Invoke(this, &RecombValidatorTest::fake_bad_fold));
    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .WillRepeatedly(Return(.3f));

    const fideo::Similitude similitude = .5f;
    SecStructure wt_struct;
    fideo::ViennaParser::parseStructure(std::string("((...))"), wt_struct);
    RecombinantInfo recomb;
    RecombinantInfo::RecombinantSequenceInfo recombinantSequenceInfo;
    recombinantSequenceInfo.sequence = NucSequence("CGCGCAG");
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(1, 2));
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(4, 7));

    recomb.recombinantSequences.push_back(recombinantSequenceInfo);

    recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(1, 2));
    recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(4, 7));

    IQAValidator* validator = new RecombValidator<MaxSimilitude>(recomb, fold_backend, str_cmp_backend, wt_struct, similitude);

    NucSequence s("CGCGCAG");
    EXPECT_TRUE(validator->validate(s));

    delete validator;
}
