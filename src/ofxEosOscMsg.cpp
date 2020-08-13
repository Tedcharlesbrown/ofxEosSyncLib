//
//  ofxEosSyncMessage.cpp
//  ofxEtcTcpOsc
//
//  Created by Jayson Haebich on 08/08/2020.
//  Edited by Ted Charles Brown

#include "ofxEosOscMsg.h"

/**
 * Create an empty ofxEosSyncOscMsg
 */
ofxEosOscMsg::ofxEosOscMsg()
{
    
}

/**
 * Create an ofxEosSyncOscMsg from an EosOsc::sCommand
 */
ofxEosOscMsg::ofxEosOscMsg( EosOsc::sCommand & inCmd )
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
                
            default: break;
        }
    }
}

/**
 * Makes a string with address and args, for debugging
 */
string ofxEosOscMsg::getAsString()
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
ofxEosOscMsg::ofxEosOscMsg( string addr )
{
    this->addr = addr;
}

/**
 * get the address of this message
 */
string ofxEosOscMsg::getAddress()
{
    return addr;
}

/**
 * Get the arg type at index
 */
int ofxEosOscMsg::getArgType ( int index )
{
    return argList[ index ].tag;
}

/**
 * Get an int at index
 */
int ofxEosOscMsg::getArgAsInt( int index )
{
    return argList[ index ].i;
}


/**
 * Get a float at index
 */
float  ofxEosOscMsg::getArgAsFloat  ( int index )
{
    return argList[ index ].f;
}

/**
 * Get a String at index
 */
string ofxEosOscMsg::getArgAsString( int index )
{
    return argList[ index ].s;
}

/**
 * Get a if argument [has percentage]
 */
bool ofxEosOscMsg::argHasPercent( int index )
{
    if (argList[ index ].s.find("[") != string::npos) {
        return true;
    }
    return false;
}

/**
 * Get a percent of argument
 */
string ofxEosOscMsg::getArgPercent( int index )
{
    if (argList[ index ].s.find("[") != string::npos) {
        string incomingOSC = argList[ index ].s;
        int indexValueStart = incomingOSC.find("[");
        int indexValueEnd = incomingOSC.find("]");
        string outputString = incomingOSC.substr(indexValueStart + 1, indexValueEnd - indexValueStart - 1);
        return outputString;
    } else {
        return "ARGUMENT HAS NO [PERCENTAGE]";
    }

}

/**
 * Clear all the arguments
 */
void ofxEosOscMsg::clear()
{
    argList.clear();
}

/**
 * Set the address of this osc mesagge
 */
void ofxEosOscMsg::setAddress( const string addr )
{
    this->addr = addr;
}

/**
 * Add an int arg
 */
void ofxEosOscMsg::addIntArg( const int val )
{
    argList.push_back( OscArgument( val ) );
}

/**
 * Add a float arg
 */
void ofxEosOscMsg::addFloatArg( const float val )
{
    argList.push_back( OscArgument( val ) );
}

/**
 * Add a string arg
 */
void ofxEosOscMsg::addStringArg( const string val )
{
    argList.push_back( OscArgument( val ) );
}

int ofxEosOscMsg::getNumArgs()
{
    return argList.size();
}
