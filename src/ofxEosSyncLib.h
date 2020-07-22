
#include "EosOsc.h"
#include "EosSyncLib.h"
#include "EosTcp.h"
#include "EosTimer.h"
#include "OSCParser.h"

#if defined(TARGET_OF_IOS) || defined(TARGET_OSX ) || defined(TARGET_OF_IPHONE)
#include "EosUdp_Mac.h"
#include "EosTcp_Mac.h"

#endif

#ifdef TARGET_WIN32
#include "EosUdp_Win.h"
#include "EosTcp_Win.h"
#endif

#include "EosUdp.h"


//TODO: include only the needed headers from openFrameworks rather than ofMain.h which includes all
#include "ofMain.h"


class ofxEosSyncLib
{
public:

	ofxEosSyncLib();
	~ofxEosSyncLib();
	
	void setup(const std::string& ipAddress, int port = EosSyncLib::DEFAULT_PORT);
	
	bool update();
	
	const EosSyncData & getData() const;
	
	bool isSetup() const; 
	bool isConnected() const; 
	bool isSyncd() const; 
	
	bool send(OSCPacketWriter &packet, bool immediate);
    string recv();
	
	std::string getStatusString();
	
private:
	
	
	std::string ipAddress;
	int port;
	
	EosSyncData data;
	
	EosSyncLib eosSyncLib;
    OSCMethod oscMethod;
	
	bool bIsSetup = false;
	bool bWasConnected = false;
	bool bWasSyncd = false;
	
	
	void flushLogQ();
	
	void printSummary(const EosSyncData &syncData);
};

//////////////////////////////////////////////////////////////////////////////////
