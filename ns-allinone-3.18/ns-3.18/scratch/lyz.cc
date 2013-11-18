/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

//******* GLOBAL CONSTANTS - BEGIN ******
#define LEVEL1_NUM 4
#define LEVEL2_NUM 10
#define LEVEL3_NUM (LEVEL2_NUM*GROUP_SIZE)
#define GROUP_SIZE 4
#define MAX_PAYLOAD 536
#define ACCESS_BW 1
#define AGGREGATE_BW 2
#define HEADER_LENGTH 40
bool debug = true;
bool debug2 = false;

//******* GLOBAL CONSTANTS - END******

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("FifthScriptExample");

//******* GLOBAL MAPPINGS - BEGIN ****** --- need to move to Global Static Class
Host2Fst H2F::h2f;
std::map<uint32_t, Ptr<Queue> > queuePtr;  //Ptr<Queue> q= map[ip_in_uint32];
std::vector<Ipv4Address> addrs; //Ipv4Address addr = addrs[host_id];  addr_in_uint32=addr.Get()
//******* GLOBAL MAPPINGS - END ******

//******* VARIABLES FOR PACKET SENDING - BEGIN ******
double GlobalEndTime = 200.0;

uint16_t sinkPort = 8080;

uint8_t *send_packet_buffer;
std::string level3DataRate = "10Mbps";
std::string level3Delay = "20ms";
std::string level2DataRate = "100Mbps";
std::string level2Delay = "20ms";

//******* VARIABLES FOR PACKET SENDING - END ******

class MyApp: public Application {
public:

	MyApp();
	virtual ~MyApp();

	void Setup(Ptr<Socket> socket, Address address, uint32_t packetSize,
			uint32_t nPackets, DataRate dataRate, uint64_t flowId);

private:
	virtual void StartApplication(void);
	virtual void StopApplication(void);

	void ScheduleTx(void);
	void SendPacket(void);

	Ptr<Socket> m_socket;
	Address m_peer;
	uint32_t m_packetSize;
	uint32_t m_nPackets;
	DataRate m_dataRate;
	EventId m_sendEvent;
	bool m_running;
	uint32_t m_packetsSent;
	uint64_t m_flowId;
};

MyApp::MyApp() :
		m_socket(0), m_peer(), m_packetSize(0), m_nPackets(0), m_dataRate(0), m_sendEvent(), m_running(
				false), m_packetsSent(0), m_flowId(0) {
}

MyApp::~MyApp() {
	m_socket = 0;
}

void MyApp::Setup(Ptr<Socket> socket, Address address, uint32_t packetSize,
		uint32_t nPackets, DataRate dataRate, uint64_t flowId) {
	m_socket = socket;
	m_peer = address;
	m_packetSize = packetSize;
	m_nPackets = nPackets;
	m_dataRate = dataRate;
	m_flowId = flowId;
}

void MyApp::StartApplication(void) {
	m_running = true;
	m_packetsSent = 0;
	m_socket->Bind();
	m_socket->Connect(m_peer);
	SendPacket();
}

void MyApp::StopApplication(void) {
	m_running = false;

	if (m_sendEvent.IsRunning()) {
		Simulator::Cancel(m_sendEvent);
	}

	if (m_socket) {
		m_socket->Close();
	}
}

void MyApp::SendPacket(void) {

	if (m_packetsSent == 0)

		send_packet_buffer[0] = 1;
	else
		send_packet_buffer[0] = 0;

	if (m_packetsSent == m_nPackets - 1)

		send_packet_buffer[1] = 1;
	else
		send_packet_buffer[1] = 0;

	((uint32_t *) (&send_packet_buffer[2]))[0] = m_nPackets; //Setting flowId at offset +2 byte

	((uint64_t *) (&send_packet_buffer[6]))[0] = m_flowId; //Setting flowId at offset +6 byte

	Ptr<Packet> packet = Create<Packet>(send_packet_buffer, m_packetSize);

	//printf("Sending packet: Uid=%llu ; Original size =%d ; flowId=%llu \n",
	//              packet->GetUid(), packet->GetSize(), m_flowId);

	int ret = m_socket->Send(packet);

	if (ret != -1) {
		if (++m_packetsSent < m_nPackets) {
			ScheduleTx();
		}
	} else {
		ScheduleTx();
	}
}

void MyApp::ScheduleTx(void) {
	if (m_running) {
		Time tNext(
				Seconds(
						m_packetSize * 8
								/ static_cast<double>(m_dataRate.GetBitRate())));
		m_sendEvent = Simulator::Schedule(tNext, &MyApp::SendPacket, this);

	}
}

