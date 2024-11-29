#pragma once

#include "natscommon.h"
#include "nlohmann/json.hpp"
#include <functional>
#include <string>

namespace ApiGear {
namespace Nats {

	enum class ConnectionStatus
	{
		disconnected,
		connecting,
		connected,
		closed,
		reconnecting,
		draining_subs,
		draining_pubs
	};

	enum class SubscriptionStatus
	{
		unsubscribed,
		subscribing,
		subscribed,
		to_unsubscribe,
		unsubscribing
	};

	typedef std::function<void(bool connectionStatus)> OnConnectionStatusChangedCallBackFunction;
	typedef std::function<void(const std::string& args)> SimpleOnMessageCallback;
	typedef std::function<void(const uint64_t)> SubscriptionClosedCallback;
	struct SimpleMessageCallbackContext
	{
		SimpleOnMessageCallback function;
	};
	typedef std::function<std::string(const std::string& args)> MessageCallbackWithResult;
	struct MessageCallbackWithResultContext
	{
		MessageCallbackWithResult function;
	};
} // namespace Nats
} // namespace ApiGear
