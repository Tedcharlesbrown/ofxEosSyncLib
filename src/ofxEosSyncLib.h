
#include "EosOsc.h"
#include "EosSyncLib.h"
#include "EosTcp.h"
#include "EosTimer.h"

#if defined(TARGET_OF_IOS) || defined(TARGET_OSX ) || defined(TARGET_OF_IPHONE)
#include "EosUdp_Mac.h"
#include "EosTcp_Mac.h"

#endif

#ifdef TARGET_WIN32
#include "EosUdp_Win.h"
#include "EosTcp_Win.h"
#endif

#include "EosUdp.h"
#include "OSCParser.h"


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
	
	std::string getStatusString();
	
private:
	
	
	std::string ipAddress;
	int port;
	
	EosSyncData data;
	
	EosSyncLib eosSyncLib;
	
	bool bIsSetup = false;
	bool bWasConnected = false;
	bool bWasSyncd = false;
	
	
	void flushLogQ();
	
	void printSummary(const EosSyncData &syncData);
};




////////////////////////////////////////////////////////////////////////////////

//int main(int /*argc*/, char** /*argv*/)
//{
//	EosTimer::Init();
//
//	printf("Connecting...\n");
//
//	EosSyncLib eosSyncLib;
//	//if( eosSyncLib.Initialize("127.0.0.1",EosSyncLib::DEFAULT_PORT) )
//    if( eosSyncLib.Initialize("192.168.1.20",EosSyncLib::DEFAULT_PORT) )
//	{
//		bool wasConnected = false;
//		bool wasSyncd = false;
//
//		for(;;)
//		{
//			eosSyncLib.Tick();
//			FlushLogQ(eosSyncLib);
//
//			bool isConnected = eosSyncLib.IsConnected();
//			bool isSyncd = (eosSyncLib.GetData().GetStatus().GetValue() == EosSyncStatus::SYNC_STATUS_COMPLETE);
//
//			if(wasConnected != isConnected)
//			{
//				if( isConnected )
//				{
//					printf("Connected\n");
//					printf("Synchronizing\n");
//				}
//				else
//				{
//					printf("Disconnected\n");
//					break;
//				}
//			}
//
//			if( isConnected )
//			{
//				if(!isSyncd && eosSyncLib.GetData().GetStatus().GetDirty())
//					printf(".");
//
//				if(wasSyncd != isSyncd)
//				{
//					if( isSyncd )
//					{
//						printf("Synchronized\n");
//						PrintSummary( eosSyncLib.GetData() );
//					}
//					else
//						printf("Not Synchronized...\n");
//				}
//
//				eosSyncLib.ClearDirty();
//			}
//
//			fflush(stdout);
//
//			wasConnected = isConnected;
//			wasSyncd = isSyncd;
//
//			EosTimer::SleepMS(10);
//		}
//
//		eosSyncLib.Shutdown();
//	}
//
//	return 0;
//}
//
//////////////////////////////////////////////////////////////////////////////////
