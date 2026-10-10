//
// Created by Maksim on 29.09.2026.
//

#include "movement.h"

MovementSystem::MovementSystem(GameField &game_field) : game_field_(game_field) {}

bool MovementSystem::Action(Robot &robot, Robot *opponent, int row, int col) const {
	if (!game_field_.IsInside(row, col)) {
		return false;
	}
	if (!game_field_.GetCell(row, col).GetWalkable()) {
		return false;
	}
	if (opponent != nullptr) {
		return robot.InteractWith(*opponent);
	}
	return robot.SetPosition(row, col, game_field_.GetCell(row, col).GetMovementCost());
}


