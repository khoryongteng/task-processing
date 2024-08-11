#include "task.h"

int Task::getId() const 
{ 
  return m_id; 
}
const std::string& Task::getData() const 
{ 
  return m_data; 
}