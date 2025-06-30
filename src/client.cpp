#include "ota_helper.hpp"

#include <iostream>
#include <thread>

int main() {
  ota::OtaHelper ota_helper;
  bool is_conn = ota_helper.CheckConnection(5000);
  if (!is_conn) {
    std::cout << "connection failed!" << std::endl;
    return 0;
  }
  std::cout << "connection successful!" << std::endl;

  // ota::datatypes::MPUUpdateTaskBuildingReq task_building_req = {};
  // task_building_req.task_id = 110;
  // task_building_req.http_server_ip_address = "172.31.48.2";
  // task_building_req.http_server_mac_address = "00:1c:42:88:88:c4";
  // task_building_req.http_port = 80;
  // task_building_req.package_size = 2162688;
  // task_building_req.package_num = 1;
  // ota::datatypes::MPUUpdateTaskBuildingResp task_building_resp = {};
  // auto res = ota_helper.BldUpdtTask(task_building_req, task_building_resp, 1000);
  // if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //   std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //   return 0;
  // }
  // std::cout << "BldUpdtTask: task_id: " << task_building_resp.task_id
  //           << "building_result: " << task_building_resp.building_result << std::endl;
  // if (task_building_resp.building_result != 0x00) {
  //   return 0;
  // }

  // ota::datatypes::MPUTransmitProgressResp transmit_progress_resp = {};
  // do {
  //   auto res = ota_helper.StwrTrsmtPrgs(110, transmit_progress_resp, 1000);
  //   if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //     std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //     return 0;
  //   }
  //   std::cout << "StwrTrsmtPrgs: task_id: " << transmit_progress_resp.task_id
  //             << "transmit_result: " << transmit_progress_resp.transmit_result
  //             << "transmit_percent: " << transmit_progress_resp.transmit_percent << std::endl;
  // } while (transmit_progress_resp.transmit_result == 0x01 && transmit_progress_resp.transmit_percent < 100);
  // if (transmit_progress_resp.transmit_result != 0x00) {
  //   return 0;
  // }

  // ota::datatypes::MPUGetStatusResp status_resp = {};
  // do {
  //   auto res = ota_helper.GetUpdtTaskStatus(110, status_resp, 1000);
  //   if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //     std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //     return 0;
  //   }
  //   std::cout << "GetUpdtTaskStatus: task_id: " << status_resp.task_id
  //             << "current_status: " << status_resp.current_status << std::endl;
  // } while (status_resp.current_status == 0x02);
  // if (status_resp.current_status != 0x03) {
  //   return 0;
  // }

  return 0;
}
