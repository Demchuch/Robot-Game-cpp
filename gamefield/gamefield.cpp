//
// Created by Maksim on 29.09.2026.
//

#include "gamefield.h"

#include <stdexcept>
#include "../config/game_constants.h"


GameField::GameField(int width, int height) {
	if (width > kMinFieldSize && height > kMinFieldSize && width < kMaxFieldSize && height < kMaxFieldSize) {
		width_ = width;
		height_ = height;
		cells_.resize(height_);
		for (int row = 0; row < height_; ++row) {
			for (int col = 0; col < width_; ++col) {
				bool is_walkable = !(row == 0 || row == height_ - 1 || col == 0 || col == width_ - 1);
				cells_[row].push_back(Cell(is_walkable, kDefaultMovementCost));
			}
		}
	} else {
		throw std::invalid_argument("invalid size");
	}
}

const Cell &GameField::GetCell(int row, int col) const {
	if (!IsInside(row, col)) {
		throw std::invalid_argument("cell is outside the field");
	}
	return cells_[row][col];
}

void GameField::SetWalkable(int row, int col, bool is_walkable) {
	if (!IsInside(row, col)) {
		throw std::invalid_argument("cell is outside the field");
	}
	cells_[row][col].SetWalkable(is_walkable);
}


void GameField::SetWalkableArea(int top_row, int left_col, int height, int width, bool is_walkable) {
	if (height < 1 || width < 1) {
		throw std::invalid_argument("incorrect size");
	}
	if (!(IsInside(top_row, left_col) && IsInside(top_row + height - 1, left_col + width - 1))) {
		throw std::invalid_argument("area not inside");
	}
	for (int row = top_row; row <= top_row + height - 1; ++row) {
		for (int col = left_col; col <= left_col + width - 1; ++col) {
			SetWalkable(row, col, is_walkable);
		}
	}
}


void GameField::RevealCell(int row, int col) {
	if (!IsInside(row, col)) {
		throw std::invalid_argument("cell is outside the field");
	}
	cells_[row][col].SetKnown();
	cells_[row][col].SetVisible(true);
}


void GameField::SetMovementCost(int row, int col, int cost) {
	if (!IsInside(row, col)) {
		throw std::invalid_argument("cell is outside the field");
	}
	cells_[row][col].SetMovementCost(cost);
}

bool GameField::IsInside(int row, int col) const {
	return row >= 0 && row < height_ && col >= 0 && col < width_;
}

int GameField::GetWidth() const {
	return width_;
}

int GameField::GetHeight() const {
	return height_;
}

void GameField::ClearVisibility() {
	for (int row = 0; row < height_; ++row) {
		for (int col = 0; col < width_; ++col) {
			cells_[row][col].SetVisible(false);
		}
	}
}
