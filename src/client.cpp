#include "ota_helper.hpp"

#include <iostream>
#include <thread>

int main() {
  ota::OtaHelper ota_helper;
  ota_helper.CheckConnection(-1);

  std::cout << "connection successful!" << std::endl;

  ota::datatypes::MPUUpdateTaskBuildingReq task_building_req = {};
  task_building_req.task_id = 110;
  task_building_req.http_server_ip_address = "172.31.48.2";
  task_building_req.http_server_mac_address = "00:1c:42:88:88:c4";
  task_building_req.http_port = 80;
  task_building_req.package_size = 2162688;
  task_building_req.package_num = 1;

  ota::datatypes::MPUUpdateTaskBuildingResp task_building_resp = {};
  auto res = ota_helper.BldUpdtTask(task_building_req, task_building_resp, 1000);
  if (res != ota::datatypes::ResultStatus::SUCCESS) {
    std::cout << "error: " << static_cast<int>(res) << std::endl;
  }

  std::cout << "resp: tasck_id: " << task_building_resp.task_id
            << "building_result: " << task_building_resp.building_result << std::endl;

  return 0;
}
