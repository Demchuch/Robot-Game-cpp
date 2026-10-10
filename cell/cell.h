//
// Created by Maksim on 28.09.2026.
//

#ifndef OOP_CELL_CELL_H_
#define OOP_CELL_CELL_H_


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

private:
	bool is_known_ = false;
	int movement_cost_;
	bool is_walkable_;
	bool is_visible_ = false;
};


#endif //OOP_CELL_CELL_H_
