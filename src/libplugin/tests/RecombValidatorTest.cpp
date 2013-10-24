#include <memory>

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
    const std::auto_ptr<IQAValidator> validator(new RecombValidator<MaxSimilitude>(recombinantInfo, fold_backend, str_cmp_backend, wt_struct, similitude));

    const NucSequence s;
    EXPECT_TRUE(validator->validate(s));
};


TEST_F(RecombValidatorTest, QAWholeRegion)
{

    EXPECT_CALL(validatorMock, validate(_))
    .WillOnce(Invoke(this, &RecombValidatorTest::okValidate));
    const std::auto_ptr<IQARegion> qARegion(new QAWholeRegion(&validatorMock));
    const NucSequence s;
    EXPECT_TRUE(qARegion->validate(s));
};

TEST_F(RecombValidatorTest, QAWholeRegionEmpty)
{

    EXPECT_CALL(validatorMock, validate(NucSequence()))
    .WillOnce(Invoke(this, &RecombValidatorTest::okValidate));
    const std::auto_ptr<IQARegion> qARegion(new QAWholeRegion(&validatorMock));
    const NucSequence s;
    EXPECT_TRUE(qARegion->validate(s));
};

TEST_F(RecombValidatorTest, QAWholeRegionNonEmpty)
{

    EXPECT_CALL(validatorMock, validate(NucSequence("CGCGCAG")))
    .WillOnce(Invoke(this, &RecombValidatorTest::okValidate));
    const std::auto_ptr<IQARegion> qARegion(new QAWholeRegion(&validatorMock));
    const NucSequence s("CGCGCAG");
    EXPECT_TRUE(qARegion->validate(s));
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

    const std::auto_ptr<IQAValidator> validator(new RecombValidator<MaxSimilitude>(recomb, fold_backend, str_cmp_backend, wt_struct, similitude));

    const NucSequence s("CGCGCAG");
    EXPECT_TRUE(validator->validate(s));
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

    const std::auto_ptr<IQAValidator> validator(new RecombValidator<MaxSimilitude>(recomb, fold_backend, str_cmp_backend, wt_struct, similitude));
    const NucSequence s("CGCGCAG");
    EXPECT_TRUE(validator->validate(s));
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

    const std::auto_ptr<IQAValidator> validator(new RecombValidator<MaxSimilitude>(recomb, fold_backend, str_cmp_backend, wt_struct, similitude));

    const NucSequence s("CGCGCAG");
    EXPECT_TRUE(validator->validate(s));

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

    const std::auto_ptr<IQAValidator> validator(new RecombValidator<MaxSimilitude>(recomb, fold_backend, str_cmp_backend, wt_struct, similitude));

    const NucSequence s("CGCGCAG");
    EXPECT_TRUE(validator->validate(s));
}

TEST_F(RecombValidatorTest, SequencesGenerated)
{
    RecombinantInfo recomb;
    RecombinantInfo::RecombinantSequenceInfo recombinantSequenceInfo;
    recombinantSequenceInfo.sequence = NucSequence("ATCCCAG");
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(1, 2));
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(4, 7));

    recomb.recombinantSequences.push_back(recombinantSequenceInfo);

    recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(1, 2));
    recomb.candidateRegions.push_back(RecombinantInfo::PositionsRange(4, 7));

    const NucSequence s("CGCGCAA");
    RecombAlgorithm algorithm(recomb, s);

    std::list<biopp::NucSequence> results;
    //call to Recomb algorithm
    algorithm.run(results);

    std::list<biopp::NucSequence> expectedResults;//recombinants generated
    expectedResults.push_back(NucSequence("CUCGCAA"));
    expectedResults.push_back(NucSequence("CUCCCAA"));
    expectedResults.push_back(NucSequence("CUCCCAA"));
    expectedResults.push_back(NucSequence("CUCCCAA"));
    expectedResults.push_back(NucSequence("CUCCCAG"));
    expectedResults.push_back(NucSequence("CGCCCAA"));
    expectedResults.push_back(NucSequence("CGCCCAA"));
    expectedResults.push_back(NucSequence("CGCCCAA"));
    expectedResults.push_back(NucSequence("CGCCCAG"));
    expectedResults.push_back(NucSequence("CGCGCAA"));
    expectedResults.push_back(NucSequence("CGCGCAA"));
    expectedResults.push_back(NucSequence("CGCGCAG"));
    expectedResults.push_back(NucSequence("CGCGCAA"));
    expectedResults.push_back(NucSequence("CGCGCAG"));
    expectedResults.push_back(NucSequence("CGCGCAG"));
    expectedResults.push_back(NucSequence("AGCCCAG"));
    expectedResults.push_back(NucSequence("AGCGCAG"));
    expectedResults.push_back(NucSequence("AGCGCAG"));
    expectedResults.push_back(NucSequence("AGCGCAG"));
    expectedResults.push_back(NucSequence("AGCGCAA"));
    expectedResults.push_back(NucSequence("AUCGCAG"));
    expectedResults.push_back(NucSequence("AUCGCAG"));
    expectedResults.push_back(NucSequence("AUCGCAG"));
    expectedResults.push_back(NucSequence("AUCGCAA"));
    expectedResults.push_back(NucSequence("AUCCCAG"));
    expectedResults.push_back(NucSequence("AUCCCAG"));
    expectedResults.push_back(NucSequence("AUCCCAA"));
    expectedResults.push_back(NucSequence("AUCCCAG"));
    expectedResults.push_back(NucSequence("AUCCCAA"));
    expectedResults.push_back(NucSequence("AUCCCAA"));

    EXPECT_EQ(results.size(), expectedResults.size());

    std::list<biopp::NucSequence>::const_iterator itExpected = expectedResults.begin();
    std::list<biopp::NucSequence>::const_iterator it = results.begin();
    while(it != results.end() && itExpected != expectedResults.end())
    {
        const size_t expecedLength = 7;
        EXPECT_EQ(it->length(), itExpected->length());
        EXPECT_EQ(*it, *itExpected);
        ++it;
        ++itExpected;
    }
}
