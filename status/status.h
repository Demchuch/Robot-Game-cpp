//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_STATUS_STATUS_H_
#define OOP_STATUS_STATUS_H_

#include <string>

class Robot;

class Status {
public:
	virtual ~Status() = default;

	virtual std::string GetName() const = 0;

	virtual void Stack(const Status &other) = 0;

	virtual bool BlocksMovement() const = 0;

	virtual bool BlocksAbilities() const = 0;

	virtual void OnAbilityAttempt() = 0;

	virtual int AbsorbDamage(int damage) = 0;

	virtual void OnTurnEnd(Robot &owner) = 0;

	virtual bool IsExpired() const = 0;
};

#endif  // OOP_STATUS_STATUS_H_
