//
// Created by Maksim on 30.09.2026.
//

#include "visualizer.h"


#include <iostream>

#include "../config/game_constants.h"

void Visualizer::Draw(const GameField &field, const std::vector<Robot> &robots,
					const std::vector<RobotFactory> &factories) const {
	std::cout << kClearScreenSequence;
	for (int row = 0; row < field.GetHeight(); ++row) {
		for (int col = 0; col < field.GetWidth(); ++col) {
			if (!field.GetCell(row, col).GetKnown()) {
				std::cout << kUnknownCellSymbol;
				continue;
			}
			if (IsFactoryAt(factories, row, col)) {
				std::cout << kFactorySymbol;
				continue;
			}
			bool is_visible = field.GetCell(row, col).GetVisible();
			const Robot *robot_here = nullptr;
			for (const Robot &robot: robots) {
				if (robot.GetRow() == row && robot.GetCol() == col) {
					if (robot.GetHealth() == 0 || !is_visible) {
						continue;
					}
					robot_here = &robot;
					break;
				}
			}
			if (robot_here != nullptr) {
				std::cout << GetRobotSymbol(robot_here->GetTeam());
			} else {
				const Cell &cell = field.GetCell(row, col);
				if (!cell.GetWalkable()) {
					std::cout << kWallSymbol;
				} else if (cell.GetMovementCost() == kSlowCellThreshold) {
					std::cout << kSlowCellSymbol;
				} else {
					std::cout << kFloorSymbol;
				}
			}
		}
		std::cout << '\n';
	}
	for (const Robot &robot: robots) {
		if (robot.GetHealth() == 0 || !field.GetCell(robot.GetRow(), robot.GetCol()).GetVisible()) {
			continue;
		}
		std::cout << GetRobotSymbol(robot.GetTeam())
				<< " HP: " << robot.GetHealth() << "/" << robot.GetMaxHealth()
				<< " Energy: " << robot.GetEnergy() << "/" << robot.GetMaxEnergy()
				<< " Speed: " << robot.GetRemainingSpeed() << "/" << robot.GetSpeed()
				<< " Rank: " << robot.GetRank()
				<< " EXP: " << robot.GetExperience() << "/" << robot.GetExperienceToNextRank()
				<< std::endl;
	}
}


bool Visualizer::IsFactoryAt(const std::vector<RobotFactory> &factories, int row, int col) const {
	for (const RobotFactory &factory: factories) {
		if (factory.Occupies(row, col)) {
			return true;
		}
	}
	return false;
}

const char *Visualizer::GetRobotSymbol(Team team) const {
	switch (team) {
		case Team::kPlayer:
			return kPlayerSymbol;
		case Team::kAlly:
			return kAllySymbol;
		case Team::kEnemy:
			return kEnemySymbol;
	}
	return kEnemySymbol;
}
