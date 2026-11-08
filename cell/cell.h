//
// Created by Maksim on 28.09.2026.
//

#ifndef OOP_CELL_CELL_H_
#define OOP_CELL_CELL_H_

#include <cstddef>
#include <vector>

#include "../status/status_type.h"


class Cell {
public:
	Cell(bool is_walkable, int movement_cost);

	int GetMovementCost() const;

	bool GetKnown() const;

	bool GetWalkable() const;

	void SetKnown();

	void SetWalkable(bool is_walkable);

	void SetMovementCost(int movement_cost);

	bool GetVisible() const;

	void SetVisible(bool is_visible);

	const std::vector<StatusType> &GetStatuses() const;

	void AddStatus(StatusType type);

	void RemoveStatusAt(std::size_t index);

private:
	bool is_known_ = false;
	int movement_cost_;
	bool is_walkable_;
	bool is_visible_ = false;
	std::vector<StatusType> statuses_;
};


#endif //OOP_CELL_CELL_H_
