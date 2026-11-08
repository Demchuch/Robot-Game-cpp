//
// Created by Maksim on 10.10.2026.
//

#include "enemycontroller.h"

#include <algorithm>
#include <vector>

#include "../config/game_constants.h"

namespace {

int Sign(int value) {
	return (value > 0) - (value < 0);
}

}  // namespace



EnemyController::EnemyController(std::vector<Robot> &robots, MovementSystem &movement, GameField &game_field)
	: robots_(robots), movement_(movement), game_field_(game_field) {}



void EnemyController::AiTurn() {
	for (Robot &robot : robots_) {
		if (robot.GetTeam() != Team::kPlayer && robot.GetHealth() > 0) {
			UseAbilities(robot);
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
		int distance = Distance(candidate, robot);
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

int EnemyController::Distance(const Robot &first, const Robot &second) const {
	return std::abs(first.GetRow() - second.GetRow()) + std::abs(first.GetCol() - second.GetCol());
}

void EnemyController::UseAbilities(Robot &robot) {
	const std::vector<std::shared_ptr<Ability> > &abilities = robot.GetAbilities();
	for (std::size_t i = 0; i < abilities.size(); ++i) {
		if (abilities[i]->GetType() == AbilityType::kHeal) {
			UseHeal(robot, i);
		} else if (abilities[i]->GetType() == AbilityType::kTeleport) {
			UseTeleport(robot, i);
		}
	}
}

void EnemyController::UseHeal(Robot &robot, std::size_t index) {
	while (robot.GetHealth() * kPercentTotal < robot.GetMaxHealth() * kAiHealThresholdPercent) {
		if (!robot.UseAbility(index, robot.GetRow(), robot.GetCol(), game_field_, robots_)) {
			break;
		}
	}
}

void EnemyController::UseTeleport(Robot &robot, std::size_t index) {
	Robot *target = FindNearestHostile(robot);
	if (target == nullptr || Distance(robot, *target) <= kAiTeleportMinDistance) {
		return;
	}
	int row_diff = target->GetRow() - robot.GetRow();
	int col_diff = target->GetCol() - robot.GetCol();
	int row_offset = std::clamp(row_diff - Sign(row_diff), -kTeleportRadius, kTeleportRadius);
	int col_offset = std::clamp(col_diff - Sign(col_diff), -kTeleportRadius, kTeleportRadius);
	robot.UseAbility(index, robot.GetRow() + row_offset, robot.GetCol() + col_offset, game_field_, robots_);
}
