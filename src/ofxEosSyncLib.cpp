#include "ofxEosSyncLib.h"

ofxEosSyncLib::ofxEosSyncLib()
{
	ofLogVerbose("ofxEosSyncLib::ofxEosSyncLib") << "initing...";
	EosTimer::Init();
	ofLogVerbose("ofxEosSyncLib::ofxEosSyncLib") << "inited";
}

ofxEosSyncLib::~ofxEosSyncLib()
{
	ofLogVerbose("ofxEosSyncLib::~ofxEosSyncLib") << "Shuting down...";
	eosSyncLib.Shutdown();
	ofLogVerbose("ofxEosSyncLib::~ofxEosSyncLib") << "Shut down";
}


void ofxEosSyncLib::setup(const std::string& ipAddress, int port)
{
	if( eosSyncLib.Initialize(ipAddress.c_str(), port))
	{
		this->ipAddress = ipAddress;
		this->port = port;
		ofLogVerbose("ofxEosSyncLib::setup") << "lib initialized correctly";
		bIsSetup = true;
	}
	else
	{
		ofLogVerbose("ofxEosSyncLib::setup") << "lib failed to be initialized";
		bIsSetup = false;
		this->ipAddress = "";
		this->port = -1;
	}
}


bool ofxEosSyncLib::update()
{
	if(bIsSetup)
	{
		eosSyncLib.Tick();
		flushLogQ();

		bool isConnected = eosSyncLib.IsConnected();
		bool isSyncd = (eosSyncLib.GetData().GetStatus().GetValue() == EosSyncStatus::SYNC_STATUS_COMPLETE);

			if(bWasConnected != isConnected)
			{
				if( isConnected )
				{
					ofLogVerbose("ofxEosSyncLib::update") << "Connected and Synchronizing";
				}
				else
				{
					ofLogVerbose("ofxEosSyncLib::update") << "Disconnected";
					return false;
				}
			}

			if( isConnected )
			{
//				if(!isSyncd && eosSyncLib.GetData().GetStatus().GetDirty())
//					printf(".");

				if(bWasSyncd != isSyncd)
				{
					if( isSyncd )
					{
						ofLogVerbose("ofxEosSyncLib::update") << "Synchronized";
						data = eosSyncLib.GetData();
						printSummary( data);
					}
					else
					{
						ofLogVerbose("ofxEosSyncLib::update") << "Not Synchronized...";
					}
				}

				eosSyncLib.ClearDirty();
			}
						
			bWasConnected = isConnected;
			bWasSyncd = isSyncd;

		
		return isSyncd && isConnected;
	}
	return false;
}


const EosSyncData & ofxEosSyncLib::getData() const
{
	return data;
}


void ofxEosSyncLib::flushLogQ()
{
	EosLog::LOG_Q q;
	eosSyncLib.GetLog().Flush(q);
	for(EosLog::LOG_Q::const_iterator i=q.begin(); i!=q.end(); i++)
	{
		const EosLog::sLogMsg &msg = *i;
		const char *str = msg.text.c_str();
		if( str )
		{
			tm *t = localtime( &msg.timestamp );
			const char *type = 0;
			switch( msg.type )
			{
				//case EosLog::LOG_MSG_TYPE_DEBUG:	type="Debug"; break;
				//case EosLog::LOG_MSG_TYPE_INFO:		type="Info"; break;
				case EosLog::LOG_MSG_TYPE_WARNING:	type="Warning"; break;
				case EosLog::LOG_MSG_TYPE_ERROR:	type="Error"; break;
			}
			if( type )
				printf("[ %.2d:%.2d:%.2d - %s ] %s\n", t->tm_hour, t->tm_min, t->tm_sec, type, str);
		}
	}
}


void ofxEosSyncLib::printSummary(const EosSyncData &syncData)
{
	const EosSyncData::SHOW_DATA &showData = syncData.GetShowData();

	for(EosSyncData::SHOW_DATA::const_iterator i=showData.begin(); i!=showData.end(); i++)
	{
		EosTarget::EnumEosTargetType targetType = i->first;
		const EosSyncData::TARGETLIST_DATA &listData = i->second;
		const char *targetName = EosTarget::GetNameForTargetType(targetType);

		for(EosSyncData::TARGETLIST_DATA::const_iterator j=listData.begin(); j!=listData.end(); j++)
		{
			int listNumber = j->first;
			const EosTargetList *targetList = j->second;

			if(listNumber > 0)
				printf("%s list %d:\t%d\n", targetName, listNumber, static_cast<int>(targetList->GetNumTargets()));
			else
				printf("%s:\t%d\n", targetName, static_cast<int>(targetList->GetNumTargets()));
		}
	}
}


bool ofxEosSyncLib::send(OSCPacketWriter &packet, bool immediate)
{
	return eosSyncLib.Send(packet, immediate);
}

string ofxEosSyncLib::recv()
{
    //return ofToString(ofGetElapsedTimeMillis());
    return oscMethod.Recv();
}


bool ofxEosSyncLib::isSetup() const
{
	return bIsSetup;
}

bool ofxEosSyncLib::isConnected() const
{
	return bWasConnected;
}

bool ofxEosSyncLib::isSyncd() const
{
	return bWasSyncd;
}


std::string ofxEosSyncLib::getStatusString()
{
	
	stringstream ss;
	
	ss << "IP Address : " << boolalpha << ipAddress << "\n";
	ss << "Port : " << boolalpha << port << "\n";
	ss << "Is Setup : " << boolalpha << bIsSetup << "\n";
	ss << "Is Connected : " << boolalpha << bWasConnected << "\n";
	ss << "Is Syncd : " << boolalpha << bWasSyncd;
	
	return ss.str();
	
}
