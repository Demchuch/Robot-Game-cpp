//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_STATUS_SLOW_STATUS_H_
#define OOP_STATUS_SLOW_STATUS_H_

#include "status_base.h"

class SlowStatus : public StatusBase {
public:
	explicit SlowStatus(int turns);

	std::string GetName() const override;

	void Stack(const Status &other) override;

	bool BlocksMovement() const override;

	void OnTurnEnd(Robot &owner) override;

	bool IsExpired() const override;

private:
	int turns_;
};

#endif  // OOP_STATUS_SLOW_STATUS_H_
