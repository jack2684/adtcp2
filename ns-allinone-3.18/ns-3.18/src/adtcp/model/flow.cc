/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "flow.h"

namespace ns3 {

  uint16_t 
  Flow::SlowDown(float rate)
  {
    return SlowDown();
  }
  uint16_t 
  Flow::SpeedUp(float rate)
  {
    return SpeedUp();
  }
  uint16_t 
  Flow::SlowDown()
  {
    // this is the exact size of MSS
    return 536;
  }
  uint16_t 
  Flow::SpeedUp()
  {
    // means no flow control
    return -1;
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
  
  void
  Flow::SetAdctpState(Flow::FlowSate_t set)
  {
    m_adtcpSate = set;
  }
  
  Ipv4EndPoint* 
  Flow::GetEndPoint()
  {
    return m_endPoint;
  }
  
  bool 
  Flow::operator== (Flow param)
  {
    if(param.m_endPoint == m_endPoint
      && param.m_endPoint == m_endPoint
      && param.m_flowSize == m_flowSize
      && param.m_adtcpSate == m_adtcpSate)
      return true;
    else
      return false;
  }
  
  bool 
  Flow::operator!= (Flow param)
  {
    if(param.m_endPoint != m_endPoint
      || param.m_endPoint != m_endPoint
      || param.m_flowSize != m_flowSize
      || param.m_adtcpSate != m_adtcpSate)
      return false;
    else
      return true;
  }  
}















