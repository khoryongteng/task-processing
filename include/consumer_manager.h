#pragma once

#include <thread>

#include "task_queue.h"

class ConsumerManager
{
public:
    ConsumerManager(TaskQueue& taskQueue, int numConsumers) : m_taskQueue(taskQueue), m_numConsumers(numConsumers) {};
    void startConsumers();
    void stopConsumers();
    ~ConsumerManager();
private:
    TaskQueue& m_taskQueue;
    std::vector<std::thread> m_consumerThreads;
    int m_numConsumers;
    void taskConsumer(const int id);
};