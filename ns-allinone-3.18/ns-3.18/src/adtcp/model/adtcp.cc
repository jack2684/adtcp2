/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "adtcp.h"

namespace ns3 {

  bool debug = true;
  bool debug2 = true;
  bool debug3 = true;

  Fst::Fst(uint32_g localAddr, uint32_g queueLimit, double minTh, double maxTh)
    :m_localAddr(localAddr),
    m_queueLimit(queueLimit),
    m_minTh(minTh),
    m_maxTh(maxTh)
  {
    if(debug2) std::cout << "\t Fst::Fst, max and min:" << m_maxTh << ", " << m_minTh << std::endl;
    
  }

  void
  Fst::Init(uint32_g localAddr, uint32_g queueLimit, double minTh, double maxTh)
  {
    m_localAddr = localAddr;
    m_queueLimit = queueLimit;
    m_minTh = minTh;
    m_maxTh = maxTh;
  }

  Fst::FlowList
  Fst::GetFlowList()
  {
    return m_flowList;
  }

  double
  Fst::GetMinTh()
  {
    return m_minTh;
  }
  double 
  Fst::GetMaxTh()
  {
    return m_maxTh;
  }

  int 
  Fst::AddFlow(Flow f)
  {
    if(debug) std::cout << "\t Fst::AddFlow\n";
    if(!CheckValid(f))  
      return -1; 
    
    std::list<Flow>::iterator it, itPre; 
    for(it = m_flowList.begin(); 
      it != m_flowList.end() && f.GetFlowSize() > it->GetFlowSize(); 
      it++ ) { }
    
    if(m_flowList.size() == 0)
    {
      f.SetAdctpState(Flow::ACTIVE);
    }else
    {
      if(it == m_flowList.begin())
      {
        f.SetAdctpState(Flow::ACTIVE);
      }else
      {
        itPre = it;
        itPre--;
        f.SetAdctpState(itPre->GetAdctpState());
      }   
    }   
    
    m_flowList.insert(it, f);
    return 0;
  }

  int 
  Fst::AddFlow(uint64_g flowId, uint32_g flowSize)
  {
    if(debug) std::cout << "Fst::AddFlow\n";
    Flow f(flowId, flowSize);
    if(!CheckValid(f))  
      return -1;     
      
    std::set<uint64_g>::iterator setit = m_flowIdSet.find(flowId);
    if(setit != m_flowIdSet.end())
    {
      if(debug2) 
      {      
        std::cout << "AddFlow: duplicate flow adding\n";
        std::cout << "current flow set size " << m_flowIdSet.size() << std::endl;
        std::cout << "current flow list size " << m_flowList.size() << std::endl;
        std::cout << flowId << " -- this is the IDs:\n";    
        std::list<Flow>::iterator fit = m_flowList.begin();
        for(; fit != m_flowList.end(); fit++)
        {
          std::cout << "printing flowIds: " << fit->GetFlowId() << std::endl;
        }         
      }
      return -1;
    }
    m_flowIdSet.insert(flowId);
    
    if(debug2) std::cout << "Fst::FlowSchedule: flow number: " << m_flowList.size() + 1 << std::endl;
    
    std::list<Flow>::iterator it, itPre; 
    // to find the right position, sort by flow size
    for(it = m_flowList.begin(); 
      it != m_flowList.end() && f.GetFlowSize() >= it->GetFlowSize(); 
      it++ ) { }
    
    // to determin if the state of this new comming flow
    if(m_flowList.size() == 0)
    {
      f.SetAdctpState(Flow::ACTIVE);
    }else
    {
      if(it == m_flowList.begin())
      {
        f.SetAdctpState(Flow::ACTIVE);
      }else
      {
        itPre = it;
        itPre--;
        f.SetAdctpState(itPre->GetAdctpState());
      }   
    }   
    
    m_flowList.insert(it, f);
    return 0;
  }

  int 
  Fst::RmFlow(Flow f)
  {
    if(debug) std::cout << "\t Fst::RmFlow\n";
    if(!CheckValid(f))  
      exit(-1); 
    
    m_flowIdSet.erase(f.GetFlowId());
    m_flowList.remove(f);
    
    // make sure there is at least one ACTIVE flow 
    if(m_flowList.front().GetAdctpState() != Flow::ACTIVE)
      m_flowList.front().SetAdctpState(Flow::ACTIVE);
    
    return 0;
  }

