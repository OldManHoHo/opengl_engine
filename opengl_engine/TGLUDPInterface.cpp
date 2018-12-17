#include "TGLUDPInterface.h"
TGLUDPInterface::TGLUDPInterface()
{
    std::vector <char> proto_buf(1024);
    sockaddr_in proto_addr;
    std::pair<sockaddr_in, std::vector <char>> proto_pair(proto_addr, proto_buf);
    buffer_queue.init_memory(10,proto_pair);
    sock = socket(AF_INET, SOCK_DGRAM,0);
}
int TGLUDPInterface::s_bind(std::string ip, int port)
{
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = port;
    inet_aton(ip.c_str(), &my_addr.sin_addr);
    return bind(sock, (sockaddr*)&my_addr, sizeof(my_addr));
}

int TGLUDPInterface::s_send(std::vector <char> in_msg, std::string ip, int port)
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    inet_aton(ip.c_str(), &addr.sin_addr);
    return sendto(sock, &in_msg[0], in_msg.size(), 0, (sockaddr*)&addr, sizeof(addr));
}

int TGLUDPInterface::s_recv(std::vector <char>& out_msg, sockaddr_in * from_addr)
{
    socklen_t out_len;
    return recvfrom(sock, &out_msg[0], out_msg.size(), 0, (sockaddr*)from_addr, &out_len); 	
}

void TGLUDPInterface::start_receive_thread()
{
    receive_thread = new std::thread([&] (TGLUDPInterface * player) { player->receive_loop(); }, this);	
}

void TGLUDPInterface::receive_loop()
{
    //std::vector <char>* recv_buffer;
    std::pair <sockaddr_in, std::vector <char>>* recv_buffer;
    while(1)
    {
        buffer_queue.check_out_memory(recv_buffer);
        s_recv((*recv_buffer).second, &(*recv_buffer).first);
        buffer_queue.push_front(recv_buffer);
    }
}

std::vector <char> TGLUDPInterface::pop_msg(sockaddr_in * in_addr)
{
    std::pair <sockaddr_in, std::vector <char>>* out_pair;
    buffer_queue.pop_back(out_pair);
    std::vector <char> out_vector = out_pair->second;
    buffer_queue.check_in_memory(out_pair);
    *in_addr = out_pair->first;
    return out_vector;
}
