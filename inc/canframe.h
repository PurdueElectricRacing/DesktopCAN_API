#ifndef __CAN_FRAME_H__
#define __CAN_FRAME_H__

#include <iostream>

#include "can_exceptions.h"

#ifdef WIN32
#include "candle.h"
#endif

#define EXTENDED_ID_FLAG 0x80000000
#define EXTENDED_ID_MASK 0x1FFFFFFF
#define STANDARD_ID_MASK 0x7FF

// wrapper for the struct can_frame to allow for the = operator to be
// used for assignment
struct CanFrame
{
  CanFrame()
  {
    can_id = 0xFFFFFFFF;
    can_dlc = 0;
    padding = 0;
    reserve0 = 0;
    reserve1 = 0;
    timestamp_us = 0;
  };

  CanFrame(const CanFrame & frame);

  // do nothing since there's no nested pointers
  virtual ~CanFrame() {};

  uint32_t can_id;
  uint8_t can_dlc;
  uint8_t padding;
  uint8_t reserve0;
  uint8_t reserve1;
  uint8_t data[8];
  uint32_t timestamp_us;
  
  bool validFrame() { return can_id != 0xFFFFFFFF; };

  uint32_t getId() {
      if (can_id > 0x7FF)
      {
        return can_id & ~EXTENDED_ID_FLAG;
      }
      return can_id;
  };

#ifdef WIN32
  CanFrame &operator=(const candle_frame_t f);
#else
  CanFrame &operator=(const struct can_frame &frame);
#endif
  CanFrame &operator=(const CanFrame &frame);
};

std::ostream &operator<<(std::ostream &out, const CanFrame &frame);


#endif
