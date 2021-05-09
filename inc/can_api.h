#ifndef __CAN_API_H__
#define __CAN_API_H__

#include "can_interface.h"
#include "can_parsing.h"

#ifdef WIN32 
#include "candle.h"
#include "WinCan.h"
#else
#include "socketcan_if.h"
#endif

#include "canframe.h"


// TODO if for whatever reason the linux user decides not to use can0 as the default device, they will have no way of controlling the route being used, since the constructor defaults to can0. but i doubt this will be an issue, since most people will be using windows
/// @brief: a factory function which returns a new CanInterface * 
///         so the low level code can be completely ignorant of the underlying
///         hardware. 
static CanInterface * NewCanDevice(int baud_rate=500000) {
#ifdef WIN32
  return new WindowsCandleDev(baud_rate);
#elif STUB_CAN
  return new CanInterface();
#else
  return new SocketCanDevice();
#endif
};

#endif