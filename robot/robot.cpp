//
// Created by Maksim on 28.09.2026.
//

#include "robot.h"

#include <algorithm>
#include <stdexcept>

#include "../config/game_constants.h"

Robot::Robot(int max_health, int attack_power, int max_energy, int experience_to_next_rank, Team team, int row, int col,
			int speed, int vision_radius) {
	if (max_health <= 0) {
		throw std::invalid_argument("incorrect max_health value");
	}
	if (attack_power < 0) {
		throw std::invalid_argument("incorrect attack_power value");
	}
	if (max_energy < kActionCost) {
		throw std::invalid_argument("incorrect max_energy value");
	}
	if (experience_to_next_rank <= 0) {
		throw std::invalid_argument("incorrect experience_to_next_rank value");
	}
	if (speed < kMinSpeed) {
		throw std::invalid_argument("incorrect speed value");
	}
	if (row < 0 || col < 0) {
		throw std::invalid_argument("incorrect position value");
	}
	if (vision_radius <= 0) {
		throw std::invalid_argument("incorrect vision_radius value");
	}
	max_health_ = max_health;
	health_ = max_health;
	energy_ = max_energy;
	max_energy_ = max_energy;
	experience_ = 0;
	attack_power_ = attack_power;
	rank_ = kInitialRank;
	experience_to_next_rank_ = experience_to_next_rank;
	team_ = team;
	row_ = row;
	col_ = col;
	speed_ = speed;
	remaining_speed_ = speed;
	vision_radius_ = vision_radius;
}


int Robot::GetExperience() const {
	return experience_;
}

int Robot::GetExperienceToNextRank() const {
	return experience_to_next_rank_;
}


int Robot::Clamp(int value, int min_value, int max_value) {
	if (value < min_value) {
		return min_value;
	}
	if (value > max_value) {
		return max_value;
	}
	return value;
}

int Robot::GetHealth() const {
	return health_;
}

int Robot::GetCol() const {
	return col_;
}

int Robot::GetRow() const {
	return row_;
}

int Robot::GetMaxHealth() const {
	return max_health_;
}

int Robot::GetAttackPower() const {
	return attack_power_;
}

int Robot::GetEnergy() const {
	return energy_;
}

int Robot::GetMaxEnergy() const {
	return max_energy_;
}

Team Robot::GetTeam() const {
	return team_;
}


void Robot::TakeDamage(int amount) {
	if (amount < 0) {
		throw std::invalid_argument("damage must not be negative");
	}
	for (const std::shared_ptr<Status> &status: statuses_) {
		amount = status->AbsorbDamage(amount);
	}
	health_ = Clamp(health_ - amount, 0, max_health_);
	RemoveExpiredStatuses();
}

void Robot::Heal(int amount) {
	if (amount < 0) {
		throw std::invalid_argument("heal amount must not be negative");
	}
	health_ = Clamp(health_ + amount, 0, max_health_);
}

bool Robot::InteractWith(Robot &other) {
	if (SpendEnergy(kActionCost)) {
		if (IsFriendlyTo(other)) {
			other.Heal(attack_power_);
		} else {
			other.TakeDamage(attack_power_);
			if (other.GetHealth() == 0) {
				GainExperience(kExperienceForKill);
			}
		}
		return true;
	}
	return false;
}


void Robot::RankUp() {
	rank_ += 1;
	max_health_ += kRankUpHealthBonus;
	attack_power_ += kRankUpAttackBonus;
	max_energy_ += kRankUpEnergyBonus;
	experience_to_next_rank_ *= kRankUpExperienceMultiplier;
	health_ = max_health_;
	energy_ = max_energy_;
	++pending_rank_ups_;
}

bool Robot::SetPosition(int row, int col, int cost) {
	if (row < 0 || col < 0) {
		throw std::invalid_argument("position must not be negative");
	}
	if (cost < kMinMovementCost) {
		throw std::invalid_argument("movement cost is below the minimum");
	}
	if (CanMove() && energy_ >= kActionCost && remaining_speed_ >= cost) {
		SpendEnergy(kActionCost);
		SpendSpeed(cost);
		row_ = row;
		col_ = col;
		return true;
	}

	return false;
}

bool Robot::SpendEnergy(int amount) {
	if (amount > energy_) {
		return false;
	}
	energy_ -= amount;
	return true;
}

int Robot::GetRemainingSpeed() const {
	return remaining_speed_;
}

int Robot::GetSpeed() const {
	return speed_;
}

bool Robot::SpendSpeed(int amount) {
	if (remaining_speed_ >= amount) {
		remaining_speed_ -= amount;
		return true;
	}
	return false;
}


void Robot::ResetSpeed() {
	remaining_speed_ = speed_;
}

void Robot::GainExperience(int amount) {
	if (amount < 0) {
		throw std::invalid_argument("experience must not be negative");
	}
	experience_ += amount;
	while (experience_ >= experience_to_next_rank_) {
		RankUp();
	}
}

