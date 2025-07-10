#ifndef OTA_HELPER_HPP
#define OTA_HELPER_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(__CYGWIN__)
#define OTA_HELPER_API __declspec(dllexport)
#else
#define OTA_HELPER_API
#endif

namespace v1 {
namespace commonapi {
namespace ota {
template<typename... _AttributeExtensions>
class FOTAMPUUpdateProxy;

} // namespace ota
} // namespace commonapi
} // namespace v1

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

struct MPUStatusSwitchReq {
  std::uint16_t task_id;
  std::uint8_t switch_type;
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

struct MPUGetUpdateLogReq {
  std::uint16_t task_id;
  std::string url;
};

struct MPUGetUpdateLogResp {
  std::uint16_t task_id;
  std::uint8_t upload_result;
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

class OTA_HELPER_API OtaHelper {
  public:
  OtaHelper();

// IPD: commonapi.ota.FOTAMPUUpdate; RIPD: commonapi.ota.FOTAMPUUpdate1
  OtaHelper(const std::string &instance);
  ~OtaHelper() = default;

  /**
   * @brief 检查服务连接是否建立
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return true 表示已连接；false 表示连接失败或超时
   */
  bool CheckConnection(std::int32_t timeout_ms);

  /**
   * @brief 开始OTA升级任务
   * @param req 升级任务建立请求
   * @param resp 升级任务建立响应
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus BldUpdtTask(const datatypes::MPUUpdateTaskBuildingReq &req,
                                      datatypes::MPUUpdateTaskBuildingResp &resp, std::int32_t timeout_ms);

  /**
   * @brief 获取传输进度
   * @param task_id OTA任务ID
   * @param resp 软件包传输进度
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus StwrTrsmtPrgs(std::uint16_t task_id, datatypes::MPUTransmitProgressResp &resp,
                                        std::int32_t timeout_ms);

  /**
   * @brief 停止OTA任务
   * @param req 流程终止请求
   * @param resp 流程终止应答
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus StopUpdt(const datatypes::MPUUpdateStopReq &req, datatypes::MPUUpdateStopResp &resp,
                                   std::int32_t timeout_ms);

  /**
   * @brief 开始安装
   * @param task_id OTA任务ID
   * @param resp 安装开始应答
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus StartInst(std::uint16_t task_id, datatypes::MPUInstallStartResp &resp,
                                    std::int32_t timeout_ms);

  /**
   * @brief 获取安装结果
   * @param task_id OTA任务ID
   * @param resp 安装结果应答
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus ReqInstResult(std::uint16_t task_id, datatypes::MPUInstallResultResp &resp,
                                        std::int32_t timeout_ms);

  /**
   * @brief 开始切换 AB 分区
   * @param task_id OTA任务ID
   * @param resp AB切面应答
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus SwitchABBank(const datatypes::MPUStatusSwitchReq &req, datatypes::MPUStatusSwitchResp &resp,
                                       std::int32_t timeout_ms);

  /**
   * @brief 获取当前OTA升级任务状态
   * @param task_id OTA任务ID
   * @param resp 升级状态应答
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus GetUpdtTaskStatus(std::uint16_t task_id, datatypes::MPUGetStatusResp &resp,
                                            std::int32_t timeout_ms);

  /**
   * @brief 获取分区切换结果
   * @param task_id OTA任务ID
   * @param resp AB切面结果应答
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus ReqSwitchResult(std::uint16_t task_id, datatypes::MPUSwitchResultResp &resp,
                                          std::int32_t timeout_ms);

  /**
   * @brief 获取日志
   * @param task_id OTA任务ID
   * @param url 被升级MCU传输日志的url（http post）
   * @param resp 获取日志应答
   * @param timeout_ms 超时时间（毫秒）；-1 表示无限等待
   * @return ResultStatus::SUCCESS 表示传输，其它值表示错误类型
   */
  datatypes::ResultStatus GetUpdtTaskLog(const datatypes::MPUGetUpdateLogReq &req, datatypes::MPUGetUpdateLogResp &resp,
                                         std::int32_t timeout_ms);

  private:
  std::shared_ptr<v1::commonapi::ota::FOTAMPUUpdateProxy<>> proxy_;
};

} // namespace ota

#endif // OTA_HELPER_HPP
