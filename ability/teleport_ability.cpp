//
// Created by Maksim on 08.11.2026.
//

#include "teleport_ability.h"

#include <algorithm>
#include <cstdlib>
#include <stdexcept>

#include "../config/game_constants.h"
#include "../gamefield/gamefield.h"
#include "../robot/robot.h"

TeleportAbility::TeleportAbility(int radius, int energy_cost) {
	if (radius <= 0) {
		throw std::invalid_argument("incorrect radius value");
	}
	if (energy_cost < kTeleportMinCost) {
		throw std::invalid_argument("incorrect energy_cost value");
	}
	radius_ = radius;
	energy_cost_ = energy_cost;
}

int TeleportAbility::GetEnergyCost() const {
	return energy_cost_;
}

std::string TeleportAbility::GetName() const {
	return "Teleport";
}

void TeleportAbility::Upgrade() {
	energy_cost_ = std::max(kTeleportMinCost, energy_cost_ - kTeleportCostUpgrade);
}

bool TeleportAbility::Use(Robot &user, int target_row, int target_col,
						GameField &field, std::vector<Robot> &robots) {
	int row_diff = std::abs(target_row - user.GetRow());
	int col_diff = std::abs(target_col - user.GetCol());
	if (std::max(row_diff, col_diff) > radius_) {
		return false;
	}
	if (!field.IsInside(target_row, target_col) || !field.GetCell(target_row, target_col).GetWalkable()) {
		return false;
	}
	for (const Robot &robot: robots) {
		if (robot.GetHealth() > 0 && robot.GetRow() == target_row && robot.GetCol() == target_col) {
			return false;
		}
	}
	if (!user.SpendEnergy(energy_cost_)) {	
		return false;
	}
	user.TeleportTo(target_row, target_col);
	return true;
}

AbilityType TeleportAbility::GetType() const {
	return AbilityType::kTeleport;
}

bool TeleportAbility::NeedsTarget() const {
	return true;
}
