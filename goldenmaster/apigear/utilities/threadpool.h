/*
* MIT License
*
* Copyright (c) 2024 Epic Games Inc.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define APIGEAR_THREADPOOL __attribute__ ((dllexport))
#else
#define APIGEAR_THREADPOOL __declspec(dllexport)
#endif
#else
#if __GNUC__ >= 4
#define APIGEAR_THREADPOOL __attribute__ ((visibility ("default")))
#else
#define APIGEAR_THREADPOOL
#endif
#endif

namespace ApiGear {
namespace Utilities {
/**
 * @brief The ThreadPool class provides a pool of threads for executing tasks concurrently.
 *
 * The `ThreadPool` class allows you to create a pool of worker threads that can execute tasks concurrently.
 * You can enqueue tasks to the thread pool, and they will be executed by the available worker threads.
 * The number of worker threads in the pool is specified during construction.
 */
class APIGEAR_THREADPOOL ThreadPool {
public:
    /**
     * @brief Constructs a ThreadPool object with the specified number of threads.
     *
     * @param numThreads The number of threads to create in the thread pool.
     */
    ThreadPool(size_t numThreads);

    ~ThreadPool();

    /**
     * @brief Enqueues a task to be executed by the thread pool.
     * 
     * This function adds a task to the thread pool's queue, which will be executed by one of the worker threads.
     * The task can be any callable object, such as a function, lambda expression, or functor.
     * 
     * @tparam F The type of the callable object.
     * @param f The callable object to be enqueued.
     */
    template<class F>
    void enqueue(F&& f) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(std::forward<F>(f));
        }
        workAvailableCondition.notify_one();
    }

private:
    void initializeWorkers(size_t numThreads);
    void workerRun();

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable workAvailableCondition;
    std::atomic<bool> stop;
};
} // namespace Utilities
} // namespace ApiGear
