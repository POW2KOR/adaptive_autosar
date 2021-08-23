/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Mercedes Benz. All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  avatar_router/src/stubs/ara_com_Runtime_stub.cpp
 *        \brief  Provides stubbed functions for ara::core::Runtime
 *
 *      \details  Provides stubbed functions for ara::core::Runtime
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *********************************************************************************************************************/

#include <cstdlib>
#include <string>

#include "amsr/application_base/initialization_error_domain.h"
#include "amsr/generic/write_std_stream.h"
#include "amsr/log/internal/lifecycle.h"
#include "amsr/socal/internal/lifecycle.h"
#include "ara/core/initialization.h"
#include "vac/internal/lifecycle.h"


namespace ara {
namespace com {

bool g_ara_core_initialized{false};
bool g_ara_core_deinitialized{false};

// Stubbed Runtime class
class Runtime {

  public:
    Runtime() {}
    void InitializeBindings();
    void StartBindings();
    void DeinitializeBindings();
};

void ara::com::Runtime::InitializeBindings() {
}

void ara::com::Runtime::StartBindings() {
}

void ara::com::Runtime::DeinitializeBindings() {
}

}
}  // namespace details

