//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_ABILITY_TELEPORT_ABILITY_H_
#define OOP_ABILITY_TELEPORT_ABILITY_H_

#include "ability.h"


class TeleportAbility : public Ability {
public:
	TeleportAbility(int radius, int energy_cost);

	bool Use(Robot &user, int target_row, int target_col,
			GameField &field, std::vector<Robot> &robots) override;

	int GetEnergyCost() const override;

	std::string GetName() const override;

	void Upgrade() override;

	AbilityType GetType() const override;

	bool NeedsTarget() const override;

private:
	int radius_;
	int energy_cost_;
};


#endif  // OOP_ABILITY_TELEPORT_ABILITY_H_
