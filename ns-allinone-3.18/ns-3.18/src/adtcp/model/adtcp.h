/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef ADTCP_H
#define ADTCP_H 1

#include "ns3/ipv4.h"
#include "ns3/ipv4-interface-address.h"

#include <iostream>
#include <cstdlib>
#include <list>
#include <map>
#include <list>

namespace ns3 {

typedef short unsigned int uint16_g;
typedef long unsigned int uint32_g;
typedef unsigned long long uint64_g;

/* ... */

  class AddrPort
  {   
  public:
      unsigned long int lAddr;
      unsigned int lPort;
      unsigned long int pAddr;
      unsigned int pPort;
      
      AddrPort()
      {
          lAddr = 0;
          lPort = 0;
          pAddr = 0;
          pPort = 0;      
      };
      AddrPort(unsigned long int a1, unsigned int p1,
                unsigned long int a2, unsigned int p2)
      {
          lAddr = a1;
          lPort = p1;
          pAddr = a2;
          pPort = p2;
      }
      void operator= (AddrPort param)
      {
          lAddr = param.lAddr;
          lPort = param.lAddr;
          pAddr = param.pAddr;
          pPort = param.pPort;        
      }
      bool operator!= (AddrPort param)
      {
          if(lAddr != param.lAddr
          || lPort != param.lAddr
          || pAddr != param.pAddr
          || pPort != param.pPort)
            return false;
          else
            return true;
      }
      bool operator== (AddrPort param)
      {
          if(lAddr == param.lAddr
          && lPort == param.lAddr
          && pAddr == param.pAddr
          && pPort == param.pPort)
            return true;
          else
            return false;
      }
  };

  class Flow
  {
  public:
    //Flow();
    Flow(AddrPort newAddrPort, uint32_g flowSize);//: m_endPoint(m_endp) { };
    Flow(uint64_g flowId, uint32_g flowSize);//: m_endPoint(m_endp) { };
    /*{
      this->m_endPoint = m_endPoint;
    }*/
    //Flow(Ipv4EndPoint* m_endPoint, long long m_flowSize);

    typedef enum {
      ACTIVE,       // 0
      INACTIVE,       // 1
    } FlowSate_t;     
    
    // basic flow control
    // almost pause the flow
    void SlowDown();
    void SpeedUp();
    // gently slowDown or speedUp, currently it is just the same as above two 
    void SlowDown(float rate);
    void SpeedUp(float rate);
   
    // Get stuff
    uint32_g GetFlowSize();
    FlowSate_t GetAdctpState();
    AddrPort GetAddrPort();
    uint32_g GetrWnd();
    uint32_g GetFlowId();
    
    // Set stuff
    void SetAdctpState(Flow::FlowSate_t set);
    
    // operator
    bool operator== (Flow param);
    bool operator!= (Flow param);
    
  private: 
    // endPoint stores both local and peer's address + port
    AddrPort addrPort;
    // the flow id
    uint64_g m_flowId;
    // flow size
    uint32_g m_flowSize;  
    // control the rWnd of receiver, in order to slow down the flow
    // uint16_g m_adtcpRWnd;
    // flow state
    FlowSate_t m_adtcpSate;
    // flow rWnd
    uint32_g m_rWnd;

  }; 
  
  
    // Flow schedule table
  class Fst
  {
  public:
    Fst(){}
    Fst(uint32_g localAddr, uint32_g queueLimit, double minTh, double maxTh);
    void Init(uint32_g localAddr, uint32_g queueLimit, double minTh, double maxTh);
    
    typedef std::list<Flow> FlowList;
    
    // basic flow list operation
    int AddFlow(Flow f);
    int AddFlow(uint64_g flowId, uint32_g flowSize);
    int RmFlow(Flow f);
    int RmFlow(uint64_g flowId);
    
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
    std::list<Flow>::iterator Find(uint32_g flowId);
    FlowList GetFlowList();
    double GetMinTh();
    double GetMaxTh();
    
    // Set Stuff
    void SetqAvg(double qAvg);
    
  public:
    // the flow schedule list
    FlowList m_flowList;
    // local adress of fst
    uint32_g m_localAddr;
    // Queue limit in bytes / packets
    uint32_g m_queueLimit;
    // Min avg length threshold (bytes)
    double m_minTh;
    // Max avg length threshold (bytes), should be >= 2*minTh
    double m_maxTh;
    // Average queue length
    double m_qAvg;
    // exisitng flowId, in case of duplicate
    std::set<uint64_g> m_flowIdSet;
    
    // iterator that point the current controled flow
    std::list<Flow>::iterator itCurrFlow;
  };
  
  // this is very important, for global variable 
  // if you want to  use global variable, like h2f in the below
  // you should make statement of a static variable,
  // and then at the .cc you should define such as 'Host2Fst H2F::h2f' globally,
  // (without using extern), then you can use it globally
  typedef std::map<uint32_g, Fst> Host2Fst;
  class H2F
  {
  public:
     static Host2Fst h2f;
     //static int abcabc;
  };
  

  
//  typedef std::map<RedQueue, Ipv4Address> Queue2Fst;
}

#endif /* ADTCP_H */

