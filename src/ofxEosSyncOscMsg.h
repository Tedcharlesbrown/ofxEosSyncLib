//
//  ofxEosSyncMessage.h
//  ofxEtcTcpOsc
//
//  Created by Jayson Haebich on 08/08/2020.
//  Edited by Ted Charles Brown

#ifndef ofxEosSyncMessage_h
#define ofxEosSyncMessage_h

#include "ofMain.h"
#include "EosOsc.h"
#include "EosSyncLib.h"
#include "EosTimer.h"

// Wrapper for Eos osc message data type

struct OscArgument
{
    OscArgument( int val )
    {
        i   = val;
        tag = INT;
    }
    OscArgument( float val )
    {
        f   = val;
        tag = FLOAT;
    }
    OscArgument( string val )
    {
        s   = val;
        tag = STRING;
    }
    enum ArgType{INT, FLOAT, STRING};
    ArgType tag;
    
        int    i;
        float  f;
        string s;
    
};

class ofxEosSyncOscMsg
{
public:
    
    ofxEosSyncOscMsg();
    ofxEosSyncOscMsg( EosOsc::sCommand & inCmd );
    ofxEosSyncOscMsg( string addr );
    
    void setToPacket( OSCPacketWriter & packet);
    string getAsString();
    
    // For receiving messages
    string     getAddress();
    int getArgType    ( int index );
    int        getArgAsInt   ( int index );
    float      getArgAsFloat ( int index );
    string     getArgAsStr   ( int index );
    int        getNumArgs();
    
    // For sending messages
    void   clear();
    void   setAddress     ( const string addr );
    void   addIntArg      ( const int    arg  );
    void   addFloatArg    ( const float  arg  );
    void   addStringArg   ( const string arg  );
    
private:
    
    string addr;
    string time;
    
    vector < OscArgument > argList;
};
#endif /* ofxEosSyncMessage_h */
