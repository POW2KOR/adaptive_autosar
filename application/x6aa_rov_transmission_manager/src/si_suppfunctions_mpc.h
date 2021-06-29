/*****************************************************************************
 * \file   si_suppfunctions_mpc.h
 *
 * \brief  ns_suppfunctions_mpc_service_st3 skeleton implementation
 * \author Monica Delgado
 * \date   25-06-2021
 * \note   Based on BROP B1 release
 ******************************************************************************/
#ifndef SRC_SI_SUPPFUNCTIONS_MPC_H_
#define SRC_SI_SUPPFUNCTIONS_MPC_H_


/* C++ system includes */
#include <memory>
#include <thread>

/* Autosar includes */
#include "ara/log/logging.h"
#include "ara/core/instance_specifier.h"


/* Project specific includes */
#include "services/ns_suppfunctions_mpc_service_st3/si_suppfunctions_mpc_service_st3_skeleton.h"

namespace idc6 {
namespace rovservices {

class SISuppFunctionsServer : public services::ns_suppfunctions_mpc_service_st3::skeleton::SI_SuppFunctions_MPC_Service_ST3Skeleton {
 public:

    /*!
     * \brief Constructor.
     */
    explicit SISuppFunctionsServer();

    /*!
     * \brief Destructor.
     */
    ~SISuppFunctionsServer();

 private:
    /*!
     * \brief Service instance identifier.
     */
    static ara::core::InstanceSpecifier const si_suppfunc_instance_specifier_;

};

}  // namespace services
}  // namespace idc6

#endif  // SRC_SI_SUPPFUNCTIONS_MPC_H_
