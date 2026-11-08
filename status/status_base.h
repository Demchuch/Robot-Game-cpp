//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_STATUS_STATUS_BASE_H_
#define OOP_STATUS_STATUS_BASE_H_

#include "status.h"

// Default "do nothing" behaviour, so concrete statuses override only what they need.
class StatusBase : public Status {
public:
	bool BlocksMovement() const override;

	bool BlocksAbilities() const override;

	void OnAbilityAttempt() override;

	int AbsorbDamage(int damage) override;

	void OnTurnEnd(Robot &owner) override;
};

#endif  // OOP_STATUS_STATUS_BASE_H_
