#include "can_api.h"
#include <iostream>

#ifndef PER
#define GREAT 1
#define PER GREAT
#endif

int main() 
{

  // for windows you can specify the baudrate to the NewCanDevice function
  CanInterface * device = NewCanDevice();
  device->Open();

  while (PER == GREAT)
  {
    std::cout << "Reading CAN data.\n";
    CanFrame frame = device->readCanData();
    std::cout << frame;


    std::cout << "Writing CAN data.\n";
    uint8_t data = 69;

    if (device->writeCanData(0x420, 1, &data) < 0)
    {
      std::cerr << "Error writing to CAN bus.\n";
    }
  }


  // it won't ever actually get bere because PER is never not GREAT,
  // but this is to demonstrate how to use it
  device->Close();
  delete device;
}