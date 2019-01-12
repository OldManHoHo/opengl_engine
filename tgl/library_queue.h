//
//  LibraryQueue.h
//  TGL_Server
//
//  Created by Teddy Walsh on 12/17/18.
//
//

#ifndef TGL_LIBRARY_QUEUE_H_
#define TGL_LIBRARY_QUEUE_H_

#include <stdio.h>
#include <deque>
#include <mutex>

namespace tgl
{

template <class T>
class LibraryQueue
{
    std::deque <T*> memory_queue;
    std::deque <T*> item_queue;
    std::mutex memory_queue_lock;
    std::mutex item_queue_lock;

    T prototype;

 public:
    LibraryQueue();
    void init_memory(int queue_length, T& item_prototype);
    void check_out_memory(T *& out_item);
    void push_front(T *& in_item);
    void pop_back(T *& out_item);
    void check_in_memory(T *& in_item);
};

template <class T>
LibraryQueue<T>::LibraryQueue()
{
}

template <class T>
void LibraryQueue<T>::init_memory(int queue_length, T& item_prototype)
{
    prototype = item_prototype;
    for (int i = 0; i < queue_length; ++i)
    {
        T * temp_item = new T;
        *temp_item = item_prototype;
        memory_queue.push_back(temp_item);
    }
}

template <class T>
void LibraryQueue<T>::check_out_memory(T *& out_item)
{
    std::lock_guard<std::mutex> Lock(memory_queue_lock);
    if (memory_queue.size() == 0)
    {
        T * temp_item = new T;
        *temp_item = prototype;
        memory_queue.push_back(temp_item);
        std::cout <<
            "tgl/LibraryQueue: Maxed out memory queue. New entry created." <<
            "\n";
    }
    out_item = memory_queue.front();
    memory_queue.pop_front();
}

template <class T>
void LibraryQueue<T>::push_front(T *& in_item)
{
    std::lock_guard<std::mutex> Lock(item_queue_lock);
    item_queue.push_front(in_item);
    in_item = nullptr;
}

template <class T>
void LibraryQueue<T>::pop_back(T *& out_item)
{
    std::lock_guard<std::mutex> Lock(item_queue_lock);
    if (item_queue.size())
    {
        out_item = item_queue.back();
        item_queue.pop_back();
    }
    else
    {
        out_item = nullptr;
    }
}

template <class T>
void LibraryQueue<T>::check_in_memory(T *& in_item)
{
    std::lock_guard<std::mutex> Lock(memory_queue_lock);
    memory_queue.push_front(in_item);
    in_item = nullptr;
}

}  // namespace tgl

#endif  // TGL_LIBRARY_QUEUE_H_
