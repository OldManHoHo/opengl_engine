#include <sys/types.h>          /* See NOTES */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <deque>
#include <algorithm>
#include <set>
#include <map>


struct udp_address
{
	sockaddr_in addr;
	udp_address(sockaddr_in in_addr) {addr = in_addr;}
	bool operator< (const udp_address& other) const
	{
		return addr.sin_port*pow(2,32) + addr.sin_addr.s_addr < other.addr.sin_port*pow(2,32) + other.addr.sin_addr.s_addr;
	}
};




class TGLUDPInterface
{
public:
	static const int max_msg_size = 1024;

	int sock;
	struct sockaddr_in my_address;
	std::vector <sockaddr_in> peers;
	TGLUDPInterface();
	bool init(std::string ip_address, int port);

	std::thread * receive_thread;
	std::mutex msg_queue_mutex;
	std::deque <std::vector<uint8_t> > msg_queue;
	//std::set <struct sockaddr_in> clients;
	//std::unordered_map <struct sockaddr_in, std::deque<std::vector <uint8_t> > > msg_qs;
	std::map <udp_address,std::deque<std::vector <uint8_t> > > msg_qs;
	//std::map <int, int> msg_qs;

	int send_msg(std::vector<uint8_t> in_msg, sockaddr_in * to_addr);
	int receive_msg(std::vector <uint8_t> out_msg, std::string& ip_address, int& port);
	std::vector<uint8_t> receive_msg(sockaddr_in * from_addr);
	void start_receive_thread();
	void receive_loop();
	std::vector <uint8_t> pop_msg(sockaddr_in * in_addr);
};	
