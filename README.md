# ofxEosSyncLib
Conversion of EosSyncLib open source library to OpenFrameworks Library

This is 100% not up and running. I do not know how to actually make an addon for OpenFrameworks. If anyone is interested in helping me out a little - I would greatly appreciate it.

Link to EosSyncLib library: https://github.com/ETCLabs/EosSyncLib

OpenFrameworks addon template: https://github.com/openframeworks/ofxAddonTemplate/

----

## The Goal: 
send and receive OSC through TCP. Why: I created an app for android that uses TCP and it works pretty well. EOS prefers TCP, I also would prefer TCP because it makes connecting easier for the end user.

## What is ETC EOS: 
ETC: The company - Electronic Theatre Controls. 

EOS: family of consoles - Ion, Gio, Ti, Element, Nomad Etc...

Nomad: The offline editor / actual software that the hardware runs.

### Background:
The EOS family console line is mostly used in live theatre. From Broadway to highschool, this is the preferred console. OSC can be used to talk with the console, and to also receive feedback. There are generic OSC apps that work, such as TouchOSC and Lemur. However, These are UDP solutions and do not easily accept feedback from the console. There are other apps such as OSC RFR by Alien Stagecraft and aRFR Remote Control by ETC (RFR = Radio Focus Remote, another device created by ETC to focus and send commands to the console via a non-smartphone remote).

### Why TCP?:
This is stated by ETC to be their preferred protocol - https://www.etcconnect.com/workarea/DownloadAsset.aspx?id=10737461372.
Note: EOS can use both packet-length headers and SLIP, but packet-length is preferred.

*There are also two other main reasons why I feel TCP is needed. One: The End-User.*

Without TCP, the user will have to...
1. Type in the IP Address of the console into the app
2. Match the rx port of the console to the tx port in the app.
3. Match the tx port of the console to the rx port in the app.
4. Type in the IP Address of the phone running the app into the console, separating multiple IP's by commmas.

On the other hand, with TCP the user only has to...
1. Type in the IP Address of the console into the app.

Since TCP uses the same port for tx and rx - it dedicates port 3032 for this. No need for the user to worry about anything else.


*The other main reason is: packet drops.*

With fewer packets dropped, you can ensure that all OSC is being received properly. Since the EOS actually sends hundreds of OSC packets per keystroke, making sure you get each one is important.

#### Console setup:
If you are not familiar with the ETC EOS software, I have included an empty showfile that has the correct settings. In order to see what is being sent and received by the console, In the lower left hand side of the screen there is a tab that says "99 DIAGNOSTICS" - click this. (Likewise you can also hold down "TAB", press "99", and release "TAB"). Then, in this new window, scroll down. You should see two toggle buttons called "INCOMING OSC (off)" and "OUTGOING OSC (off)". Click these so they show.

*To double check your settings*
Upon opening up the software for the first time you will see an option for choosing "EOS ETCNOMAD" and "ELEMENT 2 ETCNOMAD" - choose "EOS ETCNOMAD". Now you should see some more options buttons, click "SETTINGS". Right hand side, click "NETWORK". Scrolling down to the bottom, UDP Strings & OSC should be checked, as well as packet-length headers. Click "ACCEPT", then click "OFFLINE". You should now be in the eos software proper. In the bottom right corner, you should see a carrot menu option. Click that to open up the bottom menu. Here, in yellow text, you should see your IP Address. If you do not see yellow text, hit "Y" on the keyboard. Next, hit "Y" again to bring up the browser menu. Under "SETUP", "SYSTEM SETTINGS", "SHOW CONTROL", "OSC" - OSC RX and OSC TX should be enabled. Nothing else is needed for TCP to work.


#### How to send OSC from the console:

With the "DIAGNOSTICS" tab open and "OUTGOING OSC (on)" so you can see. Press any "1". Press Enter. Press "2". Press Enter. These are some examples of what could be sent. Notice how a ton of information is sent on every key press.

Upon a client connecting to the console, the console will send out a whole bunch of packets with the current state.
