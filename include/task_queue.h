#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "task.h"

class TaskQueue
{
public:
  void push(const Task& task);
  Task pop();
  void setDone();
private:
  std::queue<Task> m_queue {};
  std::mutex m_mutex;
  std::condition_variable m_cv;
  bool m_done = false;
};