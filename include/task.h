#pragma once

#include <string>

class Task {
public:
    Task(const int id, const std::string& data) : m_id(id), m_data(data) {}

    int getId() const;
    const std::string& getData() const;

private:
    int m_id;
    std::string m_data;
};