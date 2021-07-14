#include <communicaton_fixture.h>

#include <gtest/gtest.h>

using namespace test;

INSTANTIATE_TEST_CASE_P(
        ReadDidTests,
        CommunicationTestFixture,
        ::testing::Values(
                std::make_tuple(0xF1A1, 0x62) // 0xF1A1(61857) is DID to read and 0x62(98) is the expected response
        ));

TEST_P(CommunicationTestFixture, ReadDidImplementedBySda) {
        uint32_t did_to_read = std::get<0>(GetParam());
        uint8_t expected_response = std::get<1>(GetParam());

        //Init
        Init();

        ASSERT_TRUE(communicator.InitiateSerivceReadDataByIdentifier(did_to_read) == expected_response);
}
