//
// Created by Maksim on 30.09.2026.
//

#ifndef OOP_VISUALIZER_H
#define OOP_VISUALIZER_H
#include "../robot/robot.h"
#include "../gamefield/gamefield.h"
#include <vector>
#include "../robotfactory/robotfactory.h"


class Visualizer {
public:
	void Draw(const GameField &field, const std::vector<Robot> &robots,
			const std::vector<RobotFactory> &factories) const;

private:
	const char *GetRobotSymbol(Team team) const;

	bool IsFactoryAt(const std::vector<RobotFactory> &factories, int row, int col) const;
};


#endif //OOP_VISUALIZER_H
