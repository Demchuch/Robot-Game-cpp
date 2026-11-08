//
// Created by Maksim on 08.11.2026.
//

#include "burn_status.h"

#include <stdexcept>
#include <typeinfo>

#include "../config/game_constants.h"
#include "../robot/robot.h"

BurnStatus::BurnStatus(int turns) {
	if (turns <= 0) {
		throw std::invalid_argument("incorrect turns value");
	}
	turns_ = turns;
}

std::string BurnStatus::GetName() const {
	return "Burn";
}

void BurnStatus::Stack(const Status &other) {
	turns_ += dynamic_cast<const BurnStatus &>(other).turns_;
}

void BurnStatus::OnTurnEnd(Robot &owner) {
	owner.TakeDamage(kBurnDamage);
	--turns_;
}

bool BurnStatus::IsExpired() const {
	return turns_ <= 0;
}
