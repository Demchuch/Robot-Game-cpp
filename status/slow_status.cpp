//
// Created by Maksim on 08.11.2026.
//

#include "slow_status.h"

#include <stdexcept>
#include <typeinfo>

SlowStatus::SlowStatus(int turns) {
	if (turns <= 0) {
		throw std::invalid_argument("incorrect turns value");
	}
	turns_ = turns;
}

std::string SlowStatus::GetName() const {
	return "Slow";
}

void SlowStatus::Stack(const Status &other) {
	turns_ += dynamic_cast<const SlowStatus &>(other).turns_;
}

bool SlowStatus::BlocksMovement() const {
	return true;
}

void SlowStatus::OnTurnEnd(Robot & /*owner*/) {
	--turns_;
}

bool SlowStatus::IsExpired() const {
	return turns_ <= 0;
}
