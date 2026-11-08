//
// Created by Maksim on 08.11.2026.
//

#include "ability_factory.h"

#include <cstdlib>
#include <stdexcept>

#include "../config/game_constants.h"
#include "area_strike_ability.h"
#include "heal_ability.h"
#include "ranged_strike_ability.h"
#include "teleport_ability.h"

std::shared_ptr<Ability> AbilityFactory::Create(AbilityType type) const {
	switch (type) {
		case AbilityType::kAreaStrike:
			return std::make_shared<AreaStrikeAbility>(kAreaStrikeRadius, kAreaStrikeDamage, kAreaStrikeCost);
		case AbilityType::kRangedStrike:
			return std::make_shared<RangedStrikeAbility>(kRangedStrikeRadius, kRangedStrikeDamage,
														kRangedStrikeCost);
		case AbilityType::kHeal:
			return std::make_shared<HealAbility>(kHealAmount, kHealCost);
		case AbilityType::kTeleport:
			return std::make_shared<TeleportAbility>(kTeleportRadius, kTeleportCost);
	}
	throw std::invalid_argument("unknown ability type");
}

std::shared_ptr<Ability> AbilityFactory::CreateRandomForEnemy() const {
	if (std::rand() % 2 == 0) {
		return Create(AbilityType::kHeal);
	}
	return Create(AbilityType::kTeleport);
}
