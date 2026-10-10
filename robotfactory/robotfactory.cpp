//
// Created by Maksim on 04.10.2026.
//

#include "robotfactory.h"


#include <stdexcept>

#include "../config/game_constants.h"


RobotFactory::RobotFactory(int row, int col, int turns_between_spawns) {
	if (row < 0 || col < 0) {
		throw std::invalid_argument("factory position must not be negative");
	}
	if (turns_between_spawns <= 0) {
		throw std::invalid_argument("turns_between_spawns must be positive");
	}
	row_ = row;
	col_ = col;
	turns_between_spawns_ = turns_between_spawns;
}


int RobotFactory::GetRow() const {
	return row_;
}


void RobotFactory::EndTurn() {
	if (turns_since_spawn_ < turns_between_spawns_) {
		turns_since_spawn_++;
	}
}


Robot RobotFactory::CreateEnemy(int row, int col) {
	if (IsReadyToSpawn()) {
		turns_since_spawn_ = 0;
		return Robot(kSpawnedMaxHealth, kSpawnedAttackPower, kSpawnedMaxEnergy, kSpawnedExperienceToNextRank,
					Team::kEnemy, row, col, kSpawnedSpeed, kVisionRadius);
	}
	throw std::logic_error("cant create robot");
}

bool RobotFactory::Occupies(int row, int col) const {
	return row >= row_ && row < row_ + kFactorySize && col >= col_ &&
			col < col_ + kFactorySize;
}


std::vector<std::pair<int, int> > RobotFactory::GetAdjacentCells() const {
	std::vector<std::pair<int, int> > cells;
	for (int row = row_ - 1; row < row_ + kFactorySize + 1; row++) {
		for (int col = col_ - 1; col < col_ + kFactorySize + 1; col++) {
			if (Occupies(row, col)) {
				continue;
			}
			cells.push_back({row, col});
		}
	}
	return cells;
}

void RobotFactory::PlaceOn(GameField &field) const {
	field.SetWalkableArea(row_, col_, kFactorySize, kFactorySize, false);
}


bool RobotFactory::IsReadyToSpawn() const {
	return turns_since_spawn_ >= turns_between_spawns_;
}

int RobotFactory::GetCol() const {
	return col_;
}
