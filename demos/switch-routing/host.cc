#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

#include "HostMessage_m.h"

using namespace omnetpp;

class Host : public cSimpleModule {
    private:
        cMessage *sendEvent;
        int numSent;
        int numReceived;
        int numRefused;
    public:
        virtual ~Host();
    protected:
        virtual void initialize();
        virtual void scheduleMessage();
        virtual void generateMessage();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
};

Define_Module(Host);

Host::~Host()
{
    cancelAndDelete(sendEvent);
}

void Host::initialize() {
    numSent = 0;
    numReceived = 0;
    numRefused = 0;

    sendEvent = new cMessage("message generation event");
    scheduleMessage();
}

void Host::scheduleMessage() {
    double waitTime = par("betweenMsg").doubleValue();
    scheduleAt(simTime()+waitTime, sendEvent);
}

void Host::generateMessage() {
    int src = getIndex();
    int n = size();
    int dst = intuniform(0, n-2);
    if (dst >= src) dst++;

    char msgname[50];
    sprintf(msgname, "I love you, Host %d! Sincerely, Host %d ^3^", dst, src);

    HostMessage *msg = new HostMessage(msgname);
    msg->setSrc(src);
    msg->setDst(dst);
    send(msg->dup(), "out");
    numSent++;
    delete msg;

    EV_INFO << "Host " << src << " sends message to Host " << dst << "\n";
}

void Host::handleMessage(cMessage *msg) {
    if (msg == sendEvent) {
        generateMessage();
        scheduleMessage();
    } else {
        HostMessage *hMsg = (HostMessage*)msg;
        if (hMsg->getDst() == getIndex()) {
            EV_INFO << "Host " << getIndex() << " receives message: '" << msg->getName() << "'\n";
            numReceived++;
            delete msg;
        } else {
            EV_INFO << "Host " << getIndex() << " refuses a message addressed for someone else\n";
            numRefused++;
            delete msg;
        }
    }
}

void Host::finish() {
    recordScalar("#sent", numSent);
    recordScalar("#received-correct", numReceived);
    recordScalar("#received-incorrect", numRefused);
}
