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

#ifndef SRC_ROV_APPLICATION_H_
#define SRC_ROV_APPLICATION_H_



/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "application/common/application_base.h"

#include "si_speed_limiter.h"
#include "si_suppfunctions_mpc.h"

/*!
 * \brief Namespace for the example application.
 */
namespace application {

/*!
 * \brief Main class representing the application.
 * \vprivate Example class for component internal use.
 */
class RovApplication : public ApplicationBase {
 public:
  /*!
   * \brief Constructor of class ROV Application.
   */
   RovApplication();

  /*!
   * \brief Constructor of class ROV Application.
   */
   ~RovApplication();

  /*!
   * \brief Lifecycle method for run mode.
   * \return Error (Exit) code of application.
   */
   virtual std::int8_t Run() override;

 private:
   /*!
   * \brief SI SpeedLimiter service instance
   */
   idc6::rovservices::SISpeedlimiter si_speedlimiter_;

  /*!
   * \brief SI SuppFunctions service instance
   */
  idc6::rovservices::SISuppFunctionsServer si_suppfunctions_server_;
};

}  // namespace application

#endif  // SRC_ROV_APPLICATION_H_
