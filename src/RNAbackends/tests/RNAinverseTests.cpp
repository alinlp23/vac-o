#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "RNAinverse.h"
#include "testing/StartProviderMock.h"

using ::testing::Test;
using ::testing::Invoke;

class RNAinverseTest : public Test
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
        NucSequence s("GCACGCGTATGCCGC");
        inv->set_start(s);
    }

    void fake_bad1_provider(IFoldInverse* const inv)
    {
        NucSequence s("GCAA"); //<5
        EXPECT_THROW(inv->set_start(s), RNABackendException);
    }
    void fake_bad2_provider(IFoldInverse* const inv)
    {
        NucSequence s("GCACGCGTATG"); // >=5 && <15
        inv->set_start(s);
    }
    void fake_bad3_provider(IFoldInverse* const inv)
    {
        NucSequence s("GCACGCGTATGCCGCAAGGCCA"); // >15
        inv->set_start(s);
    }
};

TEST_F(RNAinverseTest, FoldInverse)
{
    IFoldInverse* inverse = new RNAinverse(str, 4, 5, 10);

    StartProviderMock provider;
    EXPECT_CALL(provider, get_partial_start(inverse))
    .Times(1)
    .WillOnce(Invoke(this, &RNAinverseTest::fake_provider));


    inverse->query_start(&provider);

    NucSequence expected("GTAGCTTTATGCCGC");

    NucSequence seq;
    inverse->fold_inverse(seq);
    for (size_t i = 0; i < str.size(); ++i)
    {
        EXPECT_EQ(seq[i], expected[i]);
    }

    delete inverse;
}

TEST_F(RNAinverseTest, BadStart1)
{
    IFoldInverse* inverse = new RNAinverse(str, 4, 5, 10);

    StartProviderMock provider;
    EXPECT_CALL(provider, get_partial_start(inverse))
    .Times(1)
    .WillOnce(Invoke(this, &RNAinverseTest::fake_bad1_provider));


    EXPECT_THROW(inverse->query_start(&provider), RNABackendException);

    delete inverse;
}

TEST_F(RNAinverseTest, BadStart2)
{
    IFoldInverse* inverse = new RNAinverse(str, 4, 5, 10);

    StartProviderMock provider;
    EXPECT_CALL(provider, get_partial_start(inverse))
    .Times(1)
    .WillOnce(Invoke(this, &RNAinverseTest::fake_bad2_provider));


    EXPECT_THROW(inverse->query_start(&provider), RNABackendException);

    delete inverse;
}

TEST_F(RNAinverseTest, BadStart3)
{
    IFoldInverse* inverse = new RNAinverse(str, 4, 5, 10);

    StartProviderMock provider;
    EXPECT_CALL(provider, get_partial_start(inverse))
    .Times(1)
    .WillOnce(Invoke(this, &RNAinverseTest::fake_bad3_provider));


    EXPECT_THROW(inverse->query_start(&provider), RNABackendException);

    delete inverse;
}
