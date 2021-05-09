include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/canframe.cpp
      )

if (WIN32)
  set(SOURCES
      ${SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/candle/gsusb.c
      ${CMAKE_CURRENT_SOURCE_DIR}/candle/candle.c
      ${CMAKE_CURRENT_SOURCE_DIR}/candle/cantle_ctrl_req.c
      ${CMAKE_CURRENT_SOURCE_DIR}/candle/WinCan.cpp
      )
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/candle)
  find_package(SetupApi REQUIRED)
  find_package(Ole32 REQUIRED)
  find_package(winusb REQUIRED)

else()
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/socketcan)
  set(SOURCES
      ${SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/socketcan/socketcan_if.cpp
     )
endif()
