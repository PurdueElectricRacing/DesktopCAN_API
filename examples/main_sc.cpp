#include "can_api.h"
#include <iostream>

#ifndef PER
#define GREAT 1
#define PER GREAT
#endif

int main() 
{
  std::cout << "MAKE SURE YOU HAVE RUN THE 'setup_can.sh' SCRIPT BEFORE TRYING THIS CODE. This will crash from an exception being thrown since it won't be able to connect to the interface.\n";

  CanInterface * device = NewCanDevice();
  device->Open();

  while (PER == GREAT)
  {
    CanFrame frame = device->readCanData();
    std::cout << frame;

    uint8_t data = 69;
    if (device->writeCanData(0x420, 1, &data) < 0)
    {
      std::cerr << "Error writing to CAN bus.\n";
    }  
  }
}