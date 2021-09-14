
#ifndef ROLLER_BLINDER_REAR_PROVIDER_H_
#define ROLLER_BLINDER_REAR_PROVIDER_H_

#include <ara/log/logging.h>
#include <thread>

#include "ara/core/instance_specifier.h"

#include "services/ns_rollerblindrear_ui_ctrl_hu_service_st3/rollerblindrear_ui_ctrl_hu_service_st3_skeleton.h"
#include "services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3.h"


namespace i3 {
namespace services {
namespace common {

 class RollerBlinderRearProvider : public ::services::ns_rollerblindrear_ui_ctrl_hu_service_st3::skeleton::RollerBlindRear_UI_Ctrl_HU_Service_ST3Skeleton {
 public:

    /*!
     * \brief Constructor.
     */
    explicit RollerBlinderRearProvider();

    /*!
     * \brief Destructor.
     */
    ~RollerBlinderRearProvider();

 private:
    /*!
     * \brief Service instance identifier.
     */
    static ara::core::InstanceSpecifier const rb_rear_instance_specifier_;

};

}  // namespace common
}  // namespace services
}  // namespace i3

#endif  // ROLLER_BLINDER_REAR_PROVIDER_H_