  int 
  Fst::RmFlow(uint64_g flowId)
  {
    if(debug) std::cout << " Fst::RmFlow\n";
    
    
    std::list<Flow>::iterator fit = Find(flowId);
    if(fit != m_flowList.end())
    {
      if(debug2) std::cout << "removing flow: " << flowId << std::endl;
      m_flowList.erase(fit);
      m_flowIdSet.erase(flowId);
      // make sure there is at least one ACTIVE flow 
      if(m_flowList.front().GetAdctpState() != Flow::ACTIVE)
        m_flowList.front().SetAdctpState(Flow::ACTIVE);
    }
    else
    {
      if(debug2)
      {        
        std::cout << flowId << " -- cannot remove the non-exisitng flow\n";    
        std::cout << "current flow list size " << m_flowList.size() << std::endl;
        //std::list<Flow>::iterator fit = m_flowList.begin();
        //for(; fit != m_flowList.end(); fit++)
        //{
          //std::cout << "priting flowIds: " << fit->GetFlowId() << std::endl;
        //}        
      }
                    
      return -1;
    }
    
    return 0;
  }

  int 
  Fst::FlowSchedule(uint64_g flowId)
  {
    if(debug) std::cout << "Fst::FlowSchedule\n";
      
    std::list<Flow>::iterator fit = Find(flowId);
    if(fit == m_flowList.end())
    {
      if(debug) std::cout << flowId << " -- this flow not found!!\n";
    }
    
    if(debug3)
    {
      std::cout << "printing fst:\n";
      std::list<Flow>::iterator fit = m_flowList.begin();
      for(; fit != m_flowList.end(); fit++)
      {
        std::cout << fit->GetFlowId() << "\t" << fit->GetAdctpState() << std::endl;
      }
    }
      
    // if there is only 1 flow, we don't schedule
    if(debug2) std::cout << "Fst::FlowSchedule: flow number: " << m_flowList.size() << std::endl;
    if(m_flowList.size() > 1)
    {
      // if it is your time to be slow down..
      if(ToDecelerate(*fit))
      {
        // if average queue too long, we slow down (pause it)
        if(ExcceedMaxTh())
          (*fit).SlowDown(); 
      }else if(ToAccelerate(*fit))
      {
        // if average queue too short, we slow down (pause it)
        if(ExcceedMinTh())
          (*fit).SpeedUp(); 
      }
    }
    // no schedule
    return -1;
  }
  
  /*int 
  Fst::FlowScheduleHandler(Flow f)
  {
    // check if the 
    if(fst.IsRegiter(f.m_endPoint))
    {
      AddrPort currAddrPort(m_endPoint->GetLocalAddress(), m_endPoint->GetLocalPort());
      fst.FlowSchedule(ap2f[currAddrPort]);
    }
    return 0;
  }*/

  bool 
  Fst::ExcceedMaxTh()
  {
    if(debug2) std::cout << "\t Fst::ExcceedMaxTh: " << m_qAvg - m_maxTh << "\n";
    return m_qAvg > m_maxTh ? true : false;
  }

  bool 
  Fst::ExcceedMinTh()
  {
    if(debug2) std::cout << "\t Fst::ExcceedMinTh: " << -m_qAvg + m_minTh << "\n";
    return m_qAvg < m_minTh ? true : false;
  }

  bool 
  Fst::ToDecelerate(Flow f)
  {
    if(debug) std::cout << "\t Fst::ToDecelerate\n";
    std::list<Flow>::iterator it;
    
    // locate the current flow
    for(it = m_flowList.begin(); f != *it; it++ ) 
      if(FoundNothing(it))
        exit(-1);
    
    if(f.GetAdctpState() == Flow::ACTIVE)  
    {
      if(*it == m_flowList.front())
      {
        // we don't slow the only active flow
        return false;
      }else if(*it == m_flowList.back()
        || (++it)->GetAdctpState() == Flow::INACTIVE )
      {
        // check if it is the least prior flow
        return true;
      }
    }    
    return false;
  }

