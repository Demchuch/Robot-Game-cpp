//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_STATUS_SHIELD_STATUS_H_
#define OOP_STATUS_SHIELD_STATUS_H_

#include "status_base.h"

class ShieldStatus : public StatusBase {
public:
	explicit ShieldStatus(int capacity);

	std::string GetName() const override;

	void Stack(const Status &other) override;

	int AbsorbDamage(int damage) override;

	bool IsExpired() const override;

private:
	int capacity_;
};

#endif  // OOP_STATUS_SHIELD_STATUS_H_
