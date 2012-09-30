#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "INFORNA.h"
#include "testing/StartProviderMock.h"

using ::testing::Test;
using ::testing::Invoke;

class INFORNATest : public Test
{
protected:
    SecStructure str;
    NucSequence s;
    void SetUp()
    {
        str = "(..((.....))..)";
    }
public:
    void fake_provider(IFoldInverse* const inv)
    {
        string str = "GCACGCGTATGCCGC";
        s = str;
        inv->set_start(s);
    }

    void fake_bad1_provider(IFoldInverse* const inv)
    {
        string str = "GCAA"; //<5
        s = str;
        EXPECT_THROW(inv->set_start(s), RNABackendException);
    }
    void fake_bad2_provider(IFoldInverse* const inv)
    {
        string str = "GCACGCGTATG"; // >=5 && <15
        s = str;
        inv->set_start(s);
    }
    void fake_bad3_provider(IFoldInverse* const inv)
    {
        string str = "GCACGCGTATGCCGCAAGGCCA"; // >15
        s = str;
        inv->set_start(s);
    }
};

TEST_F(INFORNATest, FoldInverse)
{
    IFoldInverse* inverse = new INFORNA(str, 4, 5, 10);

    StartProviderMock provider;
    EXPECT_CALL(provider, get_partial_start(inverse))
    .Times(1)
    .WillOnce(Invoke(this, &INFORNATest::fake_provider));


    inverse->query_start(&provider);

    string e = "GTAGCTTTATGCCGC";
    NucSequence expected = e;

    NucSequence seq;
    inverse->fold_inverse(seq);
    for (size_t i = 0; i < str.size(); ++i)
    {
        EXPECT_EQ(seq[i], expected[i]);
    }

    delete inverse;
}

TEST_F(INFORNATest, BadStart1)
{
    IFoldInverse* inverse = new INFORNA(str, 4, 5, 10);

    StartProviderMock provider;
    EXPECT_CALL(provider, get_partial_start(inverse))
    .Times(1)
    .WillOnce(Invoke(this, &INFORNATest::fake_bad1_provider));


    EXPECT_THROW(inverse->query_start(&provider), RNABackendException);

    delete inverse;
}

TEST_F(INFORNATest, BadStart2)
{
    IFoldInverse* inverse = new INFORNA(str, 4, 5, 10);

    StartProviderMock provider;
    EXPECT_CALL(provider, get_partial_start(inverse))
    .Times(1)
    .WillOnce(Invoke(this, &INFORNATest::fake_bad2_provider));


    EXPECT_THROW(inverse->query_start(&provider), RNABackendException);

    delete inverse;
}

TEST_F(INFORNATest, BadStart3)
{
    IFoldInverse* inverse = new INFORNA(str, 4, 5, 10);

    StartProviderMock provider;
    EXPECT_CALL(provider, get_partial_start(inverse))
    .Times(1)
    .WillOnce(Invoke(this, &INFORNATest::fake_bad3_provider));


    EXPECT_THROW(inverse->query_start(&provider), RNABackendException);

    delete inverse;
}
