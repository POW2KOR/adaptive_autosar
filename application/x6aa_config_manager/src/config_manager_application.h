/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file
 *        \brief  Main class representing the application.
 *
 *      \details  -
 *
 *********************************************************************************************************************/

#ifndef SRC_CONFIG_MANAGER_APPLICATION_H_
#define SRC_CONFIG_MANAGER_APPLICATION_H_



/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "application/common/application_base.h"

#include "persistent_mem_accessor/persistent_mem_accessor.h"
#include "vc_cnfg_mngr_server/vc_cnfg_mngr_server.h"
#include "diagnostic_ssa_client/diagnostic_ssa_client.h"

/*!
 * \brief Namespace for the example application.
 */
namespace application {

using activateSarStorage0131VcEventDataType = ::DataTypes::
    NS_REC_activateSarStorage0131VcEventType_t::REC_activateSarStorage0131VcEventType_t;
using configureSarTriggerEvents0136VcEventDataType
    = ::DataTypes::NS_REC_configureSarTriggerEvents0136VcEventType_t::
        REC_configureSarTriggerEvents0136VcEventType_t;
using vechicleInformation0400VcEventDataType = ::DataTypes::
    NS_REC_vechicleInformation0400VcEventType_t::REC_vechicleInformation0400VcEventType_t;

/*!
 * \brief Main class representing the application.
 * \vprivate Example class for component internal use.
 */
class CnfgMngrApplication : public ApplicationBase {
 public:
  /*!
   * \brief Constructor of class Config Manager Application.
   */
   CnfgMngrApplication();

  /*!
   * \brief Constructor of class Config Manager Application.
   */
   ~CnfgMngrApplication() override;

  /*!
   * \brief Lifecycle method for run mode.
   * \return Error (Exit) code of application.
   */
   virtual std::int8_t Run() override;

 private:
   /*!
     * \brief SI_X6AA_Cnfg_Mngr_Service_ReservedSkeleton service instance
     */
   application::ConfigManagerApp::VcCnfgMngrServer service_reserved_server_;

   /*!
   * \brief SSA Client service instance
   */
   application::ConfigManagerApp::DiagnosticSsaClient ssa_client_;

};

}  // namespace application

#endif  // SRC_CONFIG_MANAGER_APPLICATION_H_
