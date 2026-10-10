//
// Created by Maksim on 10.10.2026.
//

#include "enemycontroller.h"



EnemyController::EnemyController( std::vector<Robot> &robots, MovementSystem &movement)
	: robots_(robots), movement_(movement){}



void EnemyController::AiTurn() {
	for (Robot &robot : robots_) {
		if (robot.GetTeam() != Team::kPlayer && robot.GetHealth() > 0) {
			Robot *target = FindNearestHostile(robot);
			if (target == nullptr) {
				continue;
			}
			int row_diff = target->GetRow() - robot.GetRow();
			int col_diff = target->GetCol() - robot.GetCol();

			bool row_is_primary = std::abs(row_diff) > std::abs(col_diff);

			if (row_is_primary) {
				int next_row = robot.GetRow() + (row_diff > 0 ? 1 : -1);
				int next_col = robot.GetCol();
				bool moved = movement_.Action(robot, FindRobotAt(next_row, next_col), next_row, next_col);
				if (!moved && col_diff != 0) {
					int side_col = robot.GetCol() + (col_diff > 0 ? 1 : -1);
					movement_.Action(robot, FindRobotAt(robot.GetRow(), side_col), robot.GetRow(),
									side_col);
				}
			} else {
				int next_row = robot.GetRow();
				int next_col = robot.GetCol() + (col_diff > 0 ? 1 : -1);
				bool moved = movement_.Action(robot, FindRobotAt(next_row, next_col),  next_row, next_col);
				if (!moved && row_diff != 0) {
					int side_row = robot.GetRow() + (row_diff > 0 ? 1 : -1);
					movement_.Action(robot, FindRobotAt(side_row, robot.GetCol()),  side_row,
									robot.GetCol());
				}
			}
		}
	}
}

Robot *EnemyController::FindNearestHostile(const Robot &robot) const {
	Robot *nearest = nullptr;
	int nearest_distance = 0;
	for (Robot &candidate : robots_) {
		if (candidate.GetHealth() == 0 || robot.IsFriendlyTo(candidate)) {
			continue;
		}
		int distance = std::abs(candidate.GetRow() - robot.GetRow()) + std::abs(candidate.GetCol() - robot.GetCol());
		if (nearest == nullptr || distance < nearest_distance) {
			nearest = &candidate;
			nearest_distance = distance;
		}
	}
	return nearest;
}

Robot *EnemyController::FindRobotAt(int row, int col) const {
	for (Robot &robot : robots_) {
		if (robot.GetHealth() == 0) {
			continue;
		}
		if (robot.GetRow() == row && robot.GetCol() == col) {
			return &robot;
		}
	}
	return nullptr;
}