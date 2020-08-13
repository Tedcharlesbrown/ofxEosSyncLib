//
//  ofxEosSync.hpp
//  ofxEtcTcpOsc
//
//  Created by Jayson Haebich on 08/08/2020.
//  Edited by Ted Charles Brown

#ifndef ofxEosSync_hpp
#define ofxEosSync_hpp

#include "ofMain.h"
#include "EosOsc.h"
#include "ofxEosOscMsg.h"
class ofxEosSync : public ofThread
{
public:
    bool setup( const string addr, const int port );
    bool hasWaitingMessages();
    bool isConnected();
    ofxEosOscMsg getNextMessage();
    void sendMessage( ofxEosOscMsg & sendMsg );
    void threadedFunction();
    void close();
    
private:
    
    list < ofxEosOscMsg > msgList;
    
    string            addr;
    unsigned short    port;
    bool              connected;
    bool              running;
    EosSyncLib        eosSyncLib;
};

#endif /* ofxEosSync_hpp */
