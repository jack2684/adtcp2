/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "flow.h"

namespace ns3 {
  Flow::Flow(AddrPort newAddrPort)
  {
    addrPort = newAddrPort;
  }

  void
  Flow::SlowDown(float rate)
  {
     SlowDown();
  }
  void
  Flow::SpeedUp(float rate)
  {
    return SpeedUp();
  }
  void
  Flow::SlowDown()
  {
    // this is the exact size of MSS
    m_adtcpSate = INACTIVE;
    m_rWnd = 536;
  }
  void
  Flow::SpeedUp()
  {
    // means no flow control
    m_adtcpSate = ACTIVE;
    m_rWnd = -1;
  }

  long long
  Flow::GetFlowSize()
  {
    return m_flowSize;
  }

  Flow::FlowSate_t 
  Flow::GetAdctpState()
  {
    return m_adtcpSate;
  }
  
  uint32_g 
  Flow::GetrWnd()
  {
    return m_rWnd;
  }
  
  void
  Flow::SetAdctpState(Flow::FlowSate_t set)
  {
    m_adtcpSate = set;
  }
  
  AddrPort 
  Flow::GetAddrPort()
  {
    return addrPort;
  }
  
  bool 
  Flow::operator== (Flow param)
  {
    if(param.addrPort == addrPort
      && param.m_flowSize == m_flowSize
      && param.m_adtcpSate == m_adtcpSate)
      return true;
    else
      return false;
  }
  
  bool 
  Flow::operator!= (Flow param)
  {
    if(param.addrPort != addrPort
      || param.addrPort != addrPort
      || param.m_flowSize != m_flowSize
      || param.m_adtcpSate != m_adtcpSate)
      return false;
    else
      return true;
  }  
    
}















