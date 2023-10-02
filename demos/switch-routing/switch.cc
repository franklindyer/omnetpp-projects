#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

#include "HostMessage_m.h"

using namespace omnetpp;

class Switch : public cSimpleModule {
    public:
        virtual ~Switch();
    private:
        cMessage **expireEntry;
        int *routeTable;
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void forwardMessage(HostMessage *msg);
};

Define_Module(Switch);

Switch::~Switch() {
    int numHosts = par("numHosts");
    for (int i = 0; i < numHosts; i++) {
        cancelAndDelete(expireEntry[i]);
    }
}

void Switch::initialize() {
    int numHosts = par("numHosts");
    expireEntry = new cMessage*[numHosts];
    routeTable = new int[numHosts];
    for (int i = 0; i < numHosts; i++) {
        expireEntry[i] = new cMessage("route table entry expiration");
        routeTable[i] = -1;
    }
}

void Switch::handleMessage(cMessage *msg) {
    // Handle periodic expiration of route table entries
    int numHosts = par("numHosts");
    for (int i = 0; i < numHosts; i++) {
        if (msg == expireEntry[i]) {
            EV_INFO << "Route table entry " << i << " of Switch " << getIndex() << " expires\n";
            routeTable[i] = -1;
            return;
        }
    }

    // All other messages are from hosts
    EV_DETAIL << "Message arrives at Switch " << getIndex() << "\n";
    HostMessage *hMsg = (HostMessage*)msg;
    int arriv = hMsg->getArrivalGate()->getIndex();
    int src = hMsg->getSrc();
    if (routeTable[src] == -1) {
        // Update route table entry corresponding to input gate, if currently empty/expired
        routeTable[src] = arriv;
        EV_INFO << "Switch " << getIndex() << " learns next-hop for Host " << src << "\n"; 
    } else {
        // If route table entry already exists, renew it by cancelling existing expiration
        cancelEvent(expireEntry[src]);
    }
    scheduleAt(simTime()+par("expire"), expireEntry[src]);
    forwardMessage(hMsg);
}

void Switch::forwardMessage(HostMessage *msg) {
    int arriv = msg->getArrivalGate()->getIndex();
    int dst = msg->getDst();
    if (routeTable[dst] == -1) {
        // If the next-hop is unknown, flood to all gates except the one it came from
        EV_DETAIL << "Next-hop for destination " << dst << " unknown to Switch " << getIndex() << ", will use flooding\n";
        int numOut = gateSize("out");
        for (int i = 0; i < numOut; i++) {
            if (i == arriv) continue;
            send(msg->dup(), "out", i);
        }
    } else if (routeTable[dst] == arriv) {
        // A switch should never forward a frame to the same gate from which it was received
        EV_DETAIL << "Switch " << getIndex() << " receives packet from same gate as its next-hop, and ignores it.\n";
    } else {
        // Otherwise, use the next-hop in the route table
        EV_DETAIL << "Next-hop for destination " << dst << " is known to Switch " << getIndex() << "\n";
        send(msg->dup(), "out", routeTable[dst]);
    }
    delete msg;
}