static void GetFlowMetaData(Ptr<const Packet> p, uint64_t * ret_flowId,
		uint32_t *ret_packetNum) {

	if (p->GetSize() <= HEADER_LENGTH) {
		*ret_flowId = 0;

		*ret_packetNum = 0;
		return;
	}

	uint8_t const *buffer = p->PeekData();

	uint32_t packetNum = *((uint32_t *) (&(buffer[HEADER_LENGTH + 2])));

	*ret_packetNum = packetNum;

	uint64_t flowId = *((uint64_t *) (&(buffer[HEADER_LENGTH + 6])));
	*ret_flowId = flowId;

}

static void macSend(Ptr<const Packet> p) {

	//printf("%lf Sending Packet: Uid=%llu, Size = %d\n",
	//      Simulator::Now().GetSeconds(), p->GetUid(), p->GetSize());

}

static void macRecv(Ptr<const Packet> p) {

	uint64_t flowId;
	uint32_t packetNum;
	Ptr<Queue> q = queuePtr[addrs[39].Get()];

	GetFlowMetaData(p, &flowId, &packetNum);

	uint8_t flowStartSign = p->PeekData()[HEADER_LENGTH];
	uint8_t flowEndSign = p->PeekData()[HEADER_LENGTH + 1];

	uint32_t fstIp = ((uint32_t *) (&(p->PeekData()[16])))[0];

	H2F::h2f[fstIp].SetqAvg(q->m_qAvg);

	if (p->GetSize() > HEADER_LENGTH) {
		flowStartSign = p->PeekData()[HEADER_LENGTH];
		flowEndSign = p->PeekData()[HEADER_LENGTH + 1];
	} else {
		flowStartSign = 0;
		flowEndSign = 0;
	}

	if (flowStartSign == 1) {
		//TODO addFlow (flowId, packetNum);

		std::cout << ">>>>adding flow " << flowId << " at: " << fstIp
				<< std::endl;
		H2F::h2f[fstIp].AddFlow(flowId, packetNum);

		//TODO record start time of current flow
	}
	if (flowEndSign == 1) {
		//TODO deleteFlow (flowId)
		std::cout << ">>>>removing flow " << flowId << " at: " << fstIp
				<< std::endl;
		H2F::h2f[fstIp].RmFlow(flowId);
		//TODO record end time of current flow

		if (debug)
			printf(
					"%lf Received Packet: Uid=%llu, FlowStart=%d, FlowEnd=%d, packetSent=%u, Size = %d, flowId=%llu\n",
					Simulator::Now().GetSeconds(), p->GetUid(), flowStartSign,
					flowEndSign, packetNum, p->GetSize(), flowId);
		//Following is a example of how to access queue length.

		if (debug)
			printf("Queue avg length = %lf\n", q->m_qAvg); //TODO add m_qAvg to Queue.h

	}

	//The following allowing code snippet print the content of the packet.
	if (debug2) {
		std::cout << " >>";
		for (unsigned int i = 16; i < p->GetSize(); i++) {
			printf("%d ", p->PeekData()[i]);
		}
		printf("\n");
	}

//        uint32_t
//        dst_ip = ((uint32_t *)(&(p->PeekData()[16])))[0];
//        //dst_ip++;
//        //std:: cout << "the ip is here: "<< ((uint8_t * )dst_ip)[3] <<  std::endl;
//        std:: cout << "the ip is here: "<< dst_ip <<  std::endl;

}

void sendFlow(NodeContainer level3, int src, int dst, uint32_t packetNum,
		uint64_t flowId, double startTime, double endTime, std::string dataRate,
		uint16_t sinkPort) {

	Ptr<Socket> ns3TcpSocket = Socket::CreateSocket(level3.Get(src),
			TcpSocketFactory::GetTypeId());

	Address sinkAddress(InetSocketAddress(addrs[dst], sinkPort));

	Ptr<MyApp> app = CreateObject<MyApp>();
	app->Setup(ns3TcpSocket, sinkAddress, MAX_PAYLOAD, packetNum,
			DataRate(dataRate), flowId);

	level3.Get(src)->AddApplication(app);

	app->SetStartTime(Seconds(startTime));
	app->SetStopTime(Seconds(endTime));
}

