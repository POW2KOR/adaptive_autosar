#include "ara/com/types.h"
#include "ara/exec/result.h"
#include <string>


namespace mbition {
namespace use_case_1 {

/**
 * Initialize the ara::com stack for the use-case.
 */
void initialize(const std::string& cfg_path);

ara::com::FindServiceHandle start_find_service();

bool service_found(void);

void stop_find_service(const ara::com::FindServiceHandle& find_service_handle);

void deinitialize(void);

} // namespace use_case_1
} // namespace mbition