#include "consumer_manager.h"

#include <iostream>

void ConsumerManager::startConsumers()
{
  for (int i = 0; i < m_numConsumers; ++i) {
    m_consumerThreads.push_back(std::thread(&ConsumerManager::taskConsumer, this, i));
  } 
}


void ConsumerManager::stopConsumers()
{
  for (auto& thread : m_consumerThreads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

ConsumerManager::~ConsumerManager()
{
  stopConsumers();
}

void ConsumerManager::taskConsumer(int id)
{
  while (true) {
    Task task = m_taskQueue.pop();
    if (task.getId() == -1) {
      break;
    }
    std::cout << "Consumer " << id << " processing Task " << task.getId() << " with data: " << task.getData() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}