//
//  ofxEosSync.cpp
//  ofxEtcTcpOsc
//
//  Created by Jayson Haebich on 08/08/2020.
//  Edited by Ted Charles Brown

#include "ofxEosSync.h"
bool ofxEosSync::setup( const string addr, const int port )
{
    EosTimer::Init();
    
    this->addr = addr;
    this->port = port;
    connected = eosSyncLib.Initialize( addr.c_str(), port );
    
    if(connected)
    {
        running = true;
        startThread();
    }
    
    return connected;
}

bool ofxEosSync::hasWaitingMessages()
{
    return msgList.size();
}

ofxEosOscMsg ofxEosSync::getNextMessage()
{
    //if(msgList.size()>0)
    //{
        this->lock();
        auto msg = msgList.front();
        msgList.pop_front();
        this->unlock();
        return msg;
    
}

void ofxEosSync::sendMessage( ofxEosOscMsg & sendMsg )
{
    OSCPacketWriter packet;
    packet.SetPath( sendMsg.getAddress() );
    
    for( int i = 0; i < sendMsg.getNumArgs(); i++)
    {
        switch(sendMsg.getArgType(i))
        {
            case OscArgument::ArgType::INT:
                packet.AddInt32( sendMsg.getArgAsInt(i) );
                break;
                
            case OscArgument::ArgType::FLOAT:
                packet.AddFloat32( sendMsg.getArgAsFloat(i) );
                break;
                
            case OscArgument::ArgType::STRING:
                packet.AddString( sendMsg.getArgAsString(i) );
                break;
        }
    }
    
    eosSyncLib.Send(packet, true);
}

void ofxEosSync::threadedFunction()
{
    while( running )
    {
        if( connected )
        {
            // Update eos library
            eosSyncLib.Tick();
            
            if( eosSyncLib.IsRunning() )
            {
                EosTimer::SleepMS(10);
                
                // Get the current list of osc objects
                EosOsc::CMD_Q cmdList;
                eosSyncLib.getCmdList(cmdList);
                
                // Now update our list with this list
                this->lock();
                while( cmdList.size() > 0)
                {
                    // Convert an EosOsc osc object to our type
                    ofxEosOscMsg msg( *cmdList.front() );
                    msgList.push_front( msg );
                    cmdList.pop();
                }
                this->unlock();
            }
        }
    }
}
bool ofxEosSync::isConnected()
{
    return connected;
}

void ofxEosSync::close()
{
    running = false;
    eosSyncLib.Shutdown();
    this->stopThread();
}
