#include "ota_helper.hpp"

#include <thread>
int main() {
  ota::OtaHelper ota_helper;
  ota_helper.CheckConnection(-1);
  while ( true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  
  return 0;
}
