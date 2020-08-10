![Addon Thumbnail](https://github.com/Tedcharlesbrown/ofxEtcTcpOsc/blob/Parent/ofxaddons_thumbnail.png)
# ofxEtcTcpOsc

This is an OpenFrameworks adaptation of the [EosSyncLib](https://github.com/ETCLabs/EosSyncLib) from [ETC Labs](https://github.com/ETCLabs). Thanks to Jayson Haebich for the conversion and making everything work.

[EOS Family Show Control Manual](https://www.etcconnect.com/workarea/DownloadAsset.aspx?id=10737461372)

## About this project

ofxEtcTcpOsc is a open-open source addon for OpenFrameworks. Initially forked from the [EosSyncLib](https://github.com/ETCLabs/EosSyncLib), it has now been converted to recieve all incoming OSC rather than just the commands gotten from "/eos/subscribe". That functionality still remains in the code, but is currently commented out.

## Installation

To use this addon with OpenFrameworks: 
* Download the library.
* Put it into the OpenFrameworks addon folder.
* Launch a new project or update an existing with the OpenFrameworks Project Manager.
* [More info on installing addons here](https://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/)

## Simple Example
#### ofApp.h
```
#pragma once

#include "ofMain.h"

#include "ofxEosSyncOscMsg.h"
#include "ofxEosSync.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    
    ofxEosSync eosOsc;
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
   ```
#### ofApp.cpp
```
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    eosOsc.setup("192.168.0.24", 3032); //Initial connect
}

//--------------------------------------------------------------
void ofApp::update(){
    while(eosOsc.hasWaitingMessages()) {
        
        ofxEosSyncOscMsg m = eosOsc.getNextMessage();
        
        if (m.getAddress() == "/eos/out/user/1/cmd") { //Get command line
            cout << m.getArgAsStr(0) << endl;
            
        } else if (m.getAddress() == "/eos/out/ping") { //Get ping back
            cout << m.getAsString() << endl;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    eosOsc.close();
    eosOsc.setup("192.168.0.35", 3032); //Close and re-connect test.
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofxEosSyncOscMsg msg;
    msg.setAddress("/eos/ping");
    eosOsc.send(msg);

}
```

## Acknowledgements

* [Electronic Theatre Controls](https://www.etcconnect.com/)
* Jayson Haebich - Converted the library and added functions to mimic [ofxOsc](https://openframeworks.cc/documentation/ofxOsc/)
* [The openFrameworks community](https://forum.openframeworks.cc/)
* [@Roy Macdonald](https://github.com/roymacdonald)


## License

The MIT License (MIT) 2020 - Ted Charles Brown.

Please have a look at the LICENSE.md for more details.
