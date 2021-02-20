#ifndef CAN_IF_H
#define CAN_IF_H

#include <string>
#include <map>
#include <exception>
#include <iostream>
#include <vector>
#include <mutex>

// user includes here
#include "canframe.h"
#include "can_exceptions.hpp"


enum CanIfType 
{
  generic_can,
  socket_can,
  windows_can,
};


class CanInterface
{
public:

  CanInterface() {};
  virtual ~CanInterface() {};

  virtual CanFrame readCanData() = 0;
  virtual int16_t writeCanData(uint16_t id, uint8_t dlc, uint8_t * data) = 0;

  virtual CanIfType interfaceType() { return generic_can; };
  
  virtual std::vector<std::string> getDevices() { 
    return std::vector<std::string>(); 
  };
  // strictly have this for windows bullcrap
  // not naming the argument suppresses compiler warnings yay
  virtual void setBaudRate(uint32_t) {};


  // this defeats the purpose of the whole inheritance thing...
  virtual void Open(uint8_t dev_idex=0, uint32_t baud_rate=500000) = 0;
  virtual void Close() = 0;

protected:
  std::mutex read_mtx;
  
};

#endif