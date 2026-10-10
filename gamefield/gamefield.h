//
// Created by Maksim on 29.09.2026.
//

#ifndef OOP_GAMEFIELD_GAMEFIELD_H_
#define OOP_GAMEFIELD_GAMEFIELD_H_

#include <vector>
#include "../cell/cell.h"

class GameField {
public:
	GameField(int width, int height);

	int GetWidth() const;

	int GetHeight() const;

	const Cell &GetCell(int row, int col) const;

	bool IsInside(int row, int col) const;

	void SetWalkable(int row, int col, bool is_walkable);

	void SetMovementCost(int row, int col, int cost);

	void RevealCell(int row, int col);

	void SetWalkableArea(int top_row, int left_col, int height, int width, bool is_walkable);

	void ClearVisibility();

private:
	int width_;
	int height_;
	std::vector<std::vector<Cell> > cells_;
};


#endif //OOP_GAMEFIELD_GAMEFIELD_H_
