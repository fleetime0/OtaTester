#include "ota_helper_py.h"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#if !defined(ENABLE_TEST)
#include "ota_helper.hpp"
#else

namespace ota {

namespace datatypes {

struct MPUGetStatusResp {
  std::uint16_t task_id;
  std::uint8_t current_status;
};

struct MPUUpdateTaskBuildingReq {
  std::uint16_t task_id;
  std::string http_server_mac_address;
  std::string http_server_ip_address;
  uint16_t http_port;
  uint64_t package_size;
  uint8_t package_num;
};

struct MPUUpdateTaskBuildingResp {
  std::uint16_t task_id;
  std::uint8_t building_result;
};

struct MPUUpdateStopReq {
  std::uint16_t task_id;
  std::uint8_t stop_type;
};

struct MPUUpdateStopResp {
  std::uint16_t task_id;
  std::uint8_t stop_type;
  std::uint8_t StopResult;
};

struct MPUTransmitProgressResp {
  std::uint16_t task_id;
  std::uint8_t transmit_result;
  std::uint8_t transmit_percent;
};

struct MPUInstallStartResp {
  std::uint16_t task_id;
  std::uint8_t start_install_result;
};

struct ModuleInstallResult {
  std::string module_id;
  std::uint8_t install_detailed_result;
  std::uint8_t module_install_percent;
};

struct MPUInstallResultResp {
  std::uint16_t task_id;
  std::uint8_t install_result;
  std::uint8_t install_percent;
  std::vector<ModuleInstallResult> module_install_results;
};

struct MPUStatusSwitchResp {
  std::uint16_t task_id;
  std::uint8_t switch_type;
  std::uint8_t switch_result;
};

struct MPUSwitchResultReq {
  std::uint16_t task_id;
};

struct ModuleSwitchResult {
  std::string module_id;
  std::uint8_t switch_detailed_result;
  std::uint8_t module_switch_process_percent;
};

struct MPUSwitchResultResp {
  std::uint16_t task_id;
  std::uint8_t switch_type;
  std::uint8_t status_switch_result;
  std::uint8_t switch_process_percent;
  std::vector<ModuleSwitchResult> module_switch_results;
};

enum class ResultStatus {
  SUCCESS,
  OUT_OF_MEMORY,
  NOT_AVAILABLE,
  CONNECTION_FAILED,
  REMOTE_ERROR,
  UNKNOWN,
  INVALID_VALUE,
  SUBSCRIPTION_REFUSED,
  SERIALIZATION_ERROR
};

} // namespace datatypes

class OtaHelper {
public:
  OtaHelper() { std::cout << "OtaHelper::OtaHelper\n"; }
  ~OtaHelper() { std::cout << "OtaHelper::~OtaHelper\n"; }

  bool CheckConnection(std::int32_t timeout_ms) {
    std::cout << timeout_ms << "===OtaHelper::CheckConnection\n";
    return true;
  }

  datatypes::ResultStatus
  BldUpdtTask(const datatypes::MPUUpdateTaskBuildingReq &req,
              datatypes::MPUUpdateTaskBuildingResp &resp,
              std::int32_t timeout_ms) {
    {
      std::cout << "OtaHelper::BldUpdtTask\n";
      resp.task_id = req.task_id;
      resp.building_result = 0X11;
      return datatypes::ResultStatus::SUCCESS;
    }
  }

  // /**
  //  * @brief 获取传输进度
  //  * @param task_id OTA任务ID
  //  * @param resp 软件包传输进度
  //  * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
  //  * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
  //  */
  datatypes::ResultStatus
  StwrTrsmtPrgs(std::uint16_t task_id, datatypes::MPUTransmitProgressResp &resp,
                std::int32_t timeout_ms) {

    std::cout << "OtaHelper::StwrTrsmtPrgs\n";
    resp.transmit_percent = 0x01;
    resp.transmit_result = 0X11;
    resp.task_id = task_id;

    return datatypes::ResultStatus::SUCCESS;
  }

