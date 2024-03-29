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

#ifndef AVATAR_ROUTER_APPLICATION_H_
#define AVATAR_ROUTER_APPLICATION_H_



/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "application/common/application_base.h"

#include "roller_blinder_rear/roller_blinder_rear_provider.h"
#include "roller_blinder_rear/roller_blinder_rear_consumer.h"

#include "sunroof_roller/sunroof_roller_ctrl.h"
#include "sunroof_roller/sunroof_roller_provider.h"

/*!
 * \brief Namespace for the example application.
 */
namespace application {

/*!
 * \brief Main class representing the application.
 * \vprivate Example class for component internal use.
 */
class Application : public ApplicationBase {
 public:
  /*!
   * \brief Constructor of class Application.
   */
   Application();

  /*!
   * \brief Constructor of class Application.
   */
   ~Application();

  /*!
   * \brief Lifecycle method for run mode.
   * \return Error (Exit) code of application.
   */
   virtual std::int8_t Run() override;

 private:
   /*!
   * \brief Rear Roller Blinder service instance on vlan10
   */
   i3::services::common::RollerBlinderRearProvider roller_blinder_service_provider_;

   /*!
   * \brief Rear Roller Blinder service instance on vlan210
   */
   i3::services::common::RollerBlinderRearConsumer roller_blinder_service_consumer_;

  /*!
   * \brief sunroof service instance
   */
  i3::services::common::SunroofRollerConsumer sunroof_roller_service_app_proxy_;

  /*!
   * \brief sunroof roller provider instance
   */
  i3::services::common::SunroofRollerProvider sunroof_roller_provider_;
  
};

}  // namespace application

#endif  // AVATAR_ROUTER_APPLICATION_H_
