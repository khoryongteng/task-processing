#pragma once

#include <thread>

#include "task_queue.h"

class ProducerManager
{
public:
    ProducerManager(TaskQueue& taskQueue, int numProducers) : m_taskQueue(taskQueue), m_numProducers(numProducers) {};
    void startProducers();
    void stopProducers();
    ~ProducerManager();
private:
    TaskQueue& m_taskQueue;
    std::vector<std::thread> m_producerThreads;
    int m_numProducers;
    void taskProducer(const int id);
};