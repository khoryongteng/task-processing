#include "producer_manager.h"
#include <iostream>

void ProducerManager::startProducers()
{
  for (int i = 0; i < m_numProducers; ++i) {
    m_producerThreads.push_back(std::thread(&ProducerManager::taskProducer, this, i));
  }
}

void ProducerManager::stopProducers()
{
  for (auto& thread : m_producerThreads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

ProducerManager::~ProducerManager()
{
  stopProducers();
}

void ProducerManager::taskProducer(int id)
{
  for (int i = 0; i < 10; ++i)
  {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      Task task(i, "Data from Producer " + std::to_string(id));
      m_taskQueue.push(task);
  }
}