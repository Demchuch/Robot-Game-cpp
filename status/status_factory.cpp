//
// Created by Maksim on 08.11.2026.
//

#include "status_factory.h"

#include <stdexcept>

#include "../config/game_constants.h"
#include "burn_status.h"
#include "overload_status.h"
#include "shield_status.h"
#include "slow_status.h"

std::shared_ptr<Status> StatusFactory::Create(StatusType type) const {
	switch (type) {
		case StatusType::kSlow:
			return std::make_shared<SlowStatus>(kSlowDuration);
		case StatusType::kOverload:
			return std::make_shared<OverloadStatus>();
		case StatusType::kBurn:
			return std::make_shared<BurnStatus>(kBurnDuration);
		case StatusType::kShield:
			return std::make_shared<ShieldStatus>(kShieldCapacity);
	}
	throw std::invalid_argument("unknown status type");
}
