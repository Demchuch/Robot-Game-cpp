//
// Created by Maksim on 08.11.2026.
//

#include "area_strike_ability.h"

#include <algorithm>
#include <cstdlib>
#include <stdexcept>

#include "../config/game_constants.h"
#include "../robot/robot.h"
#include "../status/status_factory.h"

AreaStrikeAbility::AreaStrikeAbility(int radius, int damage, int energy_cost) {
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

int AreaStrikeAbility::GetEnergyCost() const {
	return energy_cost_;
}

std::string AreaStrikeAbility::GetName() const {
	return "Area strike";
}

void AreaStrikeAbility::Upgrade() {
	radius_ += kAreaStrikeRadiusUpgrade;
}

bool AreaStrikeAbility::Use(Robot &user, int /*target_row*/, int /*target_col*/,
							GameField & /*field*/, std::vector<Robot> &robots) {
	if (!user.SpendEnergy(energy_cost_)) {
		return false;
	}
	StatusFactory status_factory;
	for (Robot &robot: robots) {
		if (&robot == &user || robot.GetHealth() == 0 || user.IsFriendlyTo(robot)) {
			continue;
		}
		int row_diff = std::abs(robot.GetRow() - user.GetRow());
		int col_diff = std::abs(robot.GetCol() - user.GetCol());
		if (std::max(row_diff, col_diff) > radius_) {
			continue;
		}
		robot.TakeDamage(damage_);
		if (robot.GetHealth() == 0) {
			user.GainExperience(kExperienceForKill);
		} else {
			robot.AddStatus(status_factory.Create(StatusType::kOverload));
		}
	}
	return true;
}

AbilityType AreaStrikeAbility::GetType() const {
	return AbilityType::kAreaStrike;
}

bool AreaStrikeAbility::NeedsTarget() const {
	return false;
}
