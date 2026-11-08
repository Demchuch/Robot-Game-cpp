//
// Created by Maksim on 08.11.2026.
//

#include "heal_ability.h"
#include "../robot/robot.h"
#include "../status/shield_status.h"
#include <stdexcept>
#include "../config/game_constants.h"

HealAbility::HealAbility(int heal_amount, int energy_cost) {
	if (heal_amount <= 0) {
		throw std::invalid_argument("incorrect heal_amount value");
	}
	if (energy_cost <= 0) {
		throw std::invalid_argument("incorrect energy_cost value");
	}
	heal_amount_ = heal_amount;
	energy_cost_ = energy_cost;
}
int HealAbility::GetEnergyCost() const {
	return energy_cost_;

}

std::string HealAbility::GetName() const {
	return "Heal";

}

void HealAbility::Upgrade() {
	heal_amount_ += kHealUpgrade;
}

bool HealAbility::Use(Robot &user, int /*target_row*/, int /*target_col*/,
					  GameField & /*field*/, std::vector<Robot> & /*robots*/) {
	if (user.SpendEnergy(energy_cost_)) {
		int overheal = user.GetHealth() + heal_amount_ - user.GetMaxHealth();
		user.Heal(heal_amount_);
		if (overheal > 0) {
			user.AddStatus(std::make_shared<ShieldStatus>(overheal));
		}
		return true;
	}
	else {
		return false;
	}
}

AbilityType HealAbility::GetType() const {
	return AbilityType::kHeal;
}

bool HealAbility::NeedsTarget() const {
	return false;
}
