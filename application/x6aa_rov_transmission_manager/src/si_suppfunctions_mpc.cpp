
/*****************************************************************************
 * \file   si_speedlimiter.cpp
 *
 * \brief  ns_speedlimiter proxy implementation
 * \author Monica Delgado
 * \date   25-06-2021
 * \note   Based on BROP B1 release
 ******************************************************************************/

#include "si_suppfunctions_mpc.h"

/* C system includes */

/* C++ system includes */
#include <memory>
#include <string>
#include <utility>

namespace idc6 {
namespace rovservices {

using vac::container::operator""_sv;

ara::core::InstanceSpecifier const SISuppFunctionsServer::si_suppfunc_instance_specifier_{
        "TransmissionManager_ROVExecutable/"
        "TransmissionManager_ROVExecutableRootSwc/"
        "P_CamSensSoil"_sv};

SISuppFunctionsServer::SISuppFunctionsServer() : services::ns_suppfunctions_mpc_service_st3::skeleton
  ::SI_SuppFunctions_MPC_Service_ST3Skeleton(si_suppfunc_instance_specifier_) {

}

SISuppFunctionsServer::~SISuppFunctionsServer() {

}

}  // namespace rovservices
}  // namespace idc6
