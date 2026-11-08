//
// Created by Maksim on 08.11.2026.
//

#include "status_base.h"

bool StatusBase::BlocksMovement() const {
	return false;
}

bool StatusBase::BlocksAbilities() const {
	return false;
}

void StatusBase::OnAbilityAttempt() {
}

int StatusBase::AbsorbDamage(int damage) {
	return damage;
}

void StatusBase::OnTurnEnd(Robot & /*owner*/) {
}
