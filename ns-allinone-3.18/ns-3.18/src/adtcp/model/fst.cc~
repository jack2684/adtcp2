/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "fst.h"

namespace ns3 { 
  int 
  Fst::AddFlow(Flow f)
  {
    if(CheckValid(f))  
      return -1; 
    
    std::list<Flow>::iterator it, itPre; 
    for(it = m_flowList.begin(); 
      it != m_flowList.end() && f.GetFlowSize() >= it->GetFlowSize(); 
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
  Fst::RmFlow(Flow f)
  {
    if(CheckValid(f))  
      exit(-1); 
    
    m_flowList.remove(f);
    
    return 0;
  }

  int 
  Fst::FlowSchedule(Flow f)
  {
    if(CheckValid(f))  
      exit(-1);  
      
    // if there is only 1 flow, we don't schedule
    if(m_flowList.size() > 1)
    {
      // if it is your time to be slow down..
      if(ToDecelerate(f))
      {
        // if average queue too long, we slow down (pause it)
        if(ExcceedMaxTh())
          return f.SlowDown(); 
      }else if(ToAccelerate(f))
      {
        // if average queue too short, we slow down (pause it)
        if(ExcceedMinTh())
          return f.SpeedUp(); 
      }
    }
    // no schedule
    return -1;
  }

  bool 
  Fst::ExcceedMaxTh()
  {
    return m_qAvg > m_maxTh ? true : false;
  }

  bool 
  Fst::ExcceedMinTh()
  {
    return m_qAvg < m_minTh ? true : false;
  }

  bool 
  Fst::ToDecelerate(Flow f)
  {
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
    if(f.GetEndPoint() == 0)  
    {
      std::cout << "Fst::AddFlow: f.m_endPoint is == 0, not set\n";
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

}















