#pragma once

#include <string>

struct Task
{
    int taskId;
    std::string taskData;
    Task(int id, std::string data) : taskId(id), taskData(data) {}
};