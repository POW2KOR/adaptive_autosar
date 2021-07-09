/*****************************************************************************
 * \file   vc_cnfg_mngr_server.h
 *
 * \brief  VVcCnfgMngrServer class representing the variant coding server application.
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/

#ifndef SRC_VC_CNFG_MNGR_SERVER_H_
#define SRC_VC_CNFG_MNGR_SERVER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_skeleton.h"


/*!
 * \brief Namespace for the example application.
 */
namespace application {

namespace ConfigManagerApp {

/*!
 * \brief Main class representing the VcCnfgMngrServer.
 * \vprivate Example class for component internal use.
 */
class VcCnfgMngrServer : public services::ns_si_cnfg_mngr_to_dummyswc::skeleton::SI_X6AA_Cnfg_Mngr_Service_ReservedSkeleton {
public:
    /*!
     * \brief Constructor of class VcCnfgMngrServer.
     */
    explicit VcCnfgMngrServer();

    /*!
     * \brief Destructor of class VcCnfgMngrServer.
     */
    ~VcCnfgMngrServer();

private:
    /*!
     * \brief Service instance identifier.
     */
    static ara::core::InstanceSpecifier const server_instance_specifier_;
};

} // namespace ConfigManagerApp

} // namespace application

#endif // SRC_VC_CNFG_MNGR_SERVER_H_
