//
// Created by Maksim on 28.09.2026.
//

#include "cell.h"

#include <stdexcept>

#include "../config/game_constants.h"


Cell::Cell(bool is_walkable, int movement_cost) {
	is_walkable_ = is_walkable;
	SetMovementCost(movement_cost);
}

int Cell::GetMovementCost() const {
	return movement_cost_;
}

bool Cell::GetWalkable() const {
	return is_walkable_;
}

bool Cell::GetKnown() const {
	return is_known_;
}


void Cell::SetKnown() {
	is_known_ = true;
}

void Cell::SetWalkable(bool is_walkable) {
	is_walkable_ = is_walkable;
}

bool Cell::GetVisible() const {
	return is_visible_;
}

void Cell::SetVisible(bool is_visible) {
	is_visible_ = is_visible;
}

void Cell::SetMovementCost(int movement_cost) {
	if (movement_cost < kMinMovementCost) {
		throw std::invalid_argument("movement_cost is below the minimum");
	}
	movement_cost_ = movement_cost;
}
