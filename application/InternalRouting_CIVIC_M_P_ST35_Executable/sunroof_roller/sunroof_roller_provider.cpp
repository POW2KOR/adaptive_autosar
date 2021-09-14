#include "sunroof_roller_provider.h"

/* C++ system includes */
#include <memory>
#include <string>
#include <utility>

namespace i3 {
namespace services {
namespace common {

using vac::container::operator""_sv;

ara::core::InstanceSpecifier const SunroofRollerProvider::sunroof_roller_instance_specifier_{
        "InternalRouting_CIVIC_M_P_ST35_Executable/"
        "InternalRouting_CIVIC_M_P_ST35_ExecutableRootSwc/"
        "P_TSSR_UI_Ctrl_Rq_Service_ST3"_sv};

SunroofRollerProvider::SunroofRollerProvider() : ::services::ns_tssr_ui_ctrl_rq_service_st3_210::skeleton
  ::TSSR_UI_Ctrl_Rq_Service_ST3_210Skeleton(sunroof_roller_instance_specifier_) {

}

SunroofRollerProvider::~SunroofRollerProvider() {

}
}  // namespace common
}  // namespace services
}  // namespace i3
