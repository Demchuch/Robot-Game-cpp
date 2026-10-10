//
// Created by Maksim on 04.10.2026.
//

#ifndef OOP_ROBOTFACTORY_H
#define OOP_ROBOTFACTORY_H
#include <utility>
#include <vector>

#include "../robot/robot.h"
#include "../robot/team.h"
#include "../gamefield/gamefield.h"


class RobotFactory {
public:
	RobotFactory(int row, int col, int turns_between_spawns);

	int GetRow() const;

	int GetCol() const;

	void EndTurn();

	bool IsReadyToSpawn() const;

	Robot CreateEnemy(int row, int col);

	std::vector<std::pair<int, int> > GetAdjacentCells() const;

	bool Occupies(int row, int col) const;

	void PlaceOn(GameField &field) const;

private:
	int row_;
	int col_;
	int turns_between_spawns_;
	int turns_since_spawn_ = 0;
};


#endif //OOP_ROBOTFACTORY_H
