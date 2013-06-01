#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fstream>
#include <list>
#include <string>

#include "biopp/biopp.h"
#include "mili/mili.h"
#include "vaco-libplugin/SequenceMutator.h"

using std::string;
using std::list;
using std::ifstream;
using ::testing::Test;
using namespace mili;
/*
class SequenceMutatorTest : public Test
{
protected:
    void SetUp()
    {
        string str = "AAA";
        seq = biopp::NucSequence(str);
        ifstream mutations_expected("libplugin/testing/mutations-expected.txt");//TODO: not found
        bool eof(false);
        while (!eof)
        {
            string m;
            getline(mutations_expected, m);
            eof = mutations_expected.eof();
            if (!eof)
                insert_into(expected, m);
        }
    }
    biopp::NucSequence seq;
    biopp::NucSequence empty;
    list<string> expected;

    void seq_to_str(biopp::NucSequence& sequence, string& str_seq)
    {
        for (size_t i = 0; i < sequence.length(); ++i)
        {
            str_seq += sequence[i].as_char();
        }
    }
    void check_all(SequenceMutator& mutator)
    {
        biopp::NucSequence mutated;

        CAutonomousIterator<list<string> > it(expected);
        while (mutator.next(mutated))
        {
            string str_seq;
            seq_to_str(mutated, str_seq);
            EXPECT_EQ(str_seq, *it);
            ++it;
        }
        EXPECT_TRUE(it.end());
    }
};

TEST_F(SequenceMutatorTest, FromNucSequence)
{
    SequenceMutator mutator(seq, 2);
    check_all(mutator);
}

TEST_F(SequenceMutatorTest, FromSize)
{
    SequenceMutator mutator(3, 2);
    mutator.begin(seq);
    check_all(mutator);
}

TEST_F(SequenceMutatorTest, FromWrongSize)
{
    SequenceMutator mutator(5, 2);
    EXPECT_THROW(mutator.begin(seq), PluginException);
}

TEST_F(SequenceMutatorTest, TooMuchMutations)
{
    EXPECT_THROW(SequenceMutator mutator(seq, 4), fideo::CombinatorException);
}

TEST_F(SequenceMutatorTest, FromEmptySeq)
{
    EXPECT_THROW(SequenceMutator mutator(empty, 2), fideo::CombinatorException);
}

TEST_F(SequenceMutatorTest, ZeroMutations)
{
    SequenceMutator mutator(seq, 0);
    NucSequence mutated;
    EXPECT_TRUE(!mutator.next(mutated));
}

TEST_F(SequenceMutatorTest, ReInitialization)
{
    SequenceMutator mutator(3, 2);
    mutator.begin(seq);
    check_all(mutator);

    mutator.begin(seq);
    check_all(mutator);
}

*/