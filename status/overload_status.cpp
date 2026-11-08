//
// Created by Maksim on 06.11.2026.
//

#include "overload_status.h"

std::string OverloadStatus::GetName() const {
	return "Overload";
}

void OverloadStatus::Stack(const Status & /*other*/) {
	// several overloads act as one
}

bool OverloadStatus::BlocksAbilities() const {
	return true;
}

void OverloadStatus::OnAbilityAttempt() {
	is_used_ = true;
}

bool OverloadStatus::IsExpired() const {
	return is_used_;
}
