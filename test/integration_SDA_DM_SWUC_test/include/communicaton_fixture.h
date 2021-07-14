#ifndef COMMUNICATION_TEST_FIXTURE_H
#define COMMUNICATION_TEST_FIXTURE_H

#include <tuple>

#include <gtest/gtest.h>

#include <communication.h>

namespace test
{
class CommunicationTestFixture : public ::testing::TestWithParam<std::tuple<uint32_t, uint8_t>> {
protected:
    void Init()
    {
        //Open the connection with DM
        ASSERT_FALSE(communicator.OpenConnectionWithDiagnosticManager());

        //Send the Routing activation request
        communicator.InitiateRoutingActivation();
    }

    test::Communication communicator;
};
}
#endif  //COMMUNICATION_TEST_FIXTURE_H