int main(int argc, char *argv[]) {

	send_packet_buffer = (uint8_t *) malloc(sizeof(uint8_t) * 2000); // Init packet sending buffer

	//****************** Set up Topology - Begin ***************************

	PointToPointHelper pointToPoint;

	NodeContainer level1, level2, level3;

	level1.Create(LEVEL1_NUM);
	level2.Create(LEVEL2_NUM);
	level3.Create(LEVEL3_NUM);

	NodeContainer level3container[LEVEL3_NUM];

	InternetStackHelper stack;
	stack.Install(level1);
	stack.Install(level2);
	stack.Install(level3);

	uint32_t cur_addr = 0x07080900;

	//Fst *fst = new Fst[LEVEL3_NUM];
	for (unsigned int i = 0; i < LEVEL3_NUM; i++) {

		pointToPoint.SetDeviceAttribute("DataRate",
				StringValue(level3DataRate));
		pointToPoint.SetChannelAttribute("Delay", StringValue(level3Delay));

		pointToPoint.SetQueue(
				"ns3::RedQueue", // only backbone link has RED queue
				"LinkBandwidth", StringValue(level3DataRate), "LinkDelay",
				StringValue(level3Delay));

		NodeContainer nodes = level3container[i];

		nodes.Create(0);
		nodes.Add(level2.Get(i / GROUP_SIZE));
		nodes.Add(level3.Get(i));

		NetDeviceContainer devices;
		devices = pointToPoint.Install(nodes);

		Ipv4AddressHelper address;

		cur_addr += 4;
		Ipv4Address addr(cur_addr);

		address.SetBase(addr, "255.255.255.252");
		Ipv4InterfaceContainer interfaces = address.Assign(devices);

		// TODO register the fst of each machine
//		fst[i].Init(interfaces.GetAddress(1).Get(), 20, 5, 15);
//		H2F::h2f[interfaces.GetAddress(1).Get()] = fst[i];

		addrs.push_back(interfaces.GetAddress(1));

		Ptr<Queue> queue = pointToPoint.devB->GetQueue(); //done: Queue of endpoint TODO make devA and devB public in PointToPointDevice
		queuePtr[interfaces.GetAddress(1).Get()] = queue;

		if (debug) {
			std::cout << "Node " << i << " (" << addrs[i] << " pushback-ed)";
			interfaces.GetAddress(0).Print(std::cout);
			std::cout << " and ";
			interfaces.GetAddress(1).Print(std::cout);
			std::cout << "\n";
		}

		PacketSinkHelper packetSinkHelper("ns3::TcpSocketFactory",
				InetSocketAddress(Ipv4Address::GetAny(), sinkPort));
		ApplicationContainer sinkApps = packetSinkHelper.Install(nodes.Get(1));

		sinkApps.Start(Seconds(0.));
		sinkApps.Stop(Seconds(GlobalEndTime));

		devices.Get(1)->TraceConnectWithoutContext("MacTx",
				MakeCallback(&macSend));

		devices.Get(1)->TraceConnectWithoutContext("MacRx",
				MakeCallback(&macRecv));

	}

	NodeContainer level2container[LEVEL2_NUM][LEVEL1_NUM];

	for (unsigned int i = 0; i < LEVEL2_NUM; i++) {
		for (unsigned int j = 0; j < LEVEL1_NUM; j++) {

			pointToPoint.SetDeviceAttribute("DataRate",
					StringValue(level2DataRate));
			pointToPoint.SetChannelAttribute("Delay", StringValue(level2Delay));

			pointToPoint.SetQueue(
					"ns3::RedQueue", // only backbone link has RED queue
					"LinkBandwidth", StringValue(level2DataRate), "LinkDelay",
					StringValue(level2Delay));

			NodeContainer nodes = level2container[i][j];

			nodes.Create(0);
			nodes.Add(level2.Get(i));
			nodes.Add(level3.Get(j));

			NetDeviceContainer devices;
			devices = pointToPoint.Install(nodes);

			Ipv4AddressHelper address;

			cur_addr += 4;
			Ipv4Address addr(cur_addr);

			address.SetBase(addr, "255.255.255.252");
			Ipv4InterfaceContainer interfaces = address.Assign(devices);
			if (debug) {
				interfaces.GetAddress(0).Print(std::cout);
				std::cout << " and ";
				interfaces.GetAddress(1).Print(std::cout);
				std::cout << "--Router\n";
			}
		}
	}
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	if (debug)
		std::cout << "Topology generated.\n";
	NodeContainer endpoints = level3;

	//****************** Set up Topology - End ***************************

	sendFlow(level3, 0, 39, 1000, 66, 0, GlobalEndTime, "1Mbps", sinkPort);
	sendFlow(level3, 11, 39, 1000, 67, 0, GlobalEndTime, "1Mbps", sinkPort);
	sendFlow(level3, 22, 39, 1000, 68, 0, GlobalEndTime, "1Mbps", sinkPort);
	sendFlow(level3, 33, 39, 1000, 69, 0, GlobalEndTime, "1Mbps", sinkPort);

	Simulator::Stop(Seconds(GlobalEndTime));
	Simulator::Run();
	Simulator::Destroy();

	return 0;
}
