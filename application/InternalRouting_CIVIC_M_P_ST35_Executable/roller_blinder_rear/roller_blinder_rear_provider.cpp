#include "roller_blinder_rear_provider.h"

/* C++ system includes */
#include <memory>
#include <string>
#include <utility>

namespace i3 {
namespace services {
namespace common {

using vac::container::operator""_sv;

ara::core::InstanceSpecifier const RollerBlinderRearProvider::rb_rear_instance_specifier_{
        "InternalRouting_CIVIC_M_P_ST35_Executable/"
        "InternalRouting_CIVIC_M_P_ST35_ExecutableRootSwc/"
        "P_RollerBlindRear_UI_Ctrl_HU_Service_ST3"_sv};

RollerBlinderRearProvider::RollerBlinderRearProvider() : ::services::ns_rollerblindrear_ui_ctrl_hu_service_st3::skeleton
  ::RollerBlindRear_UI_Ctrl_HU_Service_ST3Skeleton(rb_rear_instance_specifier_) {

}

RollerBlinderRearProvider::~RollerBlinderRearProvider() {

}
}  // namespace common
}  // namespace services
}  // namespace i3
