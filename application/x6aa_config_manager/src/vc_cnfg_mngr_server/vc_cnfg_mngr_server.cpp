/*****************************************************************************
 * \file   vc_cnfg_mngr_server.cpp
 *
 * \brief  VVcCnfgMngrServer class representing the variant coding server application.
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vc_cnfg_mngr_server.h"

#include "x6aa_config_manager_error_domain.h"

namespace application {

namespace ConfigManagerApp {

using vac::container::operator""_sv;

ara::core::InstanceSpecifier const VcCnfgMngrServer::server_instance_specifier_{
  "X6AA_Cnfg_Mngr_Executable/"
  "X6AA_Cnfg_Mngr_ExecutableRootSwc/"
  "AdaptiveProvidedPortType89"_sv};

/*!
 * \brief Initialize VcCnfgMngrServer application.
 */
VcCnfgMngrServer::VcCnfgMngrServer() : services::ns_si_cnfg_mngr_to_dummyswc::
  skeleton::SI_X6AA_Cnfg_Mngr_Service_ReservedSkeleton(server_instance_specifier_) {
  // Empty
}

VcCnfgMngrServer::~VcCnfgMngrServer() {
  // Empty
}

} // namespace ConfigManagerApp

} // namespace application
