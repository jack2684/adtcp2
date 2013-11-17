/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef FST_H
#define FST_H

//#include "ns3/red-queue.h"
#include "flow.h"

#include <list>
#include <map>

namespace ns3 {
  // Flow schedule table
  class Fst
  {
  public:
    //Fst();
    
    // basic flow list operation
    int AddFlow(Flow f);
    int RmFlow(Flow f);
    
    // flow schedule methods
    //bool IsRegiter(Ipv4EndPoint* m_endPoint);           // check if it an end host
    //int FlowScheduleHandler(Flow f);         // begin flow schedule handler
    int FlowSchedule(Flow f);         // begin flow schedule
    bool ExcceedMaxTh();              // check if average queue size too long
    bool ExcceedMinTh();              // check if average queue size too small
    bool ToDecelerate(Flow f);        // check if this flow should be SlowDowned
    bool ToAccelerate(Flow f);        // check if this flow should be SpeedUpped
    
    // check error
    bool CheckValid(Flow f);
    bool FoundNothing(std::list<Flow>::iterator it);
    
    // Get Stuff
    //std::list<Flow>::iterator find(Flow f);
    std::list<Flow>::iterator Find(Flow f);
    
  private:
    // the flow schedule list
    typedef std::list<Flow> FlowList;
    FlowList m_flowList;

    // Queue limit in bytes / packets
    uint32_g m_queueLimit;
    // Min avg length threshold (bytes)
    double m_minTh;
    // Max avg length threshold (bytes), should be >= 2*minTh
    double m_maxTh;
    // Average queue length
    double m_qAvg;
    
    // iterator that point the current controled flow
    std::list<Flow>::iterator itCurrFlow;
  };
  
  
//  typedef std::map<RedQueue, Ipv4Address> Queue2Fst;
}

#endif /* ADTCP_H */

