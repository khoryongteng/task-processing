#include <iostream>

#include "task_queue.h"
#include "producer_manager.h"
#include "consumer_manager.h"

int main(void)
{
    TaskQueue taskQueue {};
    ProducerManager producerManager(taskQueue, 2);
    ConsumerManager consumerManager(taskQueue, 3);

    producerManager.startProducers();
    consumerManager.startConsumers();

    producerManager.stopProducers(); // Stop Producers join the thread, if joined, means no more new tasks
    taskQueue.setDone(); // Therefore, setDone can be called

    consumerManager.stopConsumers();

    std::cout << "Task processing complete!" << std::endl;

    return 0;
}