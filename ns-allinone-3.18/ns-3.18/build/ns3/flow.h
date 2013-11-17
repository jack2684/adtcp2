/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef ADTCP_H
#define ADTCP_H

//#include "ns3/ipv4-end-point.h"
#include <iostream>
#include <cstdlib>
#include <list>
#include <map>

namespace ns3 {

typedef short unsigned int uint16_g;
typedef long unsigned int uint32_g;

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
    Flow(AddrPort newAddrPort);//: m_endPoint(m_endp) { };
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
    long long GetFlowSize();
    FlowSate_t GetAdctpState();
    AddrPort GetAddrPort();
    uint32_g GetrWnd();
    
    // Set stuff
    void SetAdctpState(Flow::FlowSate_t set);
    
    // operator
    bool operator== (Flow param);
    bool operator!= (Flow param);
    
  private: 
    // endPoint stores both local and peer's address + port
    AddrPort addrPort;
    // flow size
    long long m_flowSize;  
    // control the rWnd of receiver, in order to slow down the flow
    // uint16_g m_adtcpRWnd;
    // flow state
    FlowSate_t m_adtcpSate;
    // flow rWnd
    uint32_g m_rWnd;
    
  }; 
  
  typedef std::map<AddrPort, Flow> AddrPort2Flow;
}

#endif /* ADTCP_H */

