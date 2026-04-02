/**
Tracer
Copyright (C) 2020 ApiGear UG
*/
#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
  #define APIGEAR_TRACER_EXPORT __attribute__ ((dllexport))
#else
  #define APIGEAR_TRACER_EXPORT __declspec(dllexport)
#endif
#else
  #if __GNUC__ >= 4
    #define APIGEAR_TRACER_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define APIGEAR_TRACER_EXPORT
  #endif
#endif

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#endif
#include <nlohmann/json.hpp>
#include <atomic>
#include <memory>
#include <string>
#include <map>
#include <queue>
#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Util/Timer.h>
#include <Poco/Util/TimerTask.h>
#include <Poco/Mutex.h>

namespace ApiGear {
namespace PocoImpl {
class APIGEAR_TRACER_EXPORT Tracer
{
public:
    explicit Tracer();
    Tracer(Tracer const&) = delete;
    void operator=(Tracer const&) = delete;

    void connect(const std::string& baseUrl, const std::string& identifier);

    void call(const std::string &symbol, const nlohmann::json &fields);
    void signal(const std::string &symbol, const nlohmann::json &fields);
    void state(const std::string &symbol, const nlohmann::json &fields);

private:
    void connect();
    void doProcess(Poco::Util::TimerTask& task);
    void trace(const std::string &eventKind, const std::string &symbol, const nlohmann::json &fields);
    void process();

private:
    std::deque<nlohmann::json> m_queue;
    Poco::Mutex m_queueMutex;
    Poco::URI m_traceUrl;
    Poco::Mutex m_sessionMutex;
    std::unique_ptr<Poco::Net::HTTPClientSession> m_session;
    std::atomic<bool> m_busy{false};
    Poco::Mutex m_taskMutex;
    Poco::Util::Timer m_retryTimer;
    Poco::Util::TimerTask::Ptr m_task;
};

} // namespace PocoImpl
} // namespace ApiGear
