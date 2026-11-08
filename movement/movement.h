//
// Created by Maksim on 29.09.2026.
//

#ifndef OOP_MOVEMENT_H
#define OOP_MOVEMENT_H
#include "../robot/robot.h"
#include "../gamefield/gamefield.h"
#include "../status/status_factory.h"


class MovementSystem {
public:
	explicit MovementSystem(GameField &game_field);

	bool Action(Robot &robot, Robot *opponent, int row, int col) const;

private:
	void ApplyCellStatuses(Robot &robot, int row, int col) const;

	GameField &game_field_;
	StatusFactory status_factory_;
};
#endif //OOP_MOVEMENT_H
