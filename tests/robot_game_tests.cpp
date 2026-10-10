// Проверки защиты от недопустимых данных и ходов. Для каждой проверки
// выводится выполняемая команда и результат: ошибка (исключение) или отказ.
//
// Сборка из корня проекта (одной командой):
// g++ -std=c++20 -I. tests/robot_game_tests.cpp cell/cell.cpp gamefield/gamefield.cpp movement/movement.cpp robot/robot.cpp robotfactory/robotfactory.cpp -o tests_run

#include <exception>
#include <iostream>
#include <string>

#include "cell/cell.h"
#include "config/game_constants.h"
#include "gamefield/gamefield.h"
#include "movement/movement.h"
#include "robot/robot.h"
#include "robotfactory/robotfactory.h"

namespace {

int number = 0;
int failed = 0;

// Выполняет команду и ожидает исключение.
template<typename Fn>
void ExpectError(const std::string &code, Fn fn) {
	std::cout << ++number << ") " << code << "\n";
	try {
		fn();
		++failed;
		std::cout << "   [FAIL] ошибки не было\n";
	} catch (const std::exception &e) {
		std::cout << "   [OK] ошибка: " << e.what() << "\n";
	}
}

// Ожидает отказ: команда вернула false и робот остался на месте с прежними ресурсами.
void ExpectRefused(const std::string &code, bool result, const Robot &robot, int row, int col) {
	std::cout << ++number << ") " << code << "\n";
	bool unchanged = robot.GetRow() == row && robot.GetCol() == col && robot.GetEnergy() == 50 &&
	                 robot.GetRemainingSpeed() == 4;
	if (!result && unchanged) {
		std::cout << "   [OK] отказ: false, позиция (" << robot.GetRow() << ", " << robot.GetCol()
		          << "), энергия " << robot.GetEnergy() << ", скорость " << robot.GetRemainingSpeed() << "\n";
	} else {
		++failed;
		std::cout << "   [FAIL] ход выполнен или ресурсы изменились\n";
	}
}

}  // namespace

#define EXPECT_ERROR(...) ExpectError(#__VA_ARGS__ ";", [&] { __VA_ARGS__; })

int main() {
	GameField field(30, 15);

	EXPECT_ERROR(GameField small_field(1, 10));
	EXPECT_ERROR(Robot robot(0, 10, 50, 100, Team::kPlayer, 5, 5, 4, 5));
	EXPECT_ERROR(field.GetCell(-1, 0));
	EXPECT_ERROR(field.SetMovementCost(2, 2, 0));

	MovementSystem movement(field);
	Robot player(100, 10, 50, 100, Team::kPlayer, 5, 19, 4, 5);

	field.SetWalkable(5, 18, false);  // стена слева от игрока
	ExpectRefused("movement.Action(player, nullptr, 5, 18);  // клетка со стеной",
	              movement.Action(player, nullptr, 5, 18), player, 5, 19);

	RobotFactory factory(5, 20, 3);
	factory.PlaceOn(field);  // завод занимает клетки (5, 20)..(6, 21)
	ExpectRefused("movement.Action(player, nullptr, 5, 20);  // клетка завода",
	              movement.Action(player, nullptr, 5, 20), player, 5, 19);

	RobotFactory outside_factory(14, 10, 3);
	EXPECT_ERROR(outside_factory.PlaceOn(field));  // завод вылезает за нижнюю границу

	std::cout << (failed == 0 ? "Все проверки пройдены" : "Есть непройденные проверки") << "\n";
	return failed == 0 ? 0 : 1;
}
