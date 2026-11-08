#ifndef OOP_ENEMY_ENEMY_CONTROLLER_H_
#define OOP_ENEMY_ENEMY_CONTROLLER_H_

#include <vector>
#include <cstddef>
#include <cstdlib>
#include "../gamefield/gamefield.h"
#include "../robot/robot.h"
#include "../movement/movement.h"

class EnemyController {
public:
	EnemyController(std::vector<Robot> &robots, MovementSystem &movement, GameField &game_field);
	Robot *FindRobotAt(int row, int col) const;
	void AiTurn();

private:
	void UseAbilities(Robot &robot);
	void UseHeal(Robot &robot, std::size_t index);
	void UseTeleport(Robot &robot, std::size_t index);
	int Distance(const Robot &first, const Robot &second) const;
	Robot *FindNearestHostile(const Robot &robot) const;
	std::vector<Robot> &robots_;
	MovementSystem &movement_;
	GameField &game_field_;
};

#endif  // OOP_ENEMY_ENEMY_CONTROLLER_H_