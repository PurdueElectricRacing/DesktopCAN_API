#!/bin/bash

setup=1
baud=500000

echo "Usage: setup_can.sh [state (up|down)] [-b baud rate]"
echo "       Defaults: up -b 500000"

echo This script may or may not work. Who knows?
echo

if [[ $1 == "down" ]]; then
  setup=0
elif [[ $1 == "" ]]; then
  setup=1
  baud=500000
elif [[ $1 == "-b" && $2 != "" ]]; then
  if [[ $2 != "" ]]; then
    baud=$2
  else
    echo "No baud rate provided for -b switch"
    exit 1
  fi
elif [[ $2 == "-b" ]]; then
 if [[ $3 != "" ]]; then
    baud=$3
  else
    echo "No baud rate provided for -b switch"
    exit 1
  fi
else
  echo "Unrecognized command $1"
  exit 1
fi


if (( $setup == 1 )); then

  # set the can interface up
  echo "sudo ip link set can0 up type can bitrate $baud"
  sudo ip link set can0 up type can bitrate $baud

  if (( $? != 0 )); then
    echo Unable to set can0 to state up
    exit 1
  fi

  echo "Setup complete."
  echo
  echo "If the script worked the green light on the CANable should be solid and the blue light should be off."

else
  echo closing can0 link
  sudo ip link set can0 down

  if (( $? != 0 )); then
    echo Unable to set can0 to state down
    exit 1
  fi

  echo "Teardown complete."
  echo
  echo "If the script worked the blue light on the CANable should be solid and the green light should be off."

fi


