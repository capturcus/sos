#include "sosserver.h"
#include "qdebug.h"

SOSServer::SOSServer(QObject *parent)
	: QObject(parent), nt(nullptr), uit(nullptr)
{
	nt.start();
	uit.start();
}

SOSServer::~SOSServer()
{

}
