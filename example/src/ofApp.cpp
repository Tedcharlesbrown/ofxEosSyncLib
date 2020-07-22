#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Comment out the following line if you dont want to print to console ALL the messages
	ofSetLogLevel(OF_LOG_VERBOSE);
	//Change the ip and port to the ones you want.
    eosSync.setup("192.168.1.10", EosSyncLib::DEFAULT_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //cout << eosSync.recv() << endl;
    
	if(eosSync.update())
	{
		
		auto &  data = eosSync.getData();
		
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	string msg = eosSync.getStatusString();
	
	msg += "\n\nPress 's' key to send something";
	
	ofDrawBitmapString(msg, 30, 40);
}

//--------------------------------------------------------------
void ofApp::sendSomething()
{
    
	OSCPacketWriter packet;
	packet.SetPath("eos/ping");
	//packet.AddBool(true);
	
	eosSync.send(packet, true);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 's')
	{
		sendSomething();
	}
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
