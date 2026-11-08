//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_ABILITY_ABILITY_FACTORY_H_
#define OOP_ABILITY_ABILITY_FACTORY_H_

#include <memory>

#include "ability.h"
#include "ability_type.h"

class AbilityFactory {
public:
	std::shared_ptr<Ability> Create(AbilityType type) const;

	std::shared_ptr<Ability> CreateRandomForEnemy() const;
};

#endif  // OOP_ABILITY_ABILITY_FACTORY_H_