  // /**
  //  * @brief 停止OTA任务
  //  * @param req 流程终止请求
  //  * @param resp 流程终止应答
  //  * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
  //  * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
  //  */
  datatypes::ResultStatus StopUpdt(const datatypes::MPUUpdateStopReq &req,
                                   datatypes::MPUUpdateStopResp &resp,
                                   std::int32_t timeout_ms) {
    std::cout << "OtaHelper::StopUpdt\n";
    resp.stop_type = 0x01;
    resp.StopResult = 0X11;
    resp.task_id = req.task_id;

    return datatypes::ResultStatus::SUCCESS;
  }

  // /**
  //  * @brief 开始安装
  //  * @param task_id OTA任务ID
  //  * @param resp 安装开始应答
  //  * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
  //  * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
  //  */
  datatypes::ResultStatus StartInst(std::uint16_t task_id,
                                    datatypes::MPUInstallStartResp &resp,
                                    std::int32_t timeout_ms) {
    std::cout << "OtaHelper::StartInst\n";
    resp.start_install_result = 0X11;
    resp.task_id = task_id;

    return datatypes::ResultStatus::SUCCESS;
  }

  // /**
  //  * @brief 获取安装结果
  //  * @param task_id OTA任务ID
  //  * @param resp 安装结果应答
  //  * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
  //  * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
  //  */
  datatypes::ResultStatus ReqInstResult(std::uint16_t task_id,
                                        datatypes::MPUInstallResultResp &resp,
                                        std::int32_t timeout_ms) {
    std::cout << "OtaHelper::ReqInstResult\n";
    resp.install_result = 0X11;
    resp.install_percent = 0X11;
    resp.task_id = task_id;

    return datatypes::ResultStatus::SUCCESS;
  }

  // /**
  //  * @brief 开始切换 AB 分区
  //  * @param task_id OTA任务ID
  //  * @param resp AB切面应答
  //  * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
  //  * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
  //  */
  datatypes::ResultStatus SwitchABBank(std::uint16_t task_id,
                                       datatypes::MPUStatusSwitchResp &resp,
                                       std::int32_t timeout_ms) {
    std::cout << "OtaHelper::SwitchABBank\n";
    resp.switch_result = 0X11;
    resp.switch_type = 0X11;
    resp.task_id = task_id;

    return datatypes::ResultStatus::SUCCESS;
  }

  // /**
  //  * @brief 获取当前OTA升级任务状态
  //  * @param task_id OTA任务ID
  //  * @param resp 升级状态应答
  //  * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
  //  * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
  //  */
  datatypes::ResultStatus GetUpdtTaskStatus(std::uint16_t task_id,
                                            datatypes::MPUGetStatusResp &resp,
                                            std::int32_t timeout_ms) {
    std::cout << "OtaHelper::GetUpdtTaskStatus\n";
    resp.current_status = 0X11;
    resp.task_id = task_id;

    return datatypes::ResultStatus::SUCCESS;
  }

  // /**
  //  * @brief 获取分区切换结果
  //  * @param task_id OTA任务ID
  //  * @param resp AB切面结果应答
  //  * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
  //  * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
  //  */
  datatypes::ResultStatus ReqSwitchResult(std::uint16_t task_id,
                                          datatypes::MPUSwitchResultResp &resp,
                                          std::int32_t timeout_ms) {
    std::cout << "OtaHelper::ReqSwitchResult\n";

    resp.task_id = task_id;
    resp.switch_type = 0X11;
    resp.status_switch_result = 0X11;
    resp.switch_process_percent = 0X11;

    return datatypes::ResultStatus::SUCCESS;
  }
};
} // namespace ota
#endif

