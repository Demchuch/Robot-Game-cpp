//
// Created by Maksim on 30.09.2026.
//

#include "gameloop.h"

#include <cstddef>
#include <limits>

#include "../config/game_constants.h"

GameLoop::GameLoop(GameField &game_field, std::vector<Robot> &robots, std::vector<RobotFactory> &factories)
	: game_field_(game_field),
	factories_(factories),
	robots_(robots),
	movement_system_(game_field_),
	enemy_controller_(robots_, movement_system_, game_field_) {
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
	ChooseStartingAbility();
	while (!AllEnemiesDefeated() && !IsPlayerDefeated()) {
		PlayTurn();
	}
	Visualizer visualizer;
	visualizer.Draw(game_field_, robots_, factories_, display_mode_);
	if (IsPlayerDefeated()) {
		std::cout << "defeat" << std::endl;
	} else {
		std::cout << "victory" << std::endl;
	}
}


bool GameLoop::HandlePlayerInput() {
	Robot &player = FindPlayerRobot();
	std::string input;
	std::cin >> input;
	if (input == kKeyEndTurn) {
		return true;
	}
	if (input == kKeyChangeDisplayMode) {
		display_mode_ = static_cast<DisplayMode>((static_cast<int>(display_mode_) + 1) % kDisplayModeCount);
		return false;
	}
	if (IsMenuKey(input, player.GetAbilities().size())) {
		UsePlayerAbility(player, static_cast<std::size_t>(input[0] - kFirstAbilityKey));
		return false;
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
	visualizer.Draw(game_field_, robots_, factories_, display_mode_);
	while (!HandlePlayerInput()) {
		HandleRankUps();
		RevealAroundPlayer();
		visualizer.Draw(game_field_, robots_, factories_, display_mode_);
	}
	enemy_controller_.AiTurn();
	SpawnEnemies();
	EndTurnAll();
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

void GameLoop::ChooseStartingAbility() {
	std::cout << "Choose your starting ability:" << std::endl;
	for (int i = 0; i < kAbilityTypeCount; ++i) {
		std::shared_ptr<Ability> ability = ability_factory_.Create(static_cast<AbilityType>(i));
		std::cout << (i + 1) << ") " << ability->GetName() << " (energy " << ability->GetEnergyCost() << ")"
				<< std::endl;
	}
	std::size_t choice = ReadMenuChoice(kAbilityTypeCount);
	FindPlayerRobot().AddAbility(ability_factory_.Create(static_cast<AbilityType>(choice)));
}

bool GameLoop::IsMenuKey(const std::string &input, std::size_t option_count) const {
	return input.size() == 1 && input[0] >= kFirstAbilityKey &&
			static_cast<std::size_t>(input[0] - kFirstAbilityKey) < option_count;
}

std::size_t GameLoop::ReadMenuChoice(std::size_t option_count) const {
	std::string input;
	std::cin >> input;
	while (!IsMenuKey(input, option_count)) {
		if (!std::cin) {
			throw std::runtime_error("input closed");
		}
		std::cin >> input;
	}
	return static_cast<std::size_t>(input[0] - kFirstAbilityKey);
}

void GameLoop::HandleRankUps() {
	Robot &player = FindPlayerRobot();
	while (player.ConsumeRankUp()) {
		ChooseRankUpReward(player);
	}
}

void GameLoop::ChooseRankUpReward(Robot &player) {
	std::cout << "Rank up choose reward:" << std::endl;
	for (int i = 0; i < kAbilityTypeCount; ++i) {
		std::cout << (i + 1) << ") " << ability_factory_.Create(static_cast<AbilityType>(i))->GetName() << std::endl;
	}
	AbilityType chosen = static_cast<AbilityType>(ReadMenuChoice(kAbilityTypeCount));
	player.AddOrUpgradeAbility(ability_factory_.Create(chosen));
}

void GameLoop::UsePlayerAbility(Robot &player, std::size_t index) const {
	int target_row = player.GetRow();
	int target_col = player.GetCol();
	if (player.GetAbilities()[index]->NeedsTarget()) {
		std::cout << "Target offset (rows cols): ";
		int row_offset = 0;
		int col_offset = 0;
		if (!(std::cin >> row_offset >> col_offset)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
		target_row += row_offset;
		target_col += col_offset;
	}
	player.UseAbility(index, target_row, target_col, game_field_, robots_);
}

void GameLoop::EndTurnAll() {
	for (Robot &robot: robots_) {
		if (robot.GetHealth() > 0) {
			robot.EndTurn();
		}
	}
}
