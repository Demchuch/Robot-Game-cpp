//
// Created by Maksim on 30.09.2026.
//

#include "visualizer.h"


#include <iomanip>
#include <iostream>

#include "../config/game_constants.h"

void Visualizer::Draw(const GameField &field, const std::vector<Robot> &robots,
					const std::vector<RobotFactory> &factories, DisplayMode mode) const {
	std::cout << kClearScreenSequence;
	for (int row = 0; row < field.GetHeight(); ++row) {
		for (int col = 0; col < field.GetWidth(); ++col) {
			std::cout << GetCellSymbol(field, robots, factories, row, col, mode);
		}
		std::cout << '\n';
	}
	DrawHud(field, robots, mode);
}

std::string Visualizer::GetCellSymbol(const GameField &field, const std::vector<Robot> &robots,
									const std::vector<RobotFactory> &factories, int row, int col,
									DisplayMode mode) const {
	const Cell &cell = field.GetCell(row, col);
	if (!cell.GetKnown()) {
		return kUnknownCellSymbol;
	}
	if (IsFactoryAt(factories, row, col)) {
		return kFactorySymbol;
	}
	const Robot *robot = cell.GetVisible() ? FindVisibleRobotAt(robots, row, col) : nullptr;
	if (robot != nullptr) {
		if (mode == DisplayMode::kEnemies && robot->GetTeam() == Team::kEnemy) {
			return kEnemyHighlightSymbol;
		}
		return GetRobotSymbol(robot->GetTeam());
	}
	if (!cell.GetWalkable()) {
		return mode == DisplayMode::kImpassable ? kWallHighlightSymbol : kWallSymbol;
	}
	if (mode == DisplayMode::kStatusCells && !cell.GetStatuses().empty()) {
		return kStatusCellSymbol;
	}
	if (cell.GetMovementCost() == kSlowCellThreshold) {
		return kSlowCellSymbol;
	}
	return kFloorSymbol;
}

const Robot *Visualizer::FindVisibleRobotAt(const std::vector<Robot> &robots, int row, int col) const {
	for (const Robot &robot: robots) {
		if (robot.GetHealth() > 0 && robot.GetRow() == row && robot.GetCol() == col) {
			return &robot;
		}
	}
	return nullptr;
}

std::string Visualizer::GetModeDescription(DisplayMode mode) const {
	switch (mode) {
		case DisplayMode::kStandard:
			return "standard";
		case DisplayMode::kEnemies:
			return "enemies highlighted (red background)";
		case DisplayMode::kImpassable:
			return "impassable cells highlighted (white background)";
		case DisplayMode::kStatusCells:
			return "cells with statuses highlighted (magenta background)";
	}
	return "standard";
}

void Visualizer::DrawHud(const GameField &field, const std::vector<Robot> &robots, DisplayMode mode) const {
	const Robot *player = nullptr;
	for (const Robot &robot: robots) {
		if (robot.GetTeam() == Team::kPlayer) {
			player = &robot;
		}
	}
	if (player != nullptr) {
		DrawPlayer(*player);
		std::cout << std::endl;
		std::cout << std::left << std::setw(4) << "WHO" << std::setw(7) << "OFFSET" << "  " << std::setw(7) << "HP"
				<< "  " << std::setw(7) << "EN" << "  " << std::setw(kAbilityColumnWidth) << "ABILITY" << "  "
				<< "STATUS" << std::right << std::endl;
		for (const Robot &robot: robots) {
			bool is_visible = field.GetCell(robot.GetRow(), robot.GetCol()).GetVisible();
			if (robot.GetTeam() != Team::kPlayer && robot.GetHealth() > 0 && is_visible) {
				DrawRobotRow(robot, *player);
			}
		}
	}
	std::cout << std::endl << "Display mode: " << GetModeDescription(mode) << std::endl;
	std::cout << kControlsHelp << std::endl;
}

void Visualizer::DrawPlayer(const Robot &player) const {
	std::cout << kPlayerSymbol << " HP " << player.GetHealth() << "/" << player.GetMaxHealth()
			<< "  EN " << player.GetEnergy() << "/" << player.GetMaxEnergy()
			<< "  SPD " << player.GetRemainingSpeed() << "/" << player.GetSpeed()
			<< "  RANK " << player.GetRank()
			<< " (XP " << player.GetExperience() << "/" << player.GetExperienceToNextRank() << ")" << std::endl;
	std::cout << "  Status: " << GetStatusNames(player) << std::endl;
	std::cout << "  Abilities:";
	int number = 1;
	for (const std::shared_ptr<Ability> &ability: player.GetAbilities()) {
		std::cout << " [" << number << "] " << ability->GetName() << " (" << ability->GetEnergyCost() << ")";
		++number;
	}
	std::cout << std::endl;
}


void Visualizer::DrawRobotRow(const Robot &robot, const Robot &player) const {
	std::cout << GetRobotSymbol(robot.GetTeam()) << "   ";
	std::cout << std::showpos << std::setw(3) << robot.GetRow() - player.GetRow() << " "
			<< std::setw(3) << robot.GetCol() - player.GetCol() << std::noshowpos << "  ";
	std::cout << std::setw(3) << robot.GetHealth() << "/" << std::setw(3) << robot.GetMaxHealth()
			<< "  " << std::setw(3) << robot.GetEnergy() << "/" << std::setw(3) << robot.GetMaxEnergy() << "  "
			<< std::left << std::setw(kAbilityColumnWidth) << GetAbilityNames(robot) << std::right << "  "
			<< GetStatusNames(robot) << std::endl;
}

std::string Visualizer::GetStatusNames(const Robot &robot) const {
	std::string names;
	for (const std::shared_ptr<Status> &status: robot.GetStatuses()) {
		names += status->GetName() + " ";
	}
	return names.empty() ? "-" : names;
}

std::string Visualizer::GetAbilityNames(const Robot &robot) const {
	std::string names;
	for (const std::shared_ptr<Ability> &ability: robot.GetAbilities()) {
		names += ability->GetName() + " ";
	}
	return names.empty() ? "-" : names;
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
