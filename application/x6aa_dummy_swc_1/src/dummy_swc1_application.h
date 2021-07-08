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

#ifndef SRC_DUMMY_SWC1_APPLICATION_H_
#define SRC_DUMMY_SWC1_APPLICATION_H_



/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "application/common/application_base.h"
#include "variant_coding_consumer.h"

/*!
 * \brief Namespace for the example application.
 */
namespace application {

/*!
 * \brief Main class representing the application.
 * \vprivate Example class for component internal use.
 */
class DummySwc1Application : public ApplicationBase {
 public:
  /*!
   * \brief Constructor of class Dummy SWC1 Application.
   */
   DummySwc1Application();

  /*!
   * \brief Constructor of class Dummy SWC1 Application.
   */
   ~DummySwc1Application();

  /*!
   * \brief Lifecycle method for run mode.
   * \return Error (Exit) code of application.
   */
   virtual std::int8_t Run() override;

 private:
   /*!
     * \brief Variant coding consumer instance
     */
   application::VariantCodingConsumer vc_consumer_;
};

}  // namespace application

#endif  // SRC_DUMMY_SWC1_APPLICATION_H_
