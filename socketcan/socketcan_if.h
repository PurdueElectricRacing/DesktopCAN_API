#ifndef __SOCKET_CAN_H__
#define __SOCKET_CAN_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <asm/sockios.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "canframe.h"
#include "can_interface.h"

/// @note: see https://www.kernel.org/doc/Documentation/networking/can.txt for
///        for info on the socketCAN api


class SocketCanDevice : public CanInterface
{
public:

  // Using CAN_RAW sockets is extensively comparable to the commonly
  //     known access to CAN character devices.To meet the new possibilities
  //         provided by the multi user SocketCAN approach,
  //     some reasonable
  //             defaults are set at RAW socket binding time :

  //     -The filters are set to exactly one filter receiving everything -
  //     The socket only receives valid data frames(= > no error message 
  //     frames) - The loopback of sent CAN frames is enabled(see chapter 3.2) 
  //     - The socket does not receive its own sent frames(in loopback mode)

  // these values can be changed to test stuff but i'm not sure how to use the 
  // BCM protocol so it probably won't be changed


  SocketCanDevice(int type = SOCK_RAW, int protocol = CAN_RAW, 
                  int enable_own_messages = 0, std::string ifname = "can0");
  virtual ~SocketCanDevice() { close(can_socket_fd); };

  virtual CanFrame readCanData();
  virtual int16_t writeCanData(uint32_t id, uint8_t dlc, uint8_t * data);
  virtual void Open(uint8_t, uint32_t);
  virtual void Close() { close(can_socket_fd); };
  virtual CanIfType interfaceType() { return socket_can; };

private:
  int can_socket_fd;
  std::string if_name;
  struct sockaddr_can can_addr;
};

#endif