/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef ADTCP_H
#define ADTCP_H

#include "ns3/tcp-socket-base.h"

#include <list>

namespace ns3 {

/* ... */
  class Flow
  {
  public:
    Flow();
    Flow(Ipv4EndPoint* m_endPoint);
    Flow(Ipv4EndPoint* m_endPoint, long long m_flowSize);

    typedef enum {
      ACTIVE,       // 0
      INACTIVE,       // 1
    } FlowSate_t;
    
    // basic flow control
    // almost pause the flow
    uint16_t SlowDown();
    uint16_t SpeedUp();
    // gently slowDown or speedUp, currently it is just the same as above two 
    uint16_t SlowDown(float rate);
    uint16_t SpeedUp(float rate);
   
    // Get stuff
    long long GetFlowSize();
    FlowSate_t GetAdctpState();
    Ipv4EndPoint* GetEndPoint();
    
    // operator
    bool operator== (Flow param);
    bool operator!= (Flow param);
    
  private: 
    // endPoint stores both local and peer's address + port
    Ipv4EndPoint* m_endPoint;
    // flow size
    long long m_flowSize;  
    // control the rWnd of receiver, in order to slow down the flow
    //uint16_t m_adtcpRWnd;
    // flow state
    FlowSate_t m_adtcpSate;
  }; 


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
  
  struct HostAddrPort
  {
      Ipv4Address addr;
      uint16_t port;
      HostAddrPort(Ipv4Address a, uint16_t p)
      {
          addr = a;
          port = p;
      }
  };
  
  typedef std::map<HostAddrPort, Fst> FstMapper;
}

#endif /* ADTCP_H */

