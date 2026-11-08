//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_STATUS_BURN_STATUS_H_
#define OOP_STATUS_BURN_STATUS_H_

#include "status_base.h"

class BurnStatus : public StatusBase {
public:
	explicit BurnStatus(int turns);

	std::string GetName() const override;

	void Stack(const Status &other) override;

	void OnTurnEnd(Robot &owner) override;

	bool IsExpired() const override;

private:
	int turns_;
};

#endif  // OOP_STATUS_BURN_STATUS_H_
