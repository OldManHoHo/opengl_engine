//
//  TGLLibraryQueue.h
//  TGL_Server
//
//  Created by Teddy Walsh on 12/17/18.
//
//

#ifndef TGL_LIBRARYQUEUE_H_
#define TGL_LIBRARYQUEUE_H_

#include <stdio.h>
#include <deque>
#include <mutex>

template <class T>
class TGLLibraryQueue
{
    std::deque <T*> memory_queue;
    std::deque <T*> item_queue;
    std::mutex memory_queue_lock;
    std::mutex item_queue_lock;

    T prototype;

public:
    TGLLibraryQueue();
    void init_memory(int queue_length, T& item_prototype);
    void check_out_memory(T *& out_item);
    void push_front(T *& in_item);
    void pop_back(T *& out_item);
    void check_in_memory(T *& in_item);
};

//
//  TGLLibraryQueue.cpp
//  TGL_Server
//
//  Created by Teddy Walsh on 12/17/18.
//
//

template <class T>
TGLLibraryQueue<T>::TGLLibraryQueue()
{
}

template <class T>
void TGLLibraryQueue<T>::init_memory(int queue_length, T& item_prototype)
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
void TGLLibraryQueue<T>::check_out_memory(T *& out_item)
{
    std::lock_guard<std::mutex> Lock(memory_queue_lock);
    if (memory_queue.size() == 0)
    {
        T * temp_item = new T;
        *temp_item = prototype;
        memory_queue.push_back(temp_item);
	std::cout << "TGLLibraryQueue: Maxed out memory queue. New entry created." << "\n";
    }
    out_item = memory_queue.front();
    memory_queue.pop_front();
}

template <class T>
void TGLLibraryQueue<T>::push_front(T *& in_item)
{
    std::lock_guard<std::mutex> Lock(item_queue_lock);
    item_queue.push_front(in_item);
    in_item = nullptr;
}

template <class T>
void TGLLibraryQueue<T>::pop_back(T *& out_item)
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
void TGLLibraryQueue<T>::check_in_memory(T *& in_item)
{
    std::lock_guard<std::mutex> Lock(memory_queue_lock);
    memory_queue.push_front(in_item);
    in_item = nullptr;
}


#endif /* defined(__TGL_Server__TGLLibraryQueue__) */
