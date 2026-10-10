#include "robot/robot.h"
#include "gamefield/gamefield.h"
#include "visualizer/visualizer.h"
#include <vector>
#include "config/game_constants.h"
#include "gameloop/gameloop.h"

int main() {
	GameField field(kFieldWidth, kFieldHeight);

	Robot player(100, 10, 50, 100, Team::kPlayer, kFieldHeight / 2, kFieldWidth / 2, 4, kVisionRadius);
	Robot ally(80, 20, 50, 100, Team::kAlly, 2, 2, 3, kVisionRadius);
	Robot enemy1(80, 20, 50, 100, Team::kEnemy, 5, 7, 3, kVisionRadius);
	Robot enemy2(80, 20, 50, 100, Team::kEnemy, 5, 10, 3, kVisionRadius);

	field.SetWalkable(3, 12, false);
	field.SetWalkable(3, 9, false);
	field.SetWalkable(3, 8, false);
	field.SetWalkable(3, 7, false);
	field.SetWalkable(3, 6, false);
	field.SetWalkable(3, 3, false);
	field.SetWalkable(3, 2, false);
	field.SetWalkable(3, 1, false);

	field.SetMovementCost(11, 4, kSlowCellThreshold);
	field.SetMovementCost(10, 15, kSlowCellThreshold);
	field.SetMovementCost(9, 17, kSlowCellThreshold);
	field.SetMovementCost(8, 14, kSlowCellThreshold);
	field.SetMovementCost(7, 6, kSlowCellThreshold);
	field.SetMovementCost(6, 12, kSlowCellThreshold);
	field.SetMovementCost(5, 5, kSlowCellThreshold);
	field.SetMovementCost(4, 20, kSlowCellThreshold);
	field.SetMovementCost(3, 9, kSlowCellThreshold);
	field.SetMovementCost(2, 2, kSlowCellThreshold);
	field.SetMovementCost(1, 10, kSlowCellThreshold);

	RobotFactory factory(5, 20, 10);
	std::vector<RobotFactory> factories = {factory};
	std::vector<Robot> robots = {player, enemy1, enemy2, ally};

	GameLoop game_loop(field, robots, factories);
	game_loop.Run();

	return 0;
}
