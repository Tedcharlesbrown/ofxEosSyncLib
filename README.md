# ofxEosSyncLib
Conversion of EosSyncLib open source library to OpenFrameworks Library

This is 100% not up and running. I do not know how to actually make an addon for OpenFrameworks. If anyone is interested in helping me out a little - I would greatly appreciate it.

Link to EosSyncLib library: https://github.com/ETCLabs/EosSyncLib

OpenFrameworks addon template: https://github.com/openframeworks/ofxAddonTemplate/

----

The goal: send and receive OSC through TCP. Why: I created an app for android that uses TCP and it works pretty well. EOS prefers TCP, I also would prefer TCP because it makes connecting easier for the end user.

For those who are not familiar with the ETC EOS: This is a lighting software mostly used in theatre. Upon a client connecting to the console, the console will send out a whole bunch of packets with the current state. The Library should be able to read these. The library should also be able to send strings / ints / floats to the console.

To see what the console is outputting: There is a DIAGONOSTICS Tab. It should be visible upon starting the program up. If not, pressing and holding TAB then pressing 99 and releasing TAB will take you to this menu. You can then toggle incoming and outgoing osc through this menu.

I have also tried just using the ofxNetwork library and getting that to connect through TCP. While doing this, I am only able to get the EOS to see there is a client - but my program will not see the EOS nor see any incoming packets. However, I am able to send TCP - with the caveat of it not being formatting properly as an OSC packet.
