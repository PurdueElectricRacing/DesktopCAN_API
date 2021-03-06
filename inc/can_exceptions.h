#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <exception>
#include <string>

class CanNullException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "There is no CAN device connected.\n";
  }
} static CanNullException;

// likely going to add a bunch of exceptions here
class CanSocketException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while opening/connecting to a CAN socket.\n";
  }
} static CanSocketException;

class CanDataException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while attempting to read / write from CAN device.\n";
  }
} static CanDataException;

class CanWindowsTimingException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while attempting to set the timing for a CAN device.\n";
  }
} static CanWindowsTimingException;



class CanWindowsOpenException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while attempting to open a CAN interface.\n";
  }
} static CanWindowsOpenException;



class CanWindowsCloseException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while attempting to close a CAN interface.\n";
  }
} static CanWindowsCloseException;


class CanGenericException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred with the CAN device\n";
  }
} static CanGenericException;



class CanWindowsGetDeviceException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while attempting get a CAN interface.\n";
  }
} static CanWindowsGetDeviceException;



class CanWindowsDeviceListException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while attempting find the attached CAN devs.\n";
  }
} static CanWindowsDeviceListException;


#endif