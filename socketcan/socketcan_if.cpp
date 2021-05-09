// C includes
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/sockios.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <asm/sockios.h>
#include <iomanip>
#include <errno.h>

// C++ includes
#include <iostream>

// user includes
#include "socketcan_if.h"

/// @brief: Constructor
///         Handles creation of CAN socket and initialization
///         of necessary data.
SocketCanDevice::SocketCanDevice(int type, int protocol, int enable_own_messages, std::string ifname)
{
  int fd;
  struct ifreq ifr;

  // attempt to open the socket
  errno = 0;
  fd = socket(PF_CAN, type, protocol);

  if (fd < 0)       // error opening socket
  {
    perror("SocketCanDevice constructor socket call");
    throw CanSocketException;
  }

  strcpy(ifr.ifr_name, ifname.c_str());

  errno = 0;
  if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1)
  {
    perror("SocketCanDevice: ioctl");
    throw CanSocketException;
  }

  can_addr.can_family = AF_CAN;
  can_addr.can_ifindex = ifr.ifr_ifindex;

  errno = 0;
  // enable or disable receipt of our messages. Default is disabled
  setsockopt(fd, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &enable_own_messages, 
            sizeof(enable_own_messages));

  can_socket_fd = fd;
  if_name = ifname;
}




/// @brief: attempt to open the device. we don't care about the args
///         they're just used on winders
/// @throws: CanSocketException if there was a binding failure
void SocketCanDevice::Open(uint8_t, uint32_t)
{
  errno = 0;
  // if bind fails throw an exception
  if (bind(can_socket_fd, (struct sockaddr *) &can_addr, sizeof(can_addr)) != 0)
  {
    perror("SocketCanDevice constructor bind call");
    throw CanSocketException;
  }
}



/// @brief: send data to the address specified by id
///
/// @note: see https://www.kernel.org/doc/Documentation/networking/can.txt for 
///        for info on the socketCAN api
///
/// @return: number of bytes written, or -1 on error
int16_t SocketCanDevice::writeCanData(uint32_t id, uint8_t dlc, uint8_t *data)
{
  can_frame frame;
  int16_t bytes = 0;

  frame.can_dlc = dlc;
  frame.can_id = id;
  memcpy(frame.data, data, dlc);

  errno = 0;
  bytes = sendto(can_socket_fd, &frame, sizeof(struct can_frame), 0, 
                 (struct sockaddr *) &can_addr, sizeof(can_addr));

  if (bytes == -1)
  {
    perror("writeCanData: sendto");
    throw CanSocketException;
  }

  return bytes;
}


/// @brief: reads whatever is in the CAN buffer and returns a CanFrame object
///
/// @return:
CanFrame SocketCanDevice::readCanData()
{
  CanFrame frame_obj;
  struct can_frame frame;
  
  int32_t nbytes = 0;
  struct timeval timeout;
  fd_set fdset;

  timeout.tv_sec = 1; // 1 second
  timeout.tv_usec = 0;

  FD_ZERO(&fdset);
  FD_SET(can_socket_fd, &fdset);

  errno = 0;
  int rv = select(can_socket_fd+1, &fdset, NULL, NULL, &timeout);
  
  // copy pasted this from the kernel documentation
  if (rv > 0)
  {
    errno = 0;
    
    nbytes = read(can_socket_fd, &frame, sizeof(struct can_frame));

    if (nbytes < 0)
    {
      perror("SocketCanDevice::readCanData:can raw socket read");
      throw CanSocketException;
    }

    // suppress compiler warnings grumble grumble
    if (((uint64_t) nbytes) < sizeof(struct can_frame))
    {
      fprintf(stderr, "SocketCanDevice::readCanData:read: incomplete CAN frame\n");
      throw CanDataException;
    }

    frame_obj = frame;
  }
  else
  {
    if (timeout.tv_sec == 1)
    {
      std::cerr << "A read timeout occurred.\n\n";
    }
  }  

  errno = 0;
  struct timeval t;
  // get the timestamp of the message and store it in the wrapper class.
  ioctl(can_socket_fd, SIOCGSTAMP, &(t));
  frame_obj.timestamp_us = t.tv_usec;

  return frame_obj;
}


