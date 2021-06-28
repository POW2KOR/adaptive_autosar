/*****************************************************************************
 * \file   vc_cnfg_mngr_server.h
 *
 * \brief  VDummySsaServer class representing the ssa server application.
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/

#ifndef SRC_VC_CNFG_MNGR_SERVER_H_
#define SRC_VC_CNFG_MNGR_SERVER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_skeleton.h"
#include "application/common/application_base.h"

#include <csignal>
#include <iostream>
#include <thread>

/*!
 * \brief Namespace for the example application.
 */
namespace application {

/*!
 * \brief Main class representing the DummySsaServer.
 * \vprivate Example class for component internal use.
 */
class DummySsaServer final : public ApplicationBase {
public:
    /*!
     * \brief Constructor of class DummySsaServer.
     */
    DummySsaServer();

    /*!
     * \brief Deleted copy constructor
     */
    DummySsaServer(DummySsaServer const&) = delete;

    /*!
     * \brief Default move constructor
     */
    DummySsaServer(DummySsaServer&& other) noexcept = delete;

    /*!
     * \brief Destructor of class DummySsaServer.
     */
    ~DummySsaServer();

    /*!
     * \brief Deleted copy assignment operator
     * \return Reference to application
     */
    DummySsaServer& operator=(DummySsaServer const&) & = delete;

    /*!
     * \brief Default move assignment operator
     * \return Reference to application
     */
    DummySsaServer& operator=(DummySsaServer&& other) & = delete;

    /*!
     * \brief Lifecycle method for run mode.
     * \return Error (Exit) code of application.
     */
    std::int8_t Run();

private:
    /*!
     * \brief SI_X6AA_Dummy_B2_Service_ReservedSkeleton
     */
    ara::core::Optional<services::ns_si_dummyswc_2_to_cnfg_mngr::skeleton::
                            SI_X6AA_Dummy_B2_Service_ReservedSkeleton>
        dummySsaServer;
};

} // namespace application

#endif // SRC_VC_CNFG_MNGR_SERVER_H_
