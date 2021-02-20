# DesktopCAN_API
An API for the CANable meant for Windows or Linux projects, built with Qt on Windows.

See `examples/` for usage examples

Integrating into a project
=====

The project must be a Qt desktop application using C++.
To use this module in your Qt project, first create your project, then run `git submodule add <this repo's link>` in the project's root directory. 

Next, you'll need to add this to the bottom of your `<project>.pro` file:
`include($$PWD/DesktopCAN_API/canapi.pri)`

That's it. You should be able to use this module now.

See git submodules for more information on what else you can do.
