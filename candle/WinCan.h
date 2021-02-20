#ifndef __WINDERS_CAN_API_H__
#define __WINDERS_CAN_API_H__

#include <candle.h>
#include <string>
#include <vector>

#include "can_interface.h"


enum WindowsCandleError_t
{
  win_can_no_error,
  win_can_no_devices,
  win_can_close_error,
  win_can_open_error,
  win_can_start_error,
  win_can_read_error,
  win_can_send_error,
  win_can_device_error,
  win_can_timing_error,
  win_can_unknown_error,
  win_can_timeout_error,
};


/// @note: The candle api technically allows for multiple channels, but it would
///        seem that the CANable only has 1 channel. So this code will just auto
///        open channel 0, and will be hardcoded. Should this ever change for 
///        whatever reason, here is your alert.

class WindowsCandleDev : public CanInterface
{
public:
  WindowsCandleDev(uint32_t baud_rate = 500000) : baud(baud_rate) {
    devlist = 0;
    getDevices();
  };

  virtual ~WindowsCandleDev() { 
    candle_dev_close(hdev);
    candle_dev_free(hdev);
    candle_list_free(devlist); 
  };

  virtual std::vector<std::string> getDevices();
  virtual void Open(uint8_t dev_idx=0, uint32_t baud_rate=500000);
  virtual void Close();
  virtual void setBaudRate(uint32_t rate);
  virtual CanFrame readCanData();
  virtual int16_t writeCanData(uint16_t id, uint8_t dlc, uint8_t * data);



private:

  uint32_t baud;
  candle_handle hdev;
  candle_list_handle devlist;
};


// TODO operator= for candle_frame_t from canframe struct
// TODO operator= for canframe from candle_frame_t
#endif