someip_handle someip_create_handle(const char *instance, uint32_t len) {
  if(instance==nullptr || len==0)
  {
    return new ota::OtaHelper();
  }
  return new ota::OtaHelper(std::string(instance,len));
}
void someip_destroy_handle(someip_handle handle) {
  if (handle != nullptr) {
    delete static_cast<ota::OtaHelper *>(handle);
  }
}
bool check_connection(someip_handle handle, int32_t timeout_ms) {
  return static_cast<ota::OtaHelper *>(handle)->CheckConnection(timeout_ms);
}
SomeipResultStatus bldupdt_task(someip_handle handle,
                                const SomeipMPUUpdateTaskBuildingReq *req,
                                SomeipMPUUpdateTaskBuildingResp *resp,
                                int32_t timeout_ms) {

  ota::datatypes::MPUUpdateTaskBuildingReq tempreq{
      req->task_id,
      std::string(req->http_server_mac_address),
      std::string(req->http_server_ip_address),
      req->http_port,
      req->package_size,
      req->package_num,
  };
  ota::datatypes::MPUUpdateTaskBuildingResp tempres;

  auto result = static_cast<ota::OtaHelper *>(handle)->BldUpdtTask(
      tempreq, tempres, timeout_ms);

  resp->building_result = tempres.building_result;
  resp->task_id = tempres.task_id;
  return static_cast<SomeipResultStatus>(result);
}

SomeipResultStatus stop_updt(someip_handle handle,
                             const SomeipMPUUpdateStopReq *req,
                             SomeipMPUUpdateStopResp *resp,
                             int32_t timeout_ms) {
  ota::datatypes::MPUUpdateStopReq tempreq{req->task_id, req->stop_type};
  ota::datatypes::MPUUpdateStopResp tempres;

  auto result = static_cast<ota::OtaHelper *>(handle)->StopUpdt(
      tempreq, tempres, timeout_ms);

  resp->stop_type = tempres.stop_type;
  resp->stop_result = tempres.StopResult;
  resp->task_id = tempres.task_id;

  return static_cast<SomeipResultStatus>(result);
}

SomeipResultStatus stwr_trsmt_prgs(someip_handle handle, uint16_t task_id,
                                   SomeipMPUTransmitProgressResp *resp,
                                   int32_t timeout_ms) {
  ota::datatypes::MPUTransmitProgressResp tempres;

  auto result = static_cast<ota::OtaHelper *>(handle)->StwrTrsmtPrgs(
      task_id, tempres, timeout_ms);

  resp->transmit_result = tempres.transmit_result;
  resp->transmit_percent = tempres.transmit_percent;
  resp->task_id = tempres.task_id;

  return static_cast<SomeipResultStatus>(result);
}

SomeipResultStatus start_inst(someip_handle handle, uint16_t task_id,
                              SomeipMPUInstallStartResp *resp,
                              int32_t timeout_ms) {
  ota::datatypes::MPUInstallStartResp tempres;

  auto result = static_cast<ota::OtaHelper *>(handle)->StartInst(
      task_id, tempres, timeout_ms);

  resp->start_install_result = tempres.start_install_result;
  resp->task_id = tempres.task_id;

  return static_cast<SomeipResultStatus>(result);
}

SomeipResultStatus req_inst_result(someip_handle handle, uint16_t task_id,
                                   SomeipMPUInstallResultResp *resp,
                                   int32_t timeout_ms) {
  ota::datatypes::MPUInstallResultResp tempres;

  auto result = static_cast<ota::OtaHelper *>(handle)->ReqInstResult(
      task_id, tempres, timeout_ms);

  resp->task_id = tempres.task_id;
  resp->install_result = tempres.install_result;
  resp->install_percent = tempres.install_percent;

  if (tempres.module_install_results.empty()) {
    // resp->module_install_results = nullptr;
    resp->result_len = 0;
  } else {
    resp->result_len = tempres.module_install_results.size();

    if (resp->result_len>MAX_RESULT_ARRAY_LEN)
    {
      resp->result_len=MAX_RESULT_ARRAY_LEN;
    }

    for (std::uint32_t i = 0; i < resp->result_len; ++i) {

      auto &dest = resp->module_install_results[i];
      auto &src = tempres.module_install_results[i];

      std::memcpy(dest.module_id, src.module_id.data(), src.module_id.size());
      dest.module_id[src.module_id.size()] = '\0';

      dest.install_detailed_result = src.install_detailed_result;
      dest.module_install_percent = src.module_install_percent;
    }
  }

  return static_cast<SomeipResultStatus>(result);
}
// void free_req_inst_result(SomeipMPUInstallResultResp *resp) {
//   if (resp == nullptr || resp->result_len == 0 ||
//       resp->module_install_results == nullptr) {
//     return;
//   }
//   delete[] resp->module_install_results;
// }

