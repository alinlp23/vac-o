#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "testing/FoldMock.h"
#include "testing/FoldInverseMock.h"
#include "testing/SequenceCmpMock.h"
#include "testing/StructureCmpMock.h"

#include "SSRegion.h"

using ::testing::Return;
using ::testing::_;
using ::testing::InSequence;
using ::testing::Test;

class SSRegionTest : public Test
{
protected:
    FoldMock fold_backend;
    FoldInverseMock inverse_backend;
    SequenceCmpMock seq_cmp_backend;
    StructureCmpMock str_cmp_backend;

    SecStructure wt;
    SecStructure va;
    NucSequence base;
    NucSequence partial;
    NucSequence inverse;
    SeqIndex start;
    SeqIndex end;
    NucSequencesCt wt_cache;

    void SetUp()
    {
        wt = "((...))";
        va = "(.....)";
        string b = "AAAAAAA";
        base = b;
        start = 1;
        end = 5;
        partial = b.substr(start, end - start);

        string str = "CTAC";
        inverse = str;
    }
public:
    void fake_query_partial_start(IStartProvider* provider)
    {
        provider->get_partial_start(&inverse_backend);
    }

    void fake_query_complete_start(IStartProvider* provider)
    {
        provider->get_complete_start(&inverse_backend);
    }

    void fake_fold_inverse(NucSequence& delta)
    {
        delta = inverse;
    }

    void fill_cache()
    {
        string str = "GGGGGGG";
        NucSequence s1 = str;
        insert_into(wt_cache, s1);

        str = "CGGGGCC";
        NucSequence s2 = str;
        insert_into(wt_cache, s2);

        str = "AAAAGGG";
        NucSequence s3 = str;
        insert_into(wt_cache, s3);
    }

    void check_partial_start(const NucSequence& seq)
    {
        for (size_t i = 0; i < seq.length(); ++i)
        {
            EXPECT_EQ(seq[i], partial[i]);
        }
    }

    void check_complete_start(const NucSequence& seq)
    {
        for (size_t i = 0; i < seq.length(); ++i)
        {
            EXPECT_EQ(seq[i], base[i]);
        }
    }

    Fe fake_fold(const NucSequence& seq, SecStructure& str, bool circ)
    {
        str = "((...))";
        return -3.f;
    }
};

TEST_F(SSRegionTest, SetBaseSequencePartial)
{
    SSRegion ssregion(start, end, wt, va, 0, 0.8f, 10, wt_cache, false,
                      &fold_backend, &inverse_backend, &str_cmp_backend, &seq_cmp_backend);

    EXPECT_CALL(inverse_backend, query_start(&ssregion))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::fake_query_partial_start), Return()));

    EXPECT_CALL(inverse_backend, set_start(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::check_partial_start), Return()));

    ICombinatoryRegion* issregion = &ssregion;
    issregion->set_base_sequence(base);
}

TEST_F(SSRegionTest, SetBaseSequenceComplete)
{
    SSRegion ssregion(start, end, wt, va, 0, 0.8f, 10, wt_cache, false,
                      &fold_backend, &inverse_backend, &str_cmp_backend, &seq_cmp_backend);

    EXPECT_CALL(inverse_backend, query_start(&ssregion))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::fake_query_complete_start), Return()));

    EXPECT_CALL(inverse_backend, set_start(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::check_complete_start), Return()));

    ICombinatoryRegion* issregion = &ssregion;
    issregion->set_base_sequence(base);
}

TEST_F(SSRegionTest, GenerateWithEmptyCacheZeroMutations)
{
    SSRegion ssregion(start, end, wt, va, 0, 0.8f, 10, wt_cache, false,
                      &fold_backend, &inverse_backend, &str_cmp_backend, &seq_cmp_backend);

    EXPECT_CALL(inverse_backend, query_start(_))
    .Times(1);

    NucSequence seq;
    NucSequence delta;
    ICombinatoryRegion* issregion = &ssregion;
    issregion->set_base_sequence(base);

    EXPECT_CALL(inverse_backend, fold_inverse(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::fake_fold_inverse), Return()));

    Score score = issregion->generate(seq, delta);
    EXPECT_EQ(score, 1);

    for (size_t i = 0; i < start; ++i)
    {
        EXPECT_EQ(seq[i], base[i]);
    }

    for (size_t i = 0; i < inverse.length(); ++i)
    {
        EXPECT_EQ(seq[start + i], inverse[i]);
    }

    for (size_t i = end; i < seq.length(); ++i)
    {
        EXPECT_EQ(seq[i], base[i]);
    }
}

