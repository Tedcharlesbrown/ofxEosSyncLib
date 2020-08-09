//
//  ofxEosSyncMessage.cpp
//  eosTed3
//
//  Created by Jayson Haebich on 08/08/2020.
//

#include "ofxEosSyncOscMsg.h"

/**
 * Create an ofxEosSyncOscMsg from an EosOsc::sCommand
 */
ofxEosSyncOscMsg::ofxEosSyncOscMsg( EosOsc::sCommand & inCmd )
{
    // save address and timestamp
    this->addr = inCmd.path;
    this->time = inCmd.timestamp;
    
    // Now save args
    for( int i = 0; i < inCmd.argCount; i++ )
    {
        // Select the correct argument
        switch(inCmd.args[i].GetType())
        {
            // int, please note it doesn't differentiate between 32 and 64 bit int
            case OSCArgument::EnumArgumentTypes::OSC_TYPE_INT32:
            case OSCArgument::EnumArgumentTypes::OSC_TYPE_INT64:
            {
                    int val;
                    if(inCmd.args[i].GetInt(val))
                    {
                        OscArgument arg(val); 
                        argList.push_back( arg );
                    }
            }
            break;
            
            // float
            // please note it doesn't differentiate between 32 and 64 bit float
            case OSCArgument::EnumArgumentTypes::OSC_TYPE_FLOAT32:
            case OSCArgument::EnumArgumentTypes::OSC_TYPE_FLOAT64:
            {
                    float val;
                    if(inCmd.args[i].GetFloat(val))
                    {
                        OscArgument arg(val);
                        argList.push_back( arg );
                    }
            }
            break;
                
            // string
            case OSCArgument::EnumArgumentTypes::OSC_TYPE_STRING:
            {
                    string val;
                    if(inCmd.args[i].GetString(val))
                    {
                        OscArgument arg(val);
                        argList.push_back( arg );
                    }
            }
            break;
        }
    }
}

/**
 * Makes a string with address and args, for debugging
 */
string ofxEosSyncOscMsg::getAsString()
{
    string str;
    str = time + ": " + addr;
    for( OscArgument arg : argList )
    {
        if(arg.tag == OscArgument::INT)
            str += " " + ofToString(arg.i) + "/i";
        else if(arg.tag == OscArgument::FLOAT)
            str += " " + ofToString(arg.f) +"/f";
        else if(arg.tag == OscArgument::STRING)
            str += " " + ofToString(arg.s) + "/s";
    }
    return str;
}

/**
 * Create an ofxEosSyncOscMsg from a string
 */
ofxEosSyncOscMsg::ofxEosSyncOscMsg( string addr )
{
    this->addr = addr;
}

/**
 * get the address of this message
 */
string ofxEosSyncOscMsg::getAddress()
{
    return addr;
}

/**
 * Get the arg type at index
 */
int ofxEosSyncOscMsg::getArgType ( int index )
{
    return argList[ index ].tag;
}

/**
 * Get an int at index
 */
int ofxEosSyncOscMsg::getArgAsInt( int index )
{
    return argList[ index ].i;
}


/**
 * Get a float at index
 */
float  ofxEosSyncOscMsg::getArgAsFloat  ( int index )
{
    return argList[ index ].f;
}

/**
 * Get a String at index
 */
string ofxEosSyncOscMsg::getArgAsStr( int index )
{
    return argList[ index ].s;
}

/**
 * Clear all the arguments
 */
void ofxEosSyncOscMsg::clear()
{
    argList.clear();
}

/**
 * Set the address of this osc mesagge
 */
void ofxEosSyncOscMsg::setAddress( const string addr )
{
    this->addr = addr;
}

/**
 * Add an int arg
 */
void ofxEosSyncOscMsg::addIntArg( const int val )
{
    argList.push_back( OscArgument( val ) );
}

/**
 * Add a float arg
 */
void ofxEosSyncOscMsg::addFloatArg( const float val )
{
    argList.push_back( OscArgument( val ) );
}

/**
 * Add a string arg
 */
void ofxEosSyncOscMsg::addStringArg( const string val )
{
    argList.push_back( OscArgument( val ) );
}

int ofxEosSyncOscMsg::getNumArgs()
{
    return argList.size();
}
