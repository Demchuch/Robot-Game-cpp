//
// Created by Maksim on 08.11.2026.
//

#include "ranged_strike_ability.h"

#include <algorithm>
#include <cstdlib>
#include <stdexcept>

#include "../config/game_constants.h"
#include "../robot/robot.h"
#include "../status/status_factory.h"

RangedStrikeAbility::RangedStrikeAbility(int radius, int damage, int energy_cost) {
	if (radius <= 0) {
		throw std::invalid_argument("incorrect radius value");
	}
	if (damage <= 0) {
		throw std::invalid_argument("incorrect damage value");
	}
	if (energy_cost <= 0) {
		throw std::invalid_argument("incorrect energy_cost value");
	}
	radius_ = radius;
	damage_ = damage;
	energy_cost_ = energy_cost;
}

int RangedStrikeAbility::GetEnergyCost() const {
	return energy_cost_;
}

std::string RangedStrikeAbility::GetName() const {
	return "Ranged strike";
}

void RangedStrikeAbility::Upgrade() {
	damage_ += kRangedStrikeDamageUpgrade;
}

bool RangedStrikeAbility::Use(Robot &user, int target_row, int target_col,
							GameField & /*field*/, std::vector<Robot> &robots) {
	int row_diff = std::abs(target_row - user.GetRow());
	int col_diff = std::abs(target_col - user.GetCol());
	if (std::max(row_diff, col_diff) > radius_) {
		return false;
	}
	for (Robot &robot: robots) {
		if (robot.GetHealth() == 0 || robot.GetRow() != target_row || robot.GetCol() != target_col) {
			continue;
		}
		if (&robot == &user || user.IsFriendlyTo(robot)) {
			return false;
		}
		if (!user.SpendEnergy(energy_cost_)) {
			return false;
		}
		robot.TakeDamage(damage_);
		if (robot.GetHealth() == 0) {
			user.GainExperience(kExperienceForKill);
		} else {
			StatusFactory status_factory;
			robot.AddStatus(status_factory.Create(StatusType::kBurn));
		}
		return true;
	}
	return false;
}

AbilityType RangedStrikeAbility::GetType() const {
	return AbilityType::kRangedStrike;
}

bool RangedStrikeAbility::NeedsTarget() const {
	return true;
}
