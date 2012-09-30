#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#include "TripletsProductor.h"

using std::string;
using ::testing::Test;

class TripletsProductorTest : public Test
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
        total_expected = 1;
        string str1 = "AAA";
        string str2 = "GGG";
        string str3 = "CGA";
        update_total_expected(str1);
        update_total_expected(str2);
        update_total_expected(str3);

        string str = str1 + str2 + str3;
        NucSequence seq = str;
        seq.translate(aminoacids);
    }
    AminoSequence aminoacids;
    size_t total_expected;

    void triplets_to_seq(TripletsProductor::TripletsProduct& triplets, NucSequence& seq)
    {
        string str_seq;
        for (size_t i = 0; i < triplets.size(); ++i)
        {
            str_seq += triplets[i].to_string();
        }
        seq = str_seq;
    }

    void check_aminoacids(NucSequence& seq)
    {
        AminoSequence seq_aminos;
        seq.translate(seq_aminos);
        EXPECT_EQ(aminoacids.size(), seq_aminos.size());
        for (size_t i = 0; i < aminoacids.size(); ++i)
        {
            EXPECT_EQ(aminoacids[i], seq_aminos[i]);
        }
    }
};

TEST_F(TripletsProductorTest, CountTriplets)
{
    TripletsProductor productor(aminoacids);
    TripletsProductor::TripletsProduct p;

    size_t total = 0;
    while (productor.next(p))
        ++total;

    EXPECT_EQ(total_expected, total);
}

TEST_F(TripletsProductorTest, CheckAllTriplets)
{
    TripletsProductor productor(aminoacids);
    TripletsProductor::TripletsProduct p;

    while (productor.next(p))
    {
        NucSequence seq;
        triplets_to_seq(p, seq);
        check_aminoacids(seq);
    }
}

TEST_F(TripletsProductorTest, EmptyAminoSequence)
{
    AminoSequence a;
    TripletsProductor productor(a);
    TripletsProductor::TripletsProduct p;

    EXPECT_TRUE(!productor.next(p));
}