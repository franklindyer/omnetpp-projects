#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Host : public cSimpleModule {
    protected:
        virtual void initialize();
        virtual void sendMessage(cMessage *msg);
        virtual void handleMessage(cMessage *msg);
};

Define_Module(Host);

void Host::initialize() {}

void Host::sendMessage(cMessage *msg) {}

void Host::handleMessage(cMessage *msg) {}
