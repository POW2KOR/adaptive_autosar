
#ifndef SUNROOF_ROLLER_CTRL_H_
#define SUNROOF_ROLLER_CTRL_H_

#include <memory>
#include "ara/log/logging.h"
#include "ara/core/instance_specifier.h"

#include "services/ns_tssr_ui_ctrl_rq_service_st3/tssr_ui_ctrl_rq_service_st3_proxy.h"

namespace i3 {
namespace services {
namespace common {

using sunroofRollerType = ::services::ns_tssr_ui_ctrl_rq_service_st3::proxy::TSSR_UI_Ctrl_Rq_Service_ST3Proxy;
using sunroofDataType = ::PSI_4234_TSSR_UI_Ctrl_Rq_Service_ST3_10::REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj
                ::REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj;

class SunroofRollerConsumer {
public:
  SunroofRollerConsumer();

  ~SunroofRollerConsumer();

  /*
   * \brief Check if Sunroof Roller service has been found.
   *
   * This method will stop the FindService if this has been found.
   *
   * \return  true   when success, false otherwise.
   */
  bool CheckAndStopFindService();

  /*
   * \brief Subscribe to service events and register handler for events.
   *
   * \retval  true   Success
   * \retval  false  Failure
   */
  static bool SubscribeToEvents();

  /*
   * \brief Unsubscribe from service events.
   *
   * \retval  true   Success
   * \retval  false  Failure
   */
  static bool UnsubscribeFromEvents();

  /*!
   * \brief Get if the service has been found.
   *
   * \return true when service found, false otherwise.
   */
  static bool IsServiceFound();

  /*!
   * \brief Get if it subscribed successfully to the service.
   *
   * \return true when subscribed, false otherwise.
   */
  static bool IsSubscribed();

  static void GetValues();

  static sunroofDataType data_;
  
private:
  static void
  FindServiceHandler(ara::com::ServiceHandleContainer<::services::
    ns_tssr_ui_ctrl_rq_service_st3::proxy::TSSR_UI_Ctrl_Rq_Service_ST3Proxy::HandleType> sunroof_roller_services);

  static void TSSR_UI_Ctrl_Rq_ST3EventHandler();

  static ara::log::Logger& GetLogger();

  /** Pointer to the bound service */
  static std::shared_ptr<::services::ns_tssr_ui_ctrl_rq_service_st3::proxy::
  TSSR_UI_Ctrl_Rq_Service_ST3Proxy> sunroof_roller_service_proxy_;

  /*!
   * \brief Flag that a service has been found.
   */
  static std::atomic<bool> sunroof_roller_service_instance_found_;
  /*!
   * \brief Flag that events have been subsribed.
   */
  static std::atomic<bool> sunroof_roller_events_subscribed_;
  /*!
   * \brief Find service handler instance.
   */
  ara::com::FindServiceHandle find_service_handle_;

};

}  // namespace common
}  // namespace services
}  // namespace i3

#endif  // SUNROOF_ROLLER_CTRL_H_
