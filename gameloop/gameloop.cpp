//
// Created by Maksim on 30.09.2026.
//

#include "gameloop.h"

#include "../config/game_constants.h"

GameLoop::GameLoop(GameField &game_field, std::vector<Robot> &robots, std::vector<RobotFactory> &factories)
	: game_field_(game_field),
	factories_(factories),
	robots_(robots),
	movement_system_(game_field_),
	enemy_controller_(robots_, movement_system_){
	for (const RobotFactory &factory: factories_) {
		factory.PlaceOn(game_field_);
	}
}


Robot &GameLoop::FindPlayerRobot() const {
	for (Robot &robot: robots_) {
		if (robot.GetTeam() == Team::kPlayer) {
			return robot;
		}
	}
	throw std::runtime_error("no player robot");
}




bool GameLoop::TryMoveRobot(Robot &robot, int target_row, int target_col) const {
	Robot *opponent = enemy_controller_.FindRobotAt(target_row, target_col);
	return movement_system_.Action(robot, opponent, target_row, target_col);
}

bool GameLoop::IsPlayerDefeated() const {
	return FindPlayerRobot().GetHealth() == 0;
}

void GameLoop::RegenerateEnergy() {
	for (Robot &robot: robots_) {
		robot.RegenerateEnergy(kRegenerateEnergy);
	}
}

void GameLoop::ResetSpeed() {
	for (Robot &robot: robots_) {
		robot.ResetSpeed();
	}
}


void GameLoop::Run() {
	while (!AllEnemiesDefeated() && !IsPlayerDefeated()) {
		PlayTurn();
	}
	Visualizer visualizer;
	visualizer.Draw(game_field_, robots_, factories_);
	if (IsPlayerDefeated()) {
		std::cout << "defeat" << std::endl;
	} else {
		std::cout << "victory" << std::endl;
	}
}


bool GameLoop::HandlePlayerInput() const {
	Robot &player = FindPlayerRobot();
	std::string input;
	std::cin >> input;
	if (input == kKeyEndTurn) {
		return true;
	}
	int row_offset = 0;
	int col_offset = 0;
	if (input == kKeyMoveUp) {
		row_offset = -1;
	} else if (input == kKeyMoveLeft) {
		col_offset = -1;
	} else if (input == kKeyMoveDown) {
		row_offset = 1;
	} else if (input == kKeyMoveRight) {
		col_offset = 1;
	} else {
		return false;
	}

	TryMoveRobot(player, player.GetRow() + row_offset,
				player.GetCol() + col_offset);
	return false;
}

bool GameLoop::AllEnemiesDefeated() const {
	for (const Robot &robot: robots_) {
		if (robot.GetTeam() == Team::kEnemy && robot.GetHealth() > 0) {
			return false;
		}
	}
	return true;
}

void GameLoop::PlayTurn() {
	ResetSpeed();
	RegenerateEnergy();
	RevealAroundPlayer();
	Visualizer visualizer;
	visualizer.Draw(game_field_, robots_, factories_);
	while (!HandlePlayerInput()) {
		RevealAroundPlayer();
		visualizer.Draw(game_field_, robots_, factories_);
	}
	enemy_controller_.AiTurn();
	SpawnEnemies();
}

void GameLoop::RevealAroundPlayer() {
	game_field_.ClearVisibility();
	Robot &player = FindPlayerRobot();
	int radius = player.GetVisionRadius();
	int row = player.GetRow();
	int col = player.GetCol();

	for (int dr = -radius; dr <= radius; ++dr) {
		for (int dc = -radius; dc <= radius; ++dc) {
			if ((dr * dr + dc * dc) <= radius * radius) {
				if (game_field_.IsInside(row + dr, col + dc)) {
					game_field_.RevealCell(row + dr, col + dc);
				}
			}
		}
	}
}

bool GameLoop::IsCellFree(int row, int col) const {
	return (game_field_.IsInside(row, col) && game_field_.GetCell(row, col).GetWalkable() && enemy_controller_.FindRobotAt(row, col) ==
			nullptr);
}




void GameLoop::SpawnEnemies() {
	for (RobotFactory &factory: factories_) {
		factory.EndTurn();
		if (!factory.IsReadyToSpawn()) {
			continue;
		}
		for (const std::pair<int, int> &cell: factory.GetAdjacentCells()) {
			if (IsCellFree(cell.first, cell.second)) {
				robots_.push_back(factory.CreateEnemy(cell.first, cell.second));
				break;
			}
		}
	}
}


