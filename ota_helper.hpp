#ifndef OTA_HELPER_HPP
#define OTA_HELPER_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace ota
{

  namespace datatypes
  {

    struct MPUGetStatusResp
    {
      std::uint16_t task_id;
      std::uint8_t current_status;
    };

    struct MPUUpdateTaskBuildingReq
    {
      std::uint16_t task_id;
      std::string http_server_mac_address;
      std::string http_server_ip_address;
      uint16_t http_port;
      uint64_t package_size;
      uint8_t package_num;
    };

    struct MPUUpdateTaskBuildingResp
    {
      std::uint16_t task_id;
      std::uint8_t building_result;
    };

    struct MPUUpdateStopReq
    {
      std::uint16_t task_id;
      std::uint8_t stop_type;
    };

    struct MPUUpdateStopResp
    {
      std::uint16_t task_id;
      std::uint8_t stop_type;
      std::uint8_t StopResult;
    };

    struct MPUTransmitProgressResp
    {
      std::uint16_t task_id;
      std::uint8_t transmit_result;
      std::uint8_t transmit_percent;
    };

    struct MPUInstallStartResp
    {
      std::uint16_t task_id;
      std::uint8_t start_install_result;
    };

    struct ModuleInstallResult
    {
      std::string module_id;
      std::uint8_t install_detailed_result;
      std::uint8_t module_install_percent;
    };

    struct MPUInstallResultResp
    {
      std::uint16_t task_id;
      std::uint8_t install_result;
      std::uint8_t install_percent;
      std::vector<ModuleInstallResult> module_install_results;
    };

    struct MPUStatusSwitchResp
    {
      std::uint16_t task_id;
      std::uint8_t switch_type;
      std::uint8_t switch_result;
    };

    struct MPUSwitchResultReq
    {
      std::uint16_t task_id;
    };

    struct ModuleSwitchResult
    {
      std::string module_id;
      std::uint8_t switch_detailed_result;
      std::uint8_t module_switch_process_percent;
    };

    struct MPUSwitchResultResp
    {
      std::uint16_t task_id;
      std::uint8_t switch_type;
      std::uint8_t status_switch_result;
      std::uint8_t switch_process_percent;
      std::vector<ModuleSwitchResult> module_switch_results;
    };

  } // namespace datatypes

  class OtaHelper
  {
  public:
    OtaHelper(const OtaHelper &other) = delete;
    OtaHelper &operator=(const OtaHelper &) = delete;

    static OtaHelper &GetInstance()
    {
      static OtaHelper ota_helper;
      return ota_helper;
    };

    bool Start

    bool BldUpdtTask(const datatypes::MPUUpdateTaskBuildingReq &req, datatypes::MPUUpdateTaskBuildingResp &resp,
                     std::uint32_t timeout_ms);

    bool StwrTrsmtPrgs(std::uint16_t task_id, datatypes::MPUTransmitProgressResp &resp,
                       std::uint32_t timeout_ms);

    bool StopUpdt(const datatypes::MPUUpdateStopReq &req, datatypes::MPUUpdateStopReq &resp,  std::uint32_t timeout_ms);

    bool StartInst(std::uint16_t task_id, datatypes::MPUInstallStartResp &resp,
                   std::uint32_t timeout_ms);

    bool ReqInstResult(std::uint16_t task_id, datatypes::MPUInstallResultResp &resp,
                       std::uint32_t timeout_ms);

    bool SwitchABBank(std::uint16_t task_id, datatypes::MPUStatusSwitchResp &resp,
                      std::uint32_t timeout_ms);

    bool GetUpdtTaskStatus(std::uint16_t task_id, datatypes::MPUGetStatusResp &resp,
                           std::uint32_t timeout_ms);

    bool ReqSwitchResult(std::uint16_t task_id, datatypes::MPUSwitchResultResp &resp,
                         std::uint32_t timeout_ms);

  private:
    OtaHelper();
    ~OtaHelper();
  };

} // namespace ota

#endif // OTA_HELPER_HPP
