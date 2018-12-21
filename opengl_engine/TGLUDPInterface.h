
#include <sys/types.h>          /* See NOTES */
#ifdef _TGL_CLIENT
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#endif
#include <iostream>
#include <vector>
#include <thread>
#include <deque>
#include <map>
#include <algorithm>
#include <set>
#include <map>
#include <math.h>

#include "TGLLibraryQueue.h"



struct udp_address
{
	sockaddr_in addr;
	udp_address() {};
	udp_address(sockaddr_in in_addr) {addr = in_addr;}
	bool operator< (const udp_address& other) const
	{
		return addr.sin_port*pow(2,32) + addr.sin_addr.s_addr < other.addr.sin_port*pow(2,32) + other.addr.sin_addr.s_addr;
	}
};

class TGLUDPInterface 
{
public:
	std::thread * receive_thread;
	std::mutex msg_queue_mutex;
	//std::deque <std::vector<char> > msg_queue;
	//std::map <udp_address,std::deque<std::vector <char> > > msg_qs;

    
    TGLLibraryQueue<std::pair<sockaddr_in,std::vector<char>>> buffer_queue;

	sockaddr_in my_send_addr;
	sockaddr_in my_recv_addr;
#ifdef _TGL_CLIENT
	SOCKET send_sock;
	SOCKET recv_sock;
#else
	int send_sock;
	int recv_sock;
#endif
	TGLUDPInterface();
	int s_bind(std::string ip, int receive_port, int send_port);
	int s_send(std::vector <char>& in_msg, std::string ip, int port);
	int s_send(std::vector <char>& in_msg, sockaddr_in in_addr);
	void send_to_all(std::vector <char>& in_msg);
	int s_recv(std::vector <char>& out_msg, sockaddr_in * from_addr);
	void start_receive_thread();
	void receive_loop();
	void pop_msg(std::pair <sockaddr_in,std::vector<char>>*& out_pair);
	void return_msg(std::pair <sockaddr_in,std::vector<char>>*& in_pair);
};