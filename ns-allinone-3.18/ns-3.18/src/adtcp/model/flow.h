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
    
    // Set stuff
    void SetAdctpState(Flow::FlowSate_t set);
    
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
}

#endif /* ADTCP_H */

