#ifndef OTA_HELPER_PY_H
#define OTA_HELPER_PY_H

#include <stdint.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#define OTA_HELPER_API __declspec(dllexport)
#else
#define OTA_HELPER_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void *someip_handle;

enum SomeipResultStatus {
  Result_Status_Success,
  Result_Status_Out_Of_Memory,
  Result_Status_Not_Available,
  Result_Status_Connection_Failed,
  Result_Status_Remote_Error,
  Result_Status_Unknown,
  Result_Status_Invalid_Value,
  Result_Status_Subscription_Refused,
  Result_Status_Serialization_Error
};

struct SomeipMPUUpdateTaskBuildingReq {
  uint16_t task_id;
  char *http_server_mac_address;
  char *http_server_ip_address;
  uint16_t http_port;
  uint64_t package_size;
  uint8_t package_num;
};

struct SomeipMPUUpdateTaskBuildingResp {
  uint16_t task_id;
  uint8_t building_result;
};

struct SomeipMPUUpdateStopReq {
  uint16_t task_id;
  uint8_t stop_type;
};

struct SomeipMPUUpdateStopResp {
  uint16_t task_id;
  uint8_t stop_type;
  uint8_t stop_result;
};

struct SomeipMPUTransmitProgressResp {
  uint16_t task_id;
  uint8_t transmit_result;
  uint8_t transmit_percent;
};

struct SomeipMPUInstallStartResp {
  uint16_t task_id;
  uint8_t start_install_result;
};

struct SomeipModuleInstallResult {
  char module_id[512];
  uint8_t install_detailed_result;
  uint8_t module_install_percent;
};

struct SomeipMPUInstallResultResp {
  uint16_t task_id;
  uint8_t install_result;
  uint8_t install_percent;
  uint32_t result_len;
  SomeipModuleInstallResult *module_install_results;
};

struct SomeipMPUStatusSwitchResp {
  uint16_t task_id;
  uint8_t switch_type;
  uint8_t switch_result;
};
struct SomeipMPUGetStatusResp {
  uint16_t task_id;
  uint8_t current_status;
};

struct SomeipModuleSwitchResult {
  char module_id[512];
  uint8_t switch_detailed_result;
  uint8_t module_switch_process_percent;
};
struct SomeipMPUSwitchResultResp {
  uint16_t task_id;
  uint8_t switch_type;
  uint8_t status_switch_result;
  uint8_t switch_process_percent;
  uint16_t result_len;
  SomeipModuleSwitchResult *module_switch_results;
};

OTA_HELPER_API someip_handle someip_create_handle();
OTA_HELPER_API void someip_destroy_handle(someip_handle handle);
OTA_HELPER_API bool check_connection(someip_handle handle, int32_t timeout_ms);
OTA_HELPER_API SomeipResultStatus bldupdt_task(someip_handle handle, const SomeipMPUUpdateTaskBuildingReq *req,
                                               SomeipMPUUpdateTaskBuildingResp *resp, int32_t timeout_ms);

OTA_HELPER_API SomeipResultStatus stop_updt(someip_handle handle, const SomeipMPUUpdateStopReq *req,
                                            SomeipMPUUpdateStopResp *resp, int32_t timeout_ms);

OTA_HELPER_API SomeipResultStatus stwr_trsmt_prgs(someip_handle handle, uint16_t task_id,
                                                  SomeipMPUTransmitProgressResp *resp, int32_t timeout_ms);

OTA_HELPER_API SomeipResultStatus start_inst(someip_handle handle, uint16_t task_id, SomeipMPUInstallStartResp *resp,
                                             int32_t timeout_ms);

OTA_HELPER_API SomeipResultStatus req_inst_result(someip_handle handle, uint16_t task_id,
                                                  SomeipMPUInstallResultResp *resp, int32_t timeout_ms);
OTA_HELPER_API void free_req_inst_result(SomeipMPUInstallResultResp *resp);
OTA_HELPER_API SomeipResultStatus switch_ab_bank(someip_handle handle, uint16_t task_id,
                                                 SomeipMPUStatusSwitchResp *resp, int32_t timeout_ms);

OTA_HELPER_API SomeipResultStatus get_updt_task_status(someip_handle handle, uint16_t task_id,
                                                       SomeipMPUGetStatusResp *resp, int32_t timeout_ms);

OTA_HELPER_API SomeipResultStatus req_switch_result(someip_handle handle, uint16_t task_id,
                                                    SomeipMPUSwitchResultResp *resp, int32_t timeout_ms);
OTA_HELPER_API void free_req_switch_result(SomeipMPUSwitchResultResp *resp);

#ifdef __cplusplus
}
#endif

#endif // OTA_HELPER_PY_H
