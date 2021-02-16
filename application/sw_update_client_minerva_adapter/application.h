#ifndef APPLICATION_H
#define APPLICATION_H

#include "mb/swuc/service_interfaces/plugin/swdlplugin_skeleton.h"

namespace Application {

using namespace mb::swuc::service_interfaces::plugin::internal::methods;

class SwUpdateService : public mb::swuc::service_interfaces::plugin::skeleton::SwdlPluginSkeleton {
public:
    explicit SwUpdateService(ara::core::InstanceSpecifier server_port)
        : mb::swuc::service_interfaces::plugin::skeleton::SwdlPluginSkeleton(
              SwdlPluginSkeleton::Preconstruct(server_port).Value())
    {
    }

    ~SwUpdateService() = default;

    // Implementation for all function is not done by purpose
    // Reason is that the implementation is out of the scope
    inline ara::core::Future<Rollback::Output> Rollback() override
    {
        ara::core::Future<Rollback::Output> ret;
        return ret;
    }

    inline ara::core::Future<GetResumePosition::Output> GetResumePosition() override
    {
        ara::core::Future<GetResumePosition::Output> ret;
        return ret;
    }

    inline void CleanUp() override
    {
    }

    inline void Revert() override
    {
    }

    inline ara::core::Future<Verify::Output> Verify() override
    {
        ara::core::Future<Verify::Output> ret;
        return ret;
    }

    inline void Process(
        const std::uint64_t& resumeOffset, const ::mb::swuc::types::ByteVector& file) override
    {
    }

    inline ara::core::Future<Activate::Output> Activate() override
    {
        ara::core::Future<Activate::Output> ret;
        return ret;
    }
};
}; // namespace Application

#endif /* end of include guard: APPLICATION_H */
