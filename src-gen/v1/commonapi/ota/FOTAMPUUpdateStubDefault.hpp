/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.2.15.v202410041619.
* Used org.franca.core 0.13.1.201807231814.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_COMMONAPI_OTA_FOTAMPU_Update_STUB_DEFAULT_HPP_
#define V1_COMMONAPI_OTA_FOTAMPU_Update_STUB_DEFAULT_HPP_


#include <CommonAPI/Export.hpp>

#include <v1/commonapi/ota/FOTAMPUUpdateStub.hpp>
#include <cassert>
#include <sstream>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v1 {
namespace commonapi {
namespace ota {

/**
 * Provides a default implementation for FOTAMPUUpdateStubRemoteEvent and
 * FOTAMPUUpdateStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class COMMONAPI_EXPORT_CLASS_EXPLICIT FOTAMPUUpdateStubDefault
    : public virtual FOTAMPUUpdateStub {
public:
    COMMONAPI_EXPORT FOTAMPUUpdateStubDefault()
        : remoteEventHandler_(this),
          interfaceVersion_(FOTAMPUUpdate::getInterfaceVersion()) {
    }

    COMMONAPI_EXPORT const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
        (void)_client;
        return interfaceVersion_;
    }

    COMMONAPI_EXPORT FOTAMPUUpdateStubRemoteEvent* initStubAdapter(const std::shared_ptr< FOTAMPUUpdateStubAdapter> &_adapter) {
        CommonAPI::Stub<FOTAMPUUpdateStubAdapter, FOTAMPUUpdateStubRemoteEvent>::stubAdapter_ = _adapter;
        return &remoteEventHandler_;
    }

    COMMONAPI_EXPORT virtual void BldUpdtTask(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _MPUUpdateTaskBuildingReq, BldUpdtTaskReply_t _reply) {
        (void)_client;
        (void)_MPUUpdateTaskBuildingReq;
        FOTAMPUUpdate::MPUUpdateTaskBuildingResp MPUUpdateTaskBuildingResp = {};
        _reply(MPUUpdateTaskBuildingResp);
    }
    COMMONAPI_EXPORT virtual void StwrTrsmtPrgs(const std::shared_ptr<CommonAPI::ClientId> _client, uint16_t _MPUTransmitProgressReq, StwrTrsmtPrgsReply_t _reply) {
        (void)_client;
        (void)_MPUTransmitProgressReq;
        std::string MPUTransmitProgressResp = "";
        _reply(MPUTransmitProgressResp);
    }
    COMMONAPI_EXPORT virtual void StopUpdt(const std::shared_ptr<CommonAPI::ClientId> _client, FOTAMPUUpdate::MPUUpdateStopReq _MPUUpdateStopReq, StopUpdtReply_t _reply) {
        (void)_client;
        (void)_MPUUpdateStopReq;
        FOTAMPUUpdate::MPUUpdateStopResp MPUUpdateStopResp = {};
        _reply(MPUUpdateStopResp);
    }
    COMMONAPI_EXPORT virtual void StartInst(const std::shared_ptr<CommonAPI::ClientId> _client, uint16_t _MPUInstallStartReq, StartInstReply_t _reply) {
        (void)_client;
        (void)_MPUInstallStartReq;
        FOTAMPUUpdate::MPUInstallStartResp MPUInstallStartResp = {};
        _reply(MPUInstallStartResp);
    }
    COMMONAPI_EXPORT virtual void ReqInstResult(const std::shared_ptr<CommonAPI::ClientId> _client, uint16_t _MPUInstallResultReq, ReqInstResultReply_t _reply) {
        (void)_client;
        (void)_MPUInstallResultReq;
        std::string MPUInstallResultResp = "";
        _reply(MPUInstallResultResp);
    }
    COMMONAPI_EXPORT virtual void SwitchABBank(const std::shared_ptr<CommonAPI::ClientId> _client, FOTAMPUUpdate::MPUStatusSwitchReq _MPUStatusSwitchReq, SwitchABBankReply_t _reply) {
        (void)_client;
        (void)_MPUStatusSwitchReq;
        FOTAMPUUpdate::MPUStatusSwitchResp MPUStatusSwitchResp = {};
        _reply(MPUStatusSwitchResp);
    }
    COMMONAPI_EXPORT virtual void GetUpdtTaskStatus(const std::shared_ptr<CommonAPI::ClientId> _client, uint16_t _MPUGetStatusReq, GetUpdtTaskStatusReply_t _reply) {
        (void)_client;
        (void)_MPUGetStatusReq;
        FOTAMPUUpdate::MPUGetStatusResp MPUGetStatusResp = {};
        _reply(MPUGetStatusResp);
    }
    COMMONAPI_EXPORT virtual void ReqSwitchResult(const std::shared_ptr<CommonAPI::ClientId> _client, uint16_t _MPUSwitchResultReq, ReqSwitchResultReply_t _reply) {
        (void)_client;
        (void)_MPUSwitchResultReq;
        std::string MPUSwitchResultResp = "";
        _reply(MPUSwitchResultResp);
    }
    COMMONAPI_EXPORT virtual void GetUpdtTaskLog(const std::shared_ptr<CommonAPI::ClientId> _client, FOTAMPUUpdate::MPUGetUpdateLogReq _MPUGetUpdateLogReq, GetUpdtTaskLogReply_t _reply) {
        (void)_client;
        (void)_MPUGetUpdateLogReq;
        FOTAMPUUpdate::MPUGetUpdateLogResp MPUGetUpdateLogResp = {};
        _reply(MPUGetUpdateLogResp);
    }


protected:
    class COMMONAPI_EXPORT_CLASS_EXPLICIT RemoteEventHandler: public virtual FOTAMPUUpdateStubRemoteEvent {
    public:
        COMMONAPI_EXPORT RemoteEventHandler(FOTAMPUUpdateStubDefault *_defaultStub)
            : 
              defaultStub_(_defaultStub) {
        }


    private:
        FOTAMPUUpdateStubDefault *defaultStub_;
    };
protected:
    FOTAMPUUpdateStubDefault::RemoteEventHandler remoteEventHandler_;

private:


    CommonAPI::Version interfaceVersion_;
};

} // namespace ota
} // namespace commonapi
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_COMMONAPI_OTA_FOTAMPU_Update_STUB_DEFAULT