TEST_F(SSRegionTest, CheckMutations)
{
    NMutations mutations = 2;
    const size_t times = 210; // 7*3^1 + 21*3^2

    SSRegion ssregion(start, end, wt, va, mutations, .8f, 10, wt_cache, false,
                      &fold_backend, &inverse_backend, &str_cmp_backend, &seq_cmp_backend);

    EXPECT_CALL(inverse_backend, query_start(_))
    .Times(1);

    NucSequence seq;
    NucSequence delta;
    ICombinatoryRegion* issregion = &ssregion;
    issregion->set_base_sequence(base);

    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .Times(times)
    .WillRepeatedly(Return(.5f));

    EXPECT_CALL(fold_backend, fold(_, _, false))
    .Times(times)
    .WillRepeatedly(Invoke(this, &SSRegionTest::fake_fold));

    EXPECT_CALL(inverse_backend, fold_inverse(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::fake_fold_inverse), Return()));

    Score score = issregion->generate(seq, delta);
    EXPECT_EQ(score, 1);
}

TEST_F(SSRegionTest, CheckMutationsStopAsSoonAsFail)
{
    NMutations mutations = 2;
    const size_t times = 212; //7*3^1 + 21*3^2 + 2

    SSRegion ssregion(start, end, wt, va, mutations, .8f, 10, wt_cache, true,
                      &fold_backend, &inverse_backend, &str_cmp_backend, &seq_cmp_backend);

    EXPECT_CALL(inverse_backend, query_start(_))
    .Times(1);

    NucSequence seq;
    NucSequence delta;
    ICombinatoryRegion* issregion = &ssregion;
    issregion->set_base_sequence(base);

    EXPECT_CALL(str_cmp_backend, compare(_, _))
    .Times(times)
    .WillOnce(Return(.5f))
    .WillOnce(Return(.9f)) // stop
    .WillRepeatedly(Return(.5f)); //210 times

    EXPECT_CALL(fold_backend, fold(_, _, true))
    .Times(times)
    .WillRepeatedly(Invoke(this, &SSRegionTest::fake_fold));

    EXPECT_CALL(inverse_backend, fold_inverse(_))
    .Times(2)
    .WillRepeatedly(DoAll(Invoke(this, &SSRegionTest::fake_fold_inverse), Return()));

    Score score = issregion->generate(seq, delta);
    EXPECT_EQ(score, 1);
}

TEST_F(SSRegionTest, CheckCache)
{
    fill_cache();
    SSRegion ssregion(start, end, wt, va, 0, .8f, 4, wt_cache, false,
                      &fold_backend, &inverse_backend, &str_cmp_backend, &seq_cmp_backend);

    EXPECT_CALL(inverse_backend, query_start(_))
    .Times(1);

    NucSequence seq;
    NucSequence delta;
    ICombinatoryRegion* issregion = &ssregion;
    issregion->set_base_sequence(base);

    EXPECT_CALL(seq_cmp_backend, compare(_, _))
    .WillOnce(Return(7))
    .WillOnce(Return(5))
    .WillOnce(Return(6)) // 3 times to check cache
    .WillOnce(Return(4))
    .WillOnce(Return(4))
    .WillOnce(Return(3)); // 3 times to evaluate local score

    EXPECT_CALL(inverse_backend, fold_inverse(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::fake_fold_inverse), Return()));

    Score score = issregion->generate(seq, delta);
    EXPECT_EQ(score, 3. / 4.);
}

TEST_F(SSRegionTest, CheckCacheStopAsSoonAsFail)
{
    fill_cache();
    SSRegion ssregion(start, end, wt, va, 0, .8f, 4, wt_cache, false,
                      &fold_backend, &inverse_backend, &str_cmp_backend, &seq_cmp_backend);

    EXPECT_CALL(inverse_backend, query_start(_))
    .Times(1);

    NucSequence seq;
    NucSequence delta;
    ICombinatoryRegion* issregion = &ssregion;
    issregion->set_base_sequence(base);

    InSequence order;
    EXPECT_CALL(inverse_backend, fold_inverse(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::fake_fold_inverse), Return()));

    EXPECT_CALL(seq_cmp_backend, compare(_, _))
    .WillOnce(Return(7))
    .WillOnce(Return(4));

    EXPECT_CALL(inverse_backend, fold_inverse(_))
    .Times(1)
    .WillOnce(DoAll(Invoke(this, &SSRegionTest::fake_fold_inverse), Return()));

    EXPECT_CALL(seq_cmp_backend, compare(_, _))
    .WillOnce(Return(7))
    .WillOnce(Return(5))
    .WillOnce(Return(6))
    .WillOnce(Return(4))
    .WillOnce(Return(4))
    .WillOnce(Return(3));

    Score score = issregion->generate(seq, delta);
    EXPECT_EQ(score, 3. / 4.);
}