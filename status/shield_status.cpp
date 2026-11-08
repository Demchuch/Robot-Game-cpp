//
// Created by Maksim on 08.11.2026.
//

#include "shield_status.h"

#include <stdexcept>
#include <typeinfo>

ShieldStatus::ShieldStatus(int capacity) {
	if (capacity <= 0) {
		throw std::invalid_argument("incorrect capacity value");
	}
	capacity_ = capacity;
}

std::string ShieldStatus::GetName() const {
	return "Shield";
}

void ShieldStatus::Stack(const Status &other) {
	capacity_ += dynamic_cast<const ShieldStatus &>(other).capacity_;
}

int ShieldStatus::AbsorbDamage(int damage) {
	if (damage <= capacity_) {
		capacity_ -= damage;
		return 0;
	}
	int rest = damage - capacity_;
	capacity_ = 0;
	return rest;
}

bool ShieldStatus::IsExpired() const {
	return capacity_ <= 0;
}
