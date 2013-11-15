/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef FST_H
#define FST_H

#include "ns3/tcp-socket-base.h"
#include "ns3/red-queue.h"
#include "flow.h"

#include <list>

namespace ns3 {
  // Flow schedule table
  class Fst
  {
  public:
    Fst();
    
    // basic flow list operation
    int AddFlow(Flow f);
    int RmFlow(Flow f);
    
    // flow schedule methods
    int FlowSchedule(Flow f);         // begin flow schedule
    bool ExcceedMaxTh();              // check if average queue size too long
    bool ExcceedMinTh();              // check if average queue size too small
    bool ToDecelerate(Flow f);        // check if this flow should be SlowDowned
    bool ToAccelerate(Flow f);        // check if this flow should be SpeedUpped
    
    // check error
    bool CheckValid(Flow f);
    bool FoundNothing(std::list<Flow>::iterator it);
    
    // Get Stuff
    
  private:
    // the flow schedule list
    typedef std::list<Flow> FlowList;
    FlowList m_flowList;

    // Queue limit in bytes / packets
    uint32_t m_queueLimit;
    // Min avg length threshold (bytes)
    double m_minTh;
    // Max avg length threshold (bytes), should be >= 2*minTh
    double m_maxTh;
    // Average queue length
    double m_qAvg;
    
    // iterator that point the current controled flow
    std::list<Flow>::iterator itCurrFlow;
  };
  
  /*struct HostAddrPort
  {
      Ipv4Address addr;
      uint16_t port;
      HostAddrPort(Ipv4Address a, uint16_t p)
      {
          addr = a;
          port = p;
      }
  };*/
  
  typedef std::map<Ipv4Address, Fst> Host2Fst;
  typedef std::map<RedQueue, Ipv4Address> Queue2Fst;
}

#endif /* ADTCP_H */

