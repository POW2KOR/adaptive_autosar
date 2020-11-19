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
/**        \file  logging_cfg.h
 *        \brief  TODO
 *
 *      \details  TODO
 *
 *********************************************************************************************************************/

#ifndef SRC_MBITION_APP_PROTOTYPE_CONFIG_LOGGING_CFG_H_
#define SRC_MBITION_APP_PROTOTYPE_CONFIG_LOGGING_CFG_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
namespace mbition_app_prototype {
namespace config {

/// Definition of logging file path as char[] to allow usage of sizeof()
static constexpr const char kLoggingConfigFile[] = "./etc/logging.json";

/// Context IDs
static constexpr const char kContextIdProtoMethodInvocator[] = "MAIN";

static constexpr const char* kLoggerApplicationId{"PROT"};

static constexpr const char* kLoggerApplicationDescription{"Prototype daemon"};

}  // namespace config
}  // namespace calc

#endif  // SRC_MBITION_APP_PROTOTYPE_CONFIG_LOGGING_CFG_H_
