//
// Generated file, do not edit! Created by nedtool 5.5 from HostMessage.msg.
//

#ifndef __HOSTMESSAGE_M_H
#define __HOSTMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0505
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>HostMessage.msg:1</tt> by nedtool.
 * <pre>
 * message HostMessage
 * {
 *     int src;
 *     int dest;
 * }
 * </pre>
 */
class HostMessage : public ::omnetpp::cMessage
{
  protected:
    int src;
    int dest;

  private:
    void copy(const HostMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const HostMessage&);

  public:
    HostMessage(const char *name=nullptr, short kind=0);
    HostMessage(const HostMessage& other);
    virtual ~HostMessage();
    HostMessage& operator=(const HostMessage& other);
    virtual HostMessage *dup() const override {return new HostMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getSrc() const;
    virtual void setSrc(int src);
    virtual int getDest() const;
    virtual void setDest(int dest);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const HostMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, HostMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __HOSTMESSAGE_M_H