SomeipResultStatus switch_ab_bank(someip_handle handle, SomeipMPUStatusSwitchReq *req, SomeipMPUStatusSwitchResp *resp,
                                  int32_t timeout_ms) {
  ota::datatypes::MPUStatusSwitchReq tempreq{req->task_id, req->switch_type};
                                
  ota::datatypes::MPUStatusSwitchResp tempres;

  auto result = static_cast<ota::OtaHelper *>(handle)->SwitchABBank(tempreq, tempres, timeout_ms);

  resp->switch_result = tempres.switch_result;
  resp->switch_type = tempres.switch_type;
  resp->task_id = tempres.task_id;

  return static_cast<SomeipResultStatus>(result);
}

SomeipResultStatus get_updt_task_status(someip_handle handle, uint16_t task_id,
                                        SomeipMPUGetStatusResp *resp,
                                        int32_t timeout_ms) {
  ota::datatypes::MPUGetStatusResp tempres;

  auto result = static_cast<ota::OtaHelper *>(handle)->GetUpdtTaskStatus(
      task_id, tempres, timeout_ms);

  resp->current_status = tempres.current_status;
  resp->task_id = tempres.task_id;

  return static_cast<SomeipResultStatus>(result);
}

SomeipResultStatus req_switch_result(someip_handle handle, uint16_t task_id,
                                     SomeipMPUSwitchResultResp *resp,
                                     int32_t timeout_ms) {
  ota::datatypes::MPUSwitchResultResp tempres;

  auto result = static_cast<ota::OtaHelper *>(handle)->ReqSwitchResult(
      task_id, tempres, timeout_ms);

  resp->task_id = tempres.task_id;
  resp->switch_type = tempres.switch_type;
  resp->status_switch_result = tempres.status_switch_result;
  resp->switch_process_percent = tempres.switch_process_percent;

  if (tempres.module_switch_results.empty()) {
    // resp->module_switch_results = nullptr;
    resp->result_len = 0;
  } else {
    resp->result_len = tempres.module_switch_results.size();
    // resp->module_switch_results =
    //     new SomeipModuleSwitchResult[resp->result_len];

    if (resp->result_len>MAX_RESULT_ARRAY_LEN)
    {
      resp->result_len=MAX_RESULT_ARRAY_LEN;
    }

    for (std::int32_t i = 0; i < resp->result_len; ++i) {

      auto &dest = resp->module_switch_results[i];
      auto &src = tempres.module_switch_results[i];

      std::memcpy(dest.module_id, src.module_id.data(), src.module_id.size());
      dest.module_id[src.module_id.size()] = '\0';

      dest.switch_detailed_result = src.switch_detailed_result;
      dest.module_switch_process_percent = src.module_switch_process_percent;
    }
  }

  return static_cast<SomeipResultStatus>(result);
}
// void free_req_switch_result(SomeipMPUSwitchResultResp *resp) {
//   if (resp == nullptr || resp->result_len == 0 ||
//       resp->module_switch_results == nullptr) {
//     return;
//   }
//   delete[] resp->module_switch_results;
// }

SomeipResultStatus get_updt_task_log(someip_handle handle,SomeipMPUGetUpdateLogReq *req, SomeipMPUGetUpdateLogResp*resp, int32_t timeout_ms)
{
  ota::datatypes::MPUGetUpdateLogReq tempreq{
      req->task_id,
      std::string(req->url,req->url_len)
  };

  ota::datatypes::MPUGetUpdateLogResp tempres;
  auto result = static_cast<ota::OtaHelper *>(handle)->GetUpdtTaskLog(
      tempreq, tempres, timeout_ms);

  resp->upload_result = tempres.upload_result;
  resp->task_id = tempres.task_id;

  return static_cast<SomeipResultStatus>(result);
}
