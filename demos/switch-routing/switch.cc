#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Switch : public cSimpleModule {
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void forwardMessage(cMessage *msg);
};

Define_Module(Switch);

void Switch::initialize() {}

void Switch::handleMessage(cMessage *msg) {}

void Switch::forwardMessage(cMessage *msg) {}