int Robot::GetVisionRadius() const {
	return vision_radius_;
}

void Robot::SetVisionRadius(int vision_radius) {
	if (vision_radius <= 0) {
		throw std::invalid_argument("vision_radius must be positive");
	}
	vision_radius_ = vision_radius;
}


void Robot::RegenerateEnergy(int amount) {
	if (amount < 0) {
		throw std::invalid_argument("energy amount must not be negative");
	}
	energy_ = Clamp(energy_ + amount, 0, max_energy_);
}


bool Robot::IsFriendlyTo(const Robot &other) const {
	Team other_team = other.GetTeam();
	return team_ == other_team ||
			(team_ != Team::kEnemy && other_team != Team::kEnemy);
}

void Robot::SetMaxHealth(int max_health) {
	if (max_health <= 0) {
		throw std::invalid_argument("max_health must be positive");
	}
	max_health_ = max_health;
	if (health_ > max_health_) {
		health_ = max_health_;
	}
}

void Robot::SetAttackPower(int attack_power) {
	if (attack_power < 0) {
		throw std::invalid_argument("attack_power must not be negative");
	}
	attack_power_ = attack_power;
}

void Robot::SetMaxEnergy(int max_energy) {
	if (max_energy < kActionCost) {
		throw std::invalid_argument("max_energy must be at least kActionCost");
	}
	max_energy_ = max_energy;
	if (energy_ > max_energy_) {
		energy_ = max_energy_;
	}
}

void Robot::SetExperienceToNextRank(int experience_to_next_rank) {
	if (experience_to_next_rank <= 0) {
		throw std::invalid_argument("experience_to_next_rank must be positive");
	}
	experience_to_next_rank_ = experience_to_next_rank;
}


int Robot::GetRank() const {
	return rank_;
}

void Robot::SetSpeed(int speed) {
	if (speed < kMinSpeed) {
		throw std::invalid_argument("speed must be at least kMinSpeed");
	}
	speed_ = speed;
	if (remaining_speed_ > speed_) {
		remaining_speed_ = speed_;
	}
}

void Robot::TeleportTo(int row, int col) {
	if (row < 0 || col < 0) {
		throw std::invalid_argument("position must not be negative");
	}
	row_ = row;
	col_ = col;
}

bool Robot::AddAbility(std::shared_ptr<Ability> ability) {
	if (ability == nullptr) {
		throw std::invalid_argument("ability must not be null");
	}
	for (const std::shared_ptr<Ability> &owned: abilities_) {
		if (owned->GetName() == ability->GetName()) {
			return false;
		}
	}
	abilities_.push_back(ability);
	return true;
}

const std::vector<std::shared_ptr<Ability> > &Robot::GetAbilities() const {
	return abilities_;
}

bool Robot::UseAbility(std::size_t index, int target_row, int target_col,
					GameField &field, std::vector<Robot> &robots) {
	if (index >= abilities_.size()) {
		return false;
	}
	bool is_blocked = false;
	for (const std::shared_ptr<Status> &status: statuses_) {
		if (status->BlocksAbilities()) {
			status->OnAbilityAttempt();
			is_blocked = true;
		}
	}
	if (is_blocked) {
		RemoveExpiredStatuses();
		return false;
	}
	return abilities_[index]->Use(*this, target_row, target_col, field, robots);
}

void Robot::AddOrUpgradeAbility(std::shared_ptr<Ability> ability) {
	if (AddAbility(ability)) {
		return;
	}
	for (const std::shared_ptr<Ability> &owned: abilities_) {
		if (owned->GetName() == ability->GetName()) {
			owned->Upgrade();
		}
	}
}

bool Robot::ConsumeRankUp() {
	if (pending_rank_ups_ == 0) {
		return false;
	}
	--pending_rank_ups_;
	return true;
}

void Robot::AddStatus(std::shared_ptr<Status> status) {
	if (status == nullptr) {
		throw std::invalid_argument("status must not be null");
	}
	for (const std::shared_ptr<Status> &owned: statuses_) {
		if (owned->GetName() == status->GetName()) {
			owned->Stack(*status);
			return;
		}
	}
	statuses_.push_back(status);
}

const std::vector<std::shared_ptr<Status> > &Robot::GetStatuses() const {
	return statuses_;
}

bool Robot::CanMove() const {
	for (const std::shared_ptr<Status> &status: statuses_) {
		if (status->BlocksMovement()) {
			return false;
		}
	}
	return true;
}

void Robot::EndTurn() {
	std::vector<std::shared_ptr<Status> > snapshot = statuses_;
	for (const std::shared_ptr<Status> &status: snapshot) {
		status->OnTurnEnd(*this);
	}
	RemoveExpiredStatuses();
}

void Robot::RemoveExpiredStatuses() {
	std::vector<std::shared_ptr<Status> > alive;
	for (const std::shared_ptr<Status> &status: statuses_) {
		if (!status->IsExpired()) {
			alive.push_back(status);
		}
	}
	statuses_ = alive;
}
