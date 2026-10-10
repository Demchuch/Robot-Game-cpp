// robot.h
#ifndef OOP_ROBOT_ROBOT_H_
#define OOP_ROBOT_ROBOT_H_

#include "team.h"


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

	int GetExperience() const;

	int GetExperienceToNextRank() const;

	void ResetSpeed();

	int GetSpeed() const;

	int GetRemainingSpeed() const;

private:
	bool SpendEnergy(int amount);

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
};

#endif  // OOP_ROBOT_ROBOT_H_
