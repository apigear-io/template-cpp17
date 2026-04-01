#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <atomic>
#include <chrono>
#include <stdexcept>
#include <thread>

#include "../threadpool.h"

SCENARIO("ThreadPool basic task execution", "[threadpool]")
{
    GIVEN("A thread pool with 2 workers") {
        ApiGear::Utilities::ThreadPool pool(2);

        THEN("A simple task should execute successfully") {
            std::atomic<bool> taskRan{false};
            pool.enqueue([&taskRan]() {
                taskRan.store(true);
            });

            // Give the task time to execute
            for (int i = 0; i < 100 && !taskRan.load(); ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            REQUIRE(taskRan.load());
        }
    }
}

SCENARIO("ThreadPool survives throwing tasks", "[threadpool]")
{
    GIVEN("A thread pool with 2 workers") {
        ApiGear::Utilities::ThreadPool pool(2);

        WHEN("A task throws a std::exception") {
            pool.enqueue([]() {
                throw std::runtime_error("test exception");
            });

            // Give the throwing task time to execute
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            THEN("The pool continues to execute subsequent tasks") {
                std::atomic<bool> taskRan{false};
                pool.enqueue([&taskRan]() {
                    taskRan.store(true);
                });

                for (int i = 0; i < 100 && !taskRan.load(); ++i) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                REQUIRE(taskRan.load());
            }
        }

        WHEN("A task throws an unknown exception (int)") {
            pool.enqueue([]() {
                throw 42;
            });

            // Give the throwing task time to execute
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            THEN("The pool continues to execute subsequent tasks") {
                std::atomic<bool> taskRan{false};
                pool.enqueue([&taskRan]() {
                    taskRan.store(true);
                });

                for (int i = 0; i < 100 && !taskRan.load(); ++i) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                REQUIRE(taskRan.load());
            }
        }

        WHEN("Multiple tasks throw exceptions") {
            constexpr int numThrowingTasks = 10;
            for (int i = 0; i < numThrowingTasks; ++i) {
                pool.enqueue([i]() {
                    throw std::runtime_error("exception " + std::to_string(i));
                });
            }

            // Give the throwing tasks time to execute
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            THEN("The pool still processes normal tasks afterwards") {
                std::atomic<int> completedCount{0};
                constexpr int numNormalTasks = 5;
                for (int i = 0; i < numNormalTasks; ++i) {
                    pool.enqueue([&completedCount]() {
                        completedCount.fetch_add(1);
                    });
                }

                for (int i = 0; i < 200 && completedCount.load() < numNormalTasks; ++i) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                REQUIRE(completedCount.load() == numNormalTasks);
            }
        }
    }
}
