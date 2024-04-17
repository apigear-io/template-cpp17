#include "threadpool.h"

namespace ApiGear { namespace Utilities {

ThreadPool::ThreadPool(size_t numWorkerThreads)
    : stop(false)
{
    initializeWorkers(numWorkerThreads);
}

ThreadPool::~ThreadPool() {
    stop = true;

    workAvailableCondition.notify_all();

    for (std::thread &worker : workers)
    {
        worker.join();
    }
}

void ThreadPool::initializeWorkers(size_t numWorkerThreads) {
    for (size_t i = 0; i < numWorkerThreads; ++i) {
        workers.emplace_back([this] {
                workerRun();
        });
    }
}

void ThreadPool::workerRun(){
    for (;;) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(this->queueMutex);

            this->workAvailableCondition.wait(lock, [this] {
                return this->stop || !this->tasks.empty();
            });

            if (this->stop && this->tasks.empty())
            {
                return;
            }

            task = std::move(this->tasks.front());
            this->tasks.pop();
        }

        task();
    }
}

}} // namespace ApiGear::Utilities
