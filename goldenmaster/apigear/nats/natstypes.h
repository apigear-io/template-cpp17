#pragma once

#include "natscommon.h"
#include "nlohmann/json.hpp"
#include <functional>

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

	typedef std::function<void(bool connectionStatus)> OnConnectionStatusChangedCallBackFunction;
} // namespace Nats
} // namespace ApiGear
