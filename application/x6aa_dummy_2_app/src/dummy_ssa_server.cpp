/*****************************************************************************
 * \file   dummy_ssa_server.cpp
 *
 * \brief  DummySsaServer class representing the ssa server application.
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dummy_ssa_server.h"

namespace application {

#define BODY_STYLES_COUNT 10
uint32_t bodyStyleValues[BODY_STYLES_COUNT] = {163, 200, 250, 100, 155, 111, 222, 99, 165, 50};

using vac::container::operator""_sv;

/*!
 * \brief Initialize DummySsaServer application.
 */
DummySsaServer::DummySsaServer() : ApplicationBase("dummySsa")
{
    std::cerr << "--------------------------" << std::endl;
    log_.LogInfo() << "Dummy SSA server is initializing...";
    std::cerr << "---------1321232-------------" << std::endl;

    // Set up the dummySsaServer sending data to config manager
    ara::core::InstanceSpecifier const dummySsaServerInstanceSpecifier{
        "X6AA_Dummy_SWC_2_Executable/X6AA_Dummy_SWC_2_ExecutableRootSwc/AdaptiveProvidedPortType90"_sv};
    dummySsaServer.emplace(dummySsaServerInstanceSpecifier);
    dummySsaServer->OfferService();
    log_.LogInfo() << "Dummy SSA server is offering services!!";
}

/*!
 * \brief Shutdown DummySsaServer application.
 * \internal
 * - #10 Check if exit was requested by sending SIGTERM or SIGINT.
 * -    #15 Terminate the signal handler thread to shutdown application.
 * - #20 Wait till all threads have joined.
 * \endinternal
 */
DummySsaServer::~DummySsaServer()
{
    // deinitialze the dummySsaServer
    dummySsaServer->StopOfferService();
    dummySsaServer.reset();
}

std::int8_t DummySsaServer::Run()
{
    std::int8_t ret{EXIT_SUCCESS};
    uint64_t count = 0;

    if (!has_initialization_failed_) {
        this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

        log_.LogInfo() << "Dummy SSA server started";

        while (!exit_requested_) {

            std::this_thread::sleep_for(std::chrono::seconds(5));
            dummySsaServer->Ev_CalculationResult.Send(bodyStyleValues[count % BODY_STYLES_COUNT]);
            log_.LogInfo() << "Dummy SSA server has sent an event with body style value = "
                           << bodyStyleValues[count % BODY_STYLES_COUNT];
            count++;
        }

    } else {
        ret = EXIT_FAILURE;
    }

    this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

    return ret;
}

} // namespace application
