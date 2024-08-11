#include "task_queue.h"

void TaskQueue::push(const Task& task)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_queue.push(task);
  m_cv.notify_one();
}

Task TaskQueue::pop()
{
  std::unique_lock<std::mutex> lock(m_mutex);
  m_cv.wait(lock, [this] { return !m_queue.empty() || m_done; });
  if (m_done && m_queue.empty()) {
    return Task(-1, "");
  }
  Task task = m_queue.front();
  m_queue.pop();
  return task;
}

void TaskQueue::setDone()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_done = true;
  m_cv.notify_all();
}
