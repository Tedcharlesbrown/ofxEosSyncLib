#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

	//Comment out the following line if you dont want to print to console ALL the messages
	ofSetLogLevel(OF_LOG_VERBOSE);
	//Change the ip and port to the ones you want.
	eosSync.setup("192.168.0.1", EosSyncLib::DEFAULT_PORT);
	
}

//--------------------------------------------------------------
void ofApp::update(){

	if(eosSync.update())
	{
		
		auto &  data = eosSync.getData();
		
		// here just do what ever you need with the data.
		// this is as far as the example provided by the library goes.
		// You'll need to dig into it in order to find how to send data
		
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
	
	// I have no idea if this is correct. I am just guessing.
	//You'll need to dig a bit in order to figure out the right way for sending data.
	OSCPacketWriter packet;
	packet.SetPath("Path/of/the/packet");
	packet.AddBool(true);
	
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
