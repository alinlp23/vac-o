#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "GCRegion.h"

using ::testing::Test;

class GCRegionTest : public Test
{
    void update_total_expected(string& str)
    {
        NucSequence seq;
        AminoSequence aminos;
        seq = str;
        seq.translate(aminos);
        TripletsIterator triplet_it = GeneticCode::triplets(aminos[0]);
        total_expected *= triplet_it.count();
    }
protected:
    void SetUp()
    {
        string str1 = "CCCTTT";
        string str2 = "AAA";
        string str3 = "GGG";
        base = str1+str2+str3;
        
        total_expected = 1;
        update_total_expected(str2);
        update_total_expected(str3);
        NucSequence seq2 = str2+str3;
        seq2.translate(aminoacids);
        start = 6;
        end = 12;
    }
    size_t total_expected;
    AminoSequence aminoacids;
    NucSequence base;
    SeqIndex start;
    SeqIndex end;
};

TEST_F(GCRegionTest, GenerateDetla)
{
    GCRegion gcregion(start, end, aminoacids);
    ICombinatoryRegion* igcregion = &gcregion;

    NucSequence seq;
    NucSequence delta;

    igcregion->set_base_sequence(base);
    for (size_t j=0; j<total_expected; ++j)
    {
        igcregion->generate(seq, delta);

        for (size_t i=0; i<delta.length(); ++i)
        {
            EXPECT_EQ(seq[start+i], delta[i]);
        }
    }
}

TEST_F(GCRegionTest, DetlaConserveAmino)
{
    GCRegion gcregion(start, end, aminoacids);
    ICombinatoryRegion* igcregion = &gcregion;

    NucSequence seq;
    NucSequence delta;

    igcregion->set_base_sequence(base);
    for (size_t j=0; j<total_expected; ++j)
    {
        igcregion->generate(seq, delta);

        AminoSequence as;
        delta.translate(as);
        EXPECT_EQ(as.size(), aminoacids.size());
        for (size_t i=0; i<as.size(); ++i)
        {
            EXPECT_EQ(as[i], aminoacids[i]);
        }
    }
}

TEST_F(GCRegionTest, ConserveOutOfRegion)
{
    GCRegion gcregion(start, end, aminoacids);
    ICombinatoryRegion* igcregion = &gcregion;

    NucSequence seq;
    NucSequence delta;

    igcregion->set_base_sequence(base);

    for (size_t j=0; j<total_expected; ++j)
    {
        igcregion->generate(seq, delta);

        for (size_t i=0; i<start; ++i)
        {
            EXPECT_EQ(seq[i], base[i]);
        }

        for (size_t i=end; i<seq.length(); ++i)
        {
            EXPECT_EQ(seq[i], base[i]);
        }
    }
}

TEST_F(GCRegionTest, DontRepeatBaseRegion)
{
    GCRegion gcregion(start, end, aminoacids);
    ICombinatoryRegion* igcregion = &gcregion;

    NucSequence seq;
    NucSequence delta;

    igcregion->set_base_sequence(base);

    for (size_t j=0; j<total_expected; ++j)
    {
        igcregion->generate(seq, delta);

        string str_seq;
        string str_base;
        for (size_t i=start; i<end; ++i)
        {
            str_seq += to_str(seq[i]);
            str_base += to_str(base[i]);
        }
        EXPECT_NE(str_seq, str_base);
    }
}
