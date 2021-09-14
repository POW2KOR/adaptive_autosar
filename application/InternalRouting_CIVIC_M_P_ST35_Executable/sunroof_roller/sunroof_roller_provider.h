
#ifndef SUNROOF_ROLLER_PROVIDER_H_
#define SUNROOF_ROLLER_PROVIDER_H_

#include <memory>
#include "ara/log/logging.h"
#include "ara/core/instance_specifier.h"

#include "services/ns_tssr_ui_ctrl_rq_service_st3_210/tssr_ui_ctrl_rq_service_st3_210_skeleton.h"

namespace i3 {
namespace services {
namespace common {

class SunroofRollerProvider : public ::services::ns_tssr_ui_ctrl_rq_service_st3_210::skeleton::TSSR_UI_Ctrl_Rq_Service_ST3_210Skeleton {
 public:

    /*!
     * \brief Constructor.
     */
    explicit SunroofRollerProvider();

    /*!
     * \brief Destructor.
     */
    ~SunroofRollerProvider();

 private:
    /*!
     * \brief Service instance identifier.
     */
    static ara::core::InstanceSpecifier const sunroof_roller_instance_specifier_;

};

}  // namespace common
}  // namespace services
}  // namespace i3

#endif  // SUNROOF_ROLLER_PROVIDER_H_
