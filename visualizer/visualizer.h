//
// Created by Maksim on 30.09.2026.
//

#ifndef OOP_VISUALIZER_H
#define OOP_VISUALIZER_H
#include "../robot/robot.h"
#include "../gamefield/gamefield.h"
#include <string>
#include <vector>
#include "../robotfactory/robotfactory.h"
#include "display_mode.h"


class Visualizer {
public:
	void Draw(const GameField &field, const std::vector<Robot> &robots,
			const std::vector<RobotFactory> &factories, DisplayMode mode) const;

private:
	std::string GetCellSymbol(const GameField &field, const std::vector<Robot> &robots,
							const std::vector<RobotFactory> &factories, int row, int col,
							DisplayMode mode) const;

	const Robot *FindVisibleRobotAt(const std::vector<Robot> &robots, int row, int col) const;

	std::string GetModeDescription(DisplayMode mode) const;

	void DrawHud(const GameField &field, const std::vector<Robot> &robots, DisplayMode mode) const;

	void DrawPlayer(const Robot &player) const;

	void DrawRobotRow(const Robot &robot, const Robot &player) const;

	std::string GetStatusNames(const Robot &robot) const;

	std::string GetAbilityNames(const Robot &robot) const;

	const char *GetRobotSymbol(Team team) const;

	bool IsFactoryAt(const std::vector<RobotFactory> &factories, int row, int col) const;
};


#endif //OOP_VISUALIZER_H
