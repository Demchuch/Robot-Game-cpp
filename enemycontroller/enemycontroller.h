#ifndef OOP_ENEMY_ENEMY_CONTROLLER_H_
#define OOP_ENEMY_ENEMY_CONTROLLER_H_

#include <vector>
#include <cstdlib>
#include "../robot/robot.h"
#include "../movement/movement.h"

class EnemyController {
public:
	EnemyController(std::vector<Robot> &robots, MovementSystem &movement);
	Robot *FindRobotAt(int row, int col) const;
	void AiTurn();

private:
	Robot *FindNearestHostile(const Robot &robot) const;
	std::vector<Robot> &robots_;
	MovementSystem &movement_;
};

#endif  // OOP_ENEMY_ENEMY_CONTROLLER_H_