  bool 
  Fst::ToAccelerate(Flow f)
  {
    if(debug) std::cout << "\t Fst::ToAccelerate\n";
    std::list<Flow>::iterator it;
    
    // locate the current flow
    for(it = m_flowList.begin(); f != *it; it++ ) 
      if(FoundNothing(it))
        exit(-1);
    
    if(f.GetAdctpState() == Flow::INACTIVE)  
    {
      if((*it) == m_flowList.front())
      {
        std::cout << "Fst::ToAccelerate: all flows is INACTIVE\n";
        exit(-1);
      }
      // check if it is the least prior flow
      if((--it)->GetAdctpState() == Flow::ACTIVE )
        return true;
    }    
    return false;
  }

  // check if the input of flow is valid
  bool 
  Fst::CheckValid(Flow f)
  {
    // seems it is impossible to check the valid of a flow
    return true;
    if(debug) std::cout << "\t Fst::CheckValid\n";
    if(f.GetFlowId() == 0)  
    {
      std::cout << "Fst::AddFlow: f.GetFlowId() is 0, not set\n";
      return false;
    }else
      return true;
  }

  // check if we find nothing in iteration
  bool 
  Fst::FoundNothing(std::list<Flow>::iterator it)
  {
      if(it == m_flowList.end())
      {
        std::cout << "Fst::ToDecelerate: flow not found !\n";
        return true;
      }else
      {
        return false;
      }
  }
  
  void 
  Fst::SetqAvg(double qAvg)
  {
    m_qAvg = qAvg;
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  /*bool 
  Fst::IsRegiter(Ipv4EndPoint* m_endPoint)
  {
    std::list<Flow>::iterator fit = h2f.begin();
    for(; fit != h2f.end() && *fit != m_endPoint->m_localAddr; fit++)
    std::list<Flow>::iterator fit = find()
    if(fit != h2f.end())
    {
      return true;
    }
    else
      return false;
  }*/
  
  std::list<Flow>::iterator 
  Fst::Find(Flow f)
  {
    if(debug) std::cout << "\t Fst::Find\n";
    std::list<Flow>::iterator fit = m_flowList.begin();
    for(; fit != m_flowList.end() && *fit != f; fit++){}
    //if(debug && fit != m_flowList.end()) std::cout << "\t\t Fst::Find: flow found! " ;
    return fit;
  }

  std::list<Flow>::iterator 
  Fst::Find(uint32_g flowId)
  {
    if(debug) std::cout << "\t Fst::Find\n";
    std::list<Flow>::iterator fit = m_flowList.begin();
    for(; fit != m_flowList.end() && fit->GetFlowId() != flowId; fit++)
    {
//      if(debug2) std::cout << "comparing flowid: " << fit->GetFlowId() << " and " << 
    }
    //if(debug && fit != m_flowList.end()) std::cout << "\t\t Fst::Find: flow found! " ;
    return fit;
  }

  Flow::Flow(AddrPort newAddrPort, uint32_g flowSize)
  {
    addrPort = newAddrPort;
    m_flowSize = flowSize;
    m_adtcpSate = ACTIVE;
    m_rWnd = -1;
  }
  
  Flow::Flow(uint64_g flowId, uint32_g flowSize)
  {
    m_flowId = flowId;
    m_flowSize = flowSize;
    m_adtcpSate = ACTIVE;
    m_rWnd = -1;
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
    if(debug2) std::cout << "\t Flow::SlowDown\n";
    // this is the exact size of MSS
    m_adtcpSate = INACTIVE;
    m_rWnd = 536;
  }
  void
  Flow::SpeedUp()
  {
    if(debug2) std::cout << "\t Flow::SpeedUp\n";
    // means no flow control
    m_adtcpSate = ACTIVE;
    m_rWnd = -1;
  }

  uint32_g 
  Flow::GetFlowId()
  {
    return m_flowId;
  }

  uint32_g
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
    if(param.m_flowId == m_flowId
      /*&& param.m_flowSize == m_flowSize
      && param.m_adtcpSate == m_adtcpSate*/)
      return true;
    else
      return false;
  }
  
  bool 
  Flow::operator!= (Flow param)
  {
    if(param.m_flowId != m_flowId
      /*|| param.addrPort != addrPort
      || param.m_flowSize != m_flowSize
      || param.m_adtcpSate != m_adtcpSate*/)
      return true;
    else
      return false;
  }  
    
}






















