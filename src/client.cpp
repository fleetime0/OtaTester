#include "ota_helper.hpp"

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main() {
  ota::OtaHelper ota_helper;
  bool is_conn = ota_helper.CheckConnection(5000);
  if (!is_conn) {
    std::cout << "connection failed!" << std::endl;
    return 0;
  }
  std::cout << "connection successful!" << std::endl;

  std::this_thread::sleep_for(5s);

  ota::datatypes::MPUGetUpdateLogReq update_log_req = {};
  update_log_req.task_id = 2;
  update_log_req.url = "http://172.31.48.2:8080/ota/.log/tmp379kbvfxbbh/IPD";
  ota::datatypes::MPUGetUpdateLogResp update_log_resp = {};
  update_log_resp.task_id = 1111;
  auto res = ota_helper.GetUpdtTaskLog(update_log_req, update_log_resp, 5000);
  if (res != ota::datatypes::ResultStatus::SUCCESS) {
    std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
    return 0;
  }
  std::cout << "GetUpdtTaskLog: task_id: " << static_cast<int>(update_log_resp.task_id)
            << " upload_result: " << static_cast<int>(update_log_resp.upload_result) << std::endl;

  // ota::datatypes::MPUSwitchResultResp switch_result_resp;
  // auto res = ota_helper.ReqSwitchResult(4097, switch_result_resp, 5000);
  // if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //   std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //   return 0;
  // }

  // std::cout << "ReqSwitchResult: task_id: " << static_cast<int>(switch_result_resp.task_id)
  //           << " switch_type: " << static_cast<int>(switch_result_resp.switch_type)
  //           << " status_switch_result: " << static_cast<int>(switch_result_resp.status_switch_result)
  //           << " switch_process_percent: " << static_cast<int>(switch_result_resp.switch_process_percent) <<
  //           std::endl;

  // ota::datatypes::MPUStatusSwitchResp switch_abbank_resp = {};
  // auto res = ota_helper.SwitchABBank(4097, switch_abbank_resp, 5000);

  // if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //   std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //   return 0;
  // }
  // std::cout << "SwitchABBank: task_id: " << static_cast<int>(switch_abbank_resp.task_id)
  //           << " switch_type: " << static_cast<int>(switch_abbank_resp.switch_type)
  //           << " switch_result: " << static_cast<int>(switch_abbank_resp.switch_result) << std::endl;
  // if (switch_abbank_resp.switch_result != 0x00) {
  //   std::cout << "--------------- SwitchABBank failed ---------------" << std::endl;
  // }
  // std::cout << "--------------- SwitchABBank successful! ---------------" << std::endl;

  // ota::datatypes::MPUUpdateStopReq update_stop_req = {};
  // update_stop_req.task_id = 4097;
  // update_stop_req.stop_type = 1;
  // ota::datatypes::MPUUpdateStopResp update_stop_resp = {};
  // auto res = ota_helper.StopUpdt(update_stop_req, update_stop_resp, 5000);
  // if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //   std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //   return 0;
  // }
  // std::cout << "StopUpdt: task_id: " << static_cast<int>(update_stop_resp.task_id)
  //           << " stop_type: " << static_cast<int>(update_stop_resp.stop_type)
  //           << " StopResult: " << static_cast<int>(update_stop_resp.StopResult) << std::endl;
  // if (switch_abbank_req.switch_result != 0x00) {


  // ota::datatypes::MPUUpdateTaskBuildingReq task_building_req = {};
  // task_building_req.task_id = 1111;
  // task_building_req.http_server_ip_address = "172.31.48.2";
  // task_building_req.http_server_mac_address = "02:80:5E:1F:00:02";
  // task_building_req.http_port = 8080;
  // task_building_req.package_size = 2024208699;
  // task_building_req.package_num = 2;
  // ota::datatypes::MPUUpdateTaskBuildingResp task_building_resp = {};
  // auto res = ota_helper.BldUpdtTask(task_building_req, task_building_resp, 5000);
  // if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //   std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //   return 0;
  // }
  // std::cout << "BldUpdtTask: task_id: " << static_cast<int>(task_building_resp.task_id)
  //           << " building_result: " << static_cast<int>(task_building_resp.building_result) << std::endl;
  // if (task_building_resp.building_result != 0x00) {
  //   std::cout << "--------------- BldUpdtTask failed ---------------" << std::endl;
  //   return 0;
  // }
  // std::cout << "--------------- BldUpdtTask successful! ---------------" << std::endl;

  // std::this_thread::sleep_for(5s);

  // ota::datatypes::MPUTransmitProgressResp transmit_progress_resp = {};
  // do {
  //   auto res = ota_helper.StwrTrsmtPrgs(4097, transmit_progress_resp, 5000);
  //   if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //     std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //     return 0;
  //   }
  //   std::cout << "StwrTrsmtPrgs: task_id: " << static_cast<int>(transmit_progress_resp.task_id)
  //             << " transmit_result: " << static_cast<int>(transmit_progress_resp.transmit_result)
  //             << " transmit_percent: " << static_cast<int>(transmit_progress_resp.transmit_percent) << std::endl;
  // } while (transmit_progress_resp.transmit_result == 0x01 && transmit_progress_resp.transmit_percent < 100);
  // std::cout << "StwrTrsmtPrgs: task_id: " << static_cast<int>(transmit_progress_resp.task_id)
  //           << " transmit_result: " << static_cast<int>(transmit_progress_resp.transmit_result)
  //           << " transmit_percent: " << static_cast<int>(transmit_progress_resp.transmit_percent) << std::endl;
  // std::this_thread::sleep_for(1s);
  // if (transmit_progress_resp.transmit_result != 0x00) {
  //   std::cout << "--------------- StwrTrsmtPrgs failed ---------------" << std::endl;
  //   return 0;
  // }
  // std::cout << "--------------- StwrTrsmtPrgs successful! ---------------" << std::endl;

  // std::this_thread::sleep_for(1s);

  // ota::datatypes::MPUGetStatusResp status_resp = {};
  // do {
  //   auto res = ota_helper.GetUpdtTaskStatus(1111, status_resp, 5000);
  //   if (res != ota::datatypes::ResultStatus::SUCCESS) {
  //     std::cout << "vsomeip: error: " << static_cast<int>(res) << std::endl;
  //     return 0;
  //   }
  //   std::cout << "GetUpdtTaskStatus: task_id: " << static_cast<int>(status_resp.task_id)
  //             << " current_status: " << static_cast<int>(status_resp.current_status) << std::endl;
  //   std::this_thread::sleep_for(1s);
  // } while (status_resp.current_status != 0x03);
  // std::cout << "GetUpdtTaskStatus: task_id: " << static_cast<int>(status_resp.task_id)
  //           << " current_status: " << static_cast<int>(status_resp.current_status) << std::endl;
  // if (status_resp.current_status != 0x03) {
  //   std::cout << "--------------- GetUpdtTaskStatus failed ---------------" << std::endl;
  //   return 0;
  // }
  // std::cout << "--------------- GetUpdtTaskStatus successful! ---------------" << std::endl;


  return 0;
}
