//
// Created by Maksim on 30.09.2026.
//

#ifndef OOP_GAMELOOP_H
#define OOP_GAMELOOP_H
#include "../gamefield/gamefield.h"
#include "../robot/robot.h"
#include "../movement/movement.h"
#include "../visualizer/visualizer.h"
#include "../cell/cell.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "../enemycontroller/enemycontroller.h"
#include "../ability/ability_factory.h"
#include "../visualizer/display_mode.h"

class GameLoop {
public:
	GameLoop(GameField &game_field, std::vector<Robot> &robots, std::vector<RobotFactory> &factories);

	void Run();

private:
	GameField &game_field_;
	std::vector<RobotFactory> &factories_;
	std::vector<Robot> &robots_;
	MovementSystem movement_system_;
	EnemyController enemy_controller_;
	AbilityFactory ability_factory_;
	DisplayMode display_mode_ = DisplayMode::kStandard;

	bool IsMenuKey(const std::string &input, std::size_t option_count) const;

	std::size_t ReadMenuChoice(std::size_t option_count) const;

	bool AllEnemiesDefeated() const;

	void PlayTurn();

	Robot &FindPlayerRobot() const;

	bool IsPlayerDefeated() const;

	bool HandlePlayerInput();




	void RegenerateEnergy();

	void ResetSpeed();

	bool TryMoveRobot(Robot &robot, int target_row, int target_col) const;

	void RevealAroundPlayer();

	bool IsCellFree(int row, int col) const;

	void SpawnEnemies();

	void ChooseStartingAbility();

	void HandleRankUps();

	void ChooseRankUpReward(Robot &player);

	void UsePlayerAbility(Robot &player, std::size_t index) const;

	void EndTurnAll();


};


#endif //OOP_GAMELOOP_H
