// robot.h
#ifndef OOP_ROBOT_ROBOT_H_
#define OOP_ROBOT_ROBOT_H_

#include <cstddef>
#include <memory>
#include <vector>

#include "../ability/ability.h"
#include "../status/status.h"
#include "team.h"

class GameField;


class Robot {
public:
	Robot(int max_health, int attack_power, int max_energy, int experience_to_next_rank, Team team, int row, int col,
		int speed, int vision_radius);


	int GetRow() const;

	int GetCol() const;

	int GetHealth() const;

	int GetMaxHealth() const;

	int GetAttackPower() const;

	int GetEnergy() const;

	int GetMaxEnergy() const;

	int GetRank() const;

	Team GetTeam() const;

	void SetMaxHealth(int max_health);

	void SetAttackPower(int attack_power);

	void SetMaxEnergy(int max_energy);

	void SetExperienceToNextRank(int experience_to_next_rank);

	void SetSpeed(int speed);

	bool IsFriendlyTo(const Robot &other) const;

	int GetVisionRadius() const;

	void SetVisionRadius(int vision_radius);

	void TakeDamage(int amount);

	void Heal(int amount);

	bool InteractWith(Robot &other);

	void GainExperience(int amount);

	void RegenerateEnergy(int amount);

	bool SetPosition(int row, int col, int cost);

	void TeleportTo(int row, int col);

	int GetExperience() const;

	int GetExperienceToNextRank() const;

	void ResetSpeed();

	int GetSpeed() const;

	int GetRemainingSpeed() const;

	bool SpendEnergy(int amount);

	bool AddAbility(std::shared_ptr<Ability> ability);

	const std::vector<std::shared_ptr<Ability> > &GetAbilities() const;

	bool UseAbility(std::size_t index, int target_row, int target_col,
					GameField &field, std::vector<Robot> &robots);

	void AddOrUpgradeAbility(std::shared_ptr<Ability> ability);

	bool ConsumeRankUp();

	void AddStatus(std::shared_ptr<Status> status);

	const std::vector<std::shared_ptr<Status> > &GetStatuses() const;

	bool CanMove() const;

	void EndTurn();

private:
	void RemoveExpiredStatuses();


	bool SpendSpeed(int amount);

	static int Clamp(int value, int min_value, int max_value);

	void RankUp();

	int vision_radius_;
	int health_;
	int max_health_;
	int attack_power_;
	int energy_;
	int max_energy_;
	int experience_;
	int experience_to_next_rank_;
	int rank_;
	int row_ = 1;
	int col_ = 1;
	Team team_;
	int remaining_speed_;
	int speed_;
	int pending_rank_ups_ = 0;
	std::vector<std::shared_ptr<Ability> > abilities_;
	std::vector<std::shared_ptr<Status> > statuses_;
};

#endif  // OOP_ROBOT_ROBOT_H_
