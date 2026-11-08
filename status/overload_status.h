//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_STATUS_OVERLOAD_STATUS_H_
#define OOP_STATUS_OVERLOAD_STATUS_H_

#include "status_base.h"

class OverloadStatus : public StatusBase {
public:
	std::string GetName() const override;

	void Stack(const Status &other) override;

	bool BlocksAbilities() const override;

	void OnAbilityAttempt() override;

	bool IsExpired() const override;

private:
	bool is_used_ = false;
};

#endif  // OOP_STATUS_OVERLOAD_STATUS_H_
