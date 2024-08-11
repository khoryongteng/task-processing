#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include "task.h"

std::queue<Task> taskQueue;
std::mutex mtx;
std::condition_variable cv;
bool done = false;

void taskProducer(int id)
{
    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Task task(i, "Data from Producer " + std::to_string(id));
        {
            // Lock required here to protect the queue
            std::lock_guard<std::mutex> lock(mtx);
            taskQueue.push(task);
        }
        cv.notify_one();
    }
}

void taskConsumer(int id)
{
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !taskQueue.empty() || done; }); // Wait until there is a task in the queue

        if (done && taskQueue.empty()) {
            break;
        }

        if (!taskQueue.empty()) {
            Task task = taskQueue.front();
            taskQueue.pop();
            lock.unlock();

            std::cout << "Consumer " << id << " processing Task " << task.taskId << " with data: " << task.taskData << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

int main(void)
{
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < 2; ++i)
    {
        producers.push_back(std::thread(taskProducer, i));
    }

    for (int i = 0; i < 3; ++i)
    {
        consumers.push_back(std::thread(taskConsumer, i));
    }

    for (auto& producer : producers)
    {
        producer.join();
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();

    for (auto& consumer : consumers)
    {
        consumer.join();
    }

    std::cout << "Task processing complete!" << std::endl;

    return 0;
}