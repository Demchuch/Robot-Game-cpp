#ifndef OOP_ABILITY_ABILITY_H_
#define OOP_ABILITY_ABILITY_H_

#include <string>
#include <vector>

#include "ability_type.h"

class Robot;
class GameField;

class Ability {
public:
	virtual ~Ability() = default;

	virtual bool Use(Robot &user, int target_row, int target_col,
					GameField &field, std::vector<Robot> &robots) = 0;

	virtual int GetEnergyCost() const = 0;

	virtual std::string GetName() const = 0;

	virtual void Upgrade() = 0;

	virtual AbilityType GetType() const = 0;

	virtual bool NeedsTarget() const = 0;
};

#endif  // OOP_ABILITY_ABILITY_H_