#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

#include "HostMessage_m.h"

using namespace omnetpp;

class Host : public cSimpleModule {
    private:
        cMessage *event;
    public:
        virtual ~Host();
    protected:
        virtual void initialize();
        virtual void scheduleMessage();
        virtual void generateMessage();
        virtual void handleMessage(cMessage *msg);
};

Define_Module(Host);

Host::~Host()
{
    cancelAndDelete(event);
}

void Host::initialize() {
    event = new cMessage("message generation event");
    scheduleMessage();
}

void Host::scheduleMessage() {
    double waitTime = par("betweenMsg");
    scheduleAt(simTime()+waitTime, event);
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
    delete msg;

    EV_INFO << "Host " << src << " sends message to Host " << dst << "\n";
}

void Host::handleMessage(cMessage *msg) {
    if (msg == event) {
        generateMessage();
        scheduleMessage();
    } else {
        EV_INFO << "Host " << getIndex() << " receives message: '" << msg->getName() << "'\n";
        delete msg;
    }
}
