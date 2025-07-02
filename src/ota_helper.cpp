#include "ota_helper.hpp"

#include <chrono>
#include <thread>

#include "CommonAPI/CommonAPI.hpp"
#include "nlohmann/json.hpp"
#include "v1/commonapi/ota/FOTAMPUUpdateProxy.hpp"

using namespace std::chrono_literals;
using namespace v1::commonapi::ota;


#include <iostream>
namespace ota {

OtaHelper::OtaHelper() {
  auto runtime = CommonAPI::Runtime::get();
  proxy_ = runtime->buildProxy<FOTAMPUUpdateProxy>("local", "commonapi.ota.FOTAMPUUpdate");
  std::cout << "Hello World!" << std::endl;
}

bool OtaHelper::CheckConnection(std::int32_t timeout_ms) {
  if (timeout_ms == -1) {
    return proxy_->isAvailableBlocking();
  }

  using clock = std::chrono::steady_clock;
  auto start = clock::now();
  auto timeout = std::chrono::milliseconds(timeout_ms);

  while (clock::now() - start < timeout) {
    if (proxy_->isAvailable()) {
      return true;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  return false;
}

datatypes::ResultStatus OtaHelper::BldUpdtTask(const datatypes::MPUUpdateTaskBuildingReq &req,
                                               datatypes::MPUUpdateTaskBuildingResp &resp, std::int32_t timeout_ms) {
  nlohmann::json j;
  j["taskID"] = req.task_id;
  j["httpSeverMACaddress"] = req.http_server_mac_address;
  j["httpServerIPaddress"] = req.http_server_ip_address;
  j["httpPort"] = req.http_port;
  j["packageSize"] = req.package_size;
  j["packageNum"] = req.package_num;
  j["activateType"] = 1;
  j["logLevel"] = 4;
  j["extendedParameters"] = nlohmann::json::array();
  std::string local_req = j.dump();

  CommonAPI::CallStatus call_status;

  FOTAMPUUpdate::MPUUpdateTaskBuildingResp local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;

  proxy_->BldUpdtTask(local_req, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    resp.task_id = local_resp.getTaskID();
    resp.building_result = local_resp.getBuildingResult();
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

datatypes::ResultStatus OtaHelper::StwrTrsmtPrgs(std::uint16_t task_id, datatypes::MPUTransmitProgressResp &resp,
                                                 std::int32_t timeout_ms) {
  CommonAPI::CallStatus call_status;

  std::string local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;
  proxy_->StwrTrsmtPrgs(task_id, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    nlohmann::json j = nlohmann::json::parse(local_resp);
    resp.task_id = j["taskID"].get<std::uint16_t>();
    resp.transmit_result = j["transmitResult"].get<std::uint8_t>();
    resp.transmit_percent = j["transmitPercent"].get<std::uint8_t>();
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

datatypes::ResultStatus OtaHelper::StopUpdt(const datatypes::MPUUpdateStopReq &req, datatypes::MPUUpdateStopResp &resp,
                                            std::int32_t timeout_ms) {
  FOTAMPUUpdate::MPUUpdateStopReq local_req;
  local_req.setTaskID(req.task_id);
  local_req.setStopType(req.stop_type);

  CommonAPI::CallStatus call_status;

  FOTAMPUUpdate::MPUUpdateStopResp local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;
  proxy_->StopUpdt(local_req, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    resp.task_id = local_resp.getTaskID();
    resp.stop_type = local_resp.getStopType();
    resp.StopResult = local_resp.getStopResult();
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

datatypes::ResultStatus OtaHelper::StartInst(std::uint16_t task_id, datatypes::MPUInstallStartResp &resp,
                                             std::int32_t timeout_ms) {
  CommonAPI::CallStatus call_status;

  FOTAMPUUpdate::MPUInstallStartResp local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;
  proxy_->StartInst(task_id, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    resp.task_id = local_resp.getTaskID();
    resp.start_install_result = local_resp.getStartInstallResult();
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

datatypes::ResultStatus OtaHelper::ReqInstResult(std::uint16_t task_id, datatypes::MPUInstallResultResp &resp,
                                                 std::int32_t timeout_ms) {
  CommonAPI::CallStatus call_status;

  std::string local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;
  proxy_->ReqInstResult(task_id, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    nlohmann::json j = nlohmann::json::parse(local_resp);
    resp.task_id = j["taskID"].get<std::uint16_t>();
    resp.install_result = j["installResult"].get<std::uint8_t>();
    resp.install_percent = j["installPercent"].get<std::uint8_t>();
    for (const auto &module_install_result: j["moduleInstallResults"]) {
      datatypes::ModuleInstallResult local_module_install_result;
      local_module_install_result.module_id = module_install_result["moduleID"].get<std::string>();
      local_module_install_result.install_detailed_result =
              module_install_result["installDetailedResult"].get<std::uint8_t>();
      local_module_install_result.module_install_percent =
              module_install_result["moduleInstallPercent"].get<std::uint8_t>();
      resp.module_install_results.push_back(local_module_install_result);
    }
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

datatypes::ResultStatus OtaHelper::SwitchABBank(std::uint16_t task_id, datatypes::MPUStatusSwitchResp &resp,
                                                std::int32_t timeout_ms) {
  FOTAMPUUpdate::MPUStatusSwitchReq local_req;
  local_req.setTaskID(task_id);
  local_req.setSwitchType(1);

  CommonAPI::CallStatus call_status;

  FOTAMPUUpdate::MPUStatusSwitchResp local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;
  proxy_->SwitchABBank(local_req, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    resp.task_id = local_resp.getTaskID();
    resp.switch_type = local_resp.getSwitchType();
    resp.switch_result = local_resp.getSwitchResult();
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

datatypes::ResultStatus OtaHelper::GetUpdtTaskStatus(std::uint16_t task_id, datatypes::MPUGetStatusResp &resp,
                                                     std::int32_t timeout_ms) {
  CommonAPI::CallStatus call_status;

  FOTAMPUUpdate::MPUGetStatusResp local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;
  proxy_->GetUpdtTaskStatus(task_id, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    resp.task_id = local_resp.getTaskID();
    resp.current_status = local_resp.getCurrentStatus();
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

datatypes::ResultStatus OtaHelper::ReqSwitchResult(std::uint16_t task_id, datatypes::MPUSwitchResultResp &resp,
                                                   std::int32_t timeout_ms) {
  CommonAPI::CallStatus call_status;

  std::string local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;
  proxy_->ReqSwitchResult(task_id, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    nlohmann::json j = nlohmann::json::parse(local_resp);
    resp.task_id = j["taskID"].get<std::uint16_t>();
    resp.switch_type = j["switchType"].get<std::uint8_t>();
    resp.status_switch_result = j["statusSwitchResult"].get<std::uint8_t>();
    resp.switch_process_percent = j["switchProcessPercent"].get<std::uint8_t>();
    for (const auto &module_switch_result: j["moduleSwitchResults"]) {
      datatypes::ModuleSwitchResult local_module_switch_result;
      local_module_switch_result.module_id = module_switch_result["moduleID"].get<std::string>();
      local_module_switch_result.switch_detailed_result =
              module_switch_result["switchDetailedResult"].get<std::uint8_t>();
      local_module_switch_result.module_switch_process_percent =
              module_switch_result["moduleSwitchProcessPercent"].get<std::uint8_t>();
      resp.module_switch_results.push_back(local_module_switch_result);
    }
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

datatypes::ResultStatus OtaHelper::GetUpdtTaskLog(const datatypes::MPUGetUpdateLogReq &req,
                                                  datatypes::MPUGetUpdateLogResp &resp, std::int32_t timeout_ms) {
  FOTAMPUUpdate::MPUGetUpdateLogReq local_req;
  local_req.setTaskID(req.task_id);
  local_req.setUrl(req.url);

  CommonAPI::CallStatus call_status;

  FOTAMPUUpdate::MPUGetUpdateLogResp local_resp;

  CommonAPI::CallInfo info;
  info.timeout_ = timeout_ms;
  proxy_->GetUpdtTaskLog(local_req, call_status, local_resp, &info);

  if (call_status == CommonAPI::CallStatus::SUCCESS) {
    resp.task_id = local_resp.getTaskID();
    resp.upload_result = local_resp.getUploadResult();
  }

  return static_cast<datatypes::ResultStatus>(call_status);
}

} // namespace ota
