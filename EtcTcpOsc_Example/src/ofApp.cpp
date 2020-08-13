#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    eosOsc.setup("192.168.0.24", 3032); //Initial connect
}

//--------------------------------------------------------------
void ofApp::update(){
    while(eosOsc.hasWaitingMessages()) {
        
        ofxEosOscMsg m = eosOsc.getNextMessage();
        
        if (m.getAddress() == "/eos/out/user/1/cmd") { //GET COMMAND LINE
            cout << m.getArgAsString(0) << endl;
            
        } else if (m.getAddress() == "/eos/out/ping") { //GET PING BACK
            cout << m.getAsString() << endl;
            
            
        } else if (m.getAsString().find("Intens") != string::npos){ //FIND INTENSITY MESSAGE
            if (m.argHasPercent(0)) //CHECK IF ARG 1 HAS [#]
            cout << "INTENSITY = " << m.getArgPercent(0) << endl; //PARSE THE PERCENTAGE OUT
        }
        
    
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    eosOsc.close();
    eosOsc.setup("192.168.0.35", 3032); //Close and re-connect test.
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofxEosOscMsg m;
    m.setAddress("/eos/ping");
    eosOsc.sendMessage(m);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
