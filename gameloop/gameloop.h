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
#include <iostream>
#include <string>
#include <stdexcept>
#include "../enemycontroller/enemycontroller.h"

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

	bool AllEnemiesDefeated() const;

	void PlayTurn();

	Robot &FindPlayerRobot() const;

	bool IsPlayerDefeated() const;

	bool HandlePlayerInput() const;




	void RegenerateEnergy();

	void ResetSpeed();

	bool TryMoveRobot(Robot &robot, int target_row, int target_col) const;

	void RevealAroundPlayer();

	bool IsCellFree(int row, int col) const;

	void SpawnEnemies();


};


#endif //OOP_GAMELOOP_H
