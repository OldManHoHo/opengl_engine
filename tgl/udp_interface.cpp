#include "tgl/udp_interface.h"

#ifdef _TGL_CLIENT
#pragma comment(lib, "Ws2_32.lib")
#define inet_pton InetPton
#endif

namespace tgl
{

UDPInterface::UDPInterface()
{
#ifdef _TGL_CLIENT
    // Initialize Winsock
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
    }
#endif
    std::vector <char> proto_buf(1460);
    sockaddr_in proto_addr;
    std::pair<sockaddr_in, std::vector <char>> proto_pair(proto_addr, proto_buf);
    buffer_queue.init_memory(10, proto_pair);
    send_sock = socket(AF_INET, SOCK_DGRAM, 0);
    recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
}

int UDPInterface::s_bind(std::string ip, int receive_port, int send_port)
{
    my_recv_addr.sin_family = AF_INET;
    my_recv_addr.sin_port = htons(receive_port);
    my_send_addr.sin_family = AF_INET;
    my_send_addr.sin_port = htons(send_port) + 1;
    // inet_aton(ip.c_str(), &my_addr.sin_addr);
    inet_pton(AF_INET, ip.c_str(), &my_recv_addr.sin_addr);
    inet_pton(AF_INET, ip.c_str(), &my_send_addr.sin_addr);
    bind(recv_sock,
         reinterpret_cast<sockaddr*>(&my_recv_addr),
         sizeof(my_recv_addr));
    return bind(send_sock,
                reinterpret_cast<sockaddr*>(&my_send_addr),
                sizeof(my_send_addr));
}

int UDPInterface::s_send(std::vector <char>& in_msg, std::string ip, int port)
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // std::cout <<
    //      "Sent packet to: " <<
    //      addr.sin_port <<
    //      ", " <<
    //      port <<
    //      ", size: " <<
    //      in_msg.size() <<
    //      "\n";
    // inet_aton(ip.c_str(), &addr.sin_addr);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
    return sendto(send_sock,
                  &in_msg[0],
                  in_msg.size(),
                  0,
                  reinterpret_cast<sockaddr*>(&addr),
                  sizeof(addr));
}

int UDPInterface::s_send(std::vector <char>& in_msg, sockaddr_in in_addr)
{
    in_addr.sin_port = htons(in_addr.sin_port);
    return sendto(send_sock,
                  &in_msg[0],
                  in_msg.size(),
                  0,
                  reinterpret_cast<sockaddr*>(&in_addr),
                  sizeof(in_addr));
}

// TODO(Teddy Walsh): Implement or delete. NOT USED
void UDPInterface::send_to_all(std::vector <char>& in_msg)
{
}

int UDPInterface::s_recv(std::vector <char>& out_msg, sockaddr_in * from_addr)
{
#ifdef _TGL_CLIENT
    int out_len;
#else
    socklen_t out_len;
#endif
    out_len = sizeof(sockaddr_in);
    int ret_length = recvfrom(recv_sock,
                              &out_msg[0],
                              static_cast<int>(out_msg.size()),
                              0,
                              reinterpret_cast<sockaddr*>(from_addr),
                              &out_len);
    // std::cout << "Received msg size: " << ret_length << "\n";
    from_addr->sin_port = ntohs(from_addr->sin_port);
    out_msg.resize(ret_length);
    return ret_length;
}

void UDPInterface::start_receive_thread()
{
    receive_thread = new std::thread(
                                     [&] (UDPInterface * player)
                                     {
                                         player->receive_loop();
                                     },
                                     this);
    std::cout << "Started UDPInterface receive thread" << "\n";
}

void UDPInterface::receive_loop()
{
    // std::vector <char>* recv_buffer;
    std::pair <sockaddr_in, std::vector <char>>* recv_buffer;
    while (1)
    {
        buffer_queue.check_out_memory(recv_buffer);
        recv_buffer->second.resize(1460);
        s_recv((*recv_buffer).second, &(recv_buffer->first));
        std::cout << "First char: " << int((*recv_buffer).second[0]) << "\n";
        buffer_queue.push_front(recv_buffer);
    }
}

void UDPInterface::pop_msg(
        std::pair <sockaddr_in, std::vector<char>>*& out_pair)
{
    buffer_queue.pop_back(out_pair);
}

void UDPInterface::return_msg(
        std::pair <sockaddr_in, std::vector<char>>*& in_pair)
{
    buffer_queue.check_in_memory(in_pair);
}

}  // namespace tgl
