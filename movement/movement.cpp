//
// Created by Maksim on 29.09.2026.
//

#include "movement.h"

#include <cstdlib>

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
	if (!robot.SetPosition(row, col, game_field_.GetCell(row, col).GetMovementCost())) {
		return false;
	}
	ApplyCellStatuses(robot, row, col);
	return true;
}

void MovementSystem::ApplyCellStatuses(Robot &robot, int row, int col) const {
	const std::vector<StatusType> &statuses = game_field_.GetCell(row, col).GetStatuses();
	if (statuses.empty()) {
		return;
	}
	for (StatusType type: statuses) {
		robot.AddStatus(status_factory_.Create(type));
	}
	game_field_.RemoveCellStatus(row, col, static_cast<std::size_t>(std::rand()) % statuses.size());
}


