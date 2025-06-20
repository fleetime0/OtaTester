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

} // namespace ota
