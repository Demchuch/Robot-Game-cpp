#ifndef OOP_CONFIG_GAME_CONSTANTS_H_
#define OOP_CONFIG_GAME_CONSTANTS_H_


const int kActionCost = 10;
const int kRegenerateEnergy = 30;


const int kExperienceForKill = 100;
const int kInitialRank = 1;
const int kMinSpeed = 1;
const int kRankUpHealthBonus = 10;
const int kRankUpAttackBonus = 2;
const int kRankUpEnergyBonus = 10;
const int kRankUpExperienceMultiplier = 3;


const int kMinFieldSize = 1;
const int kFieldHeight = 15;
const int kFieldWidth = 30;
const int kMaxFieldSize = 101;
const int kDefaultMovementCost = 1;
const int kMinMovementCost = 1;
const int kSlowCellThreshold = 3;


const int kVisionRadius = 5;


const int kFactorySize = 2;
const int kSpawnedMaxHealth = 80;
const int kSpawnedAttackPower = 20;
const int kSpawnedExperienceToNextRank = 100;
const int kSpawnedMaxEnergy = 50;
const int kSpawnedSpeed = 3;


const char *const kKeyMoveUp = "w";
const char *const kKeyMoveLeft = "a";
const char *const kKeyMoveDown = "s";
const char *const kKeyMoveRight = "d";
const char *const kKeyEndTurn = "e";


const char *const kUnknownCellSymbol = " ";
const char *const kFloorSymbol = ".";
const char *const kWallSymbol = "#";
const char *const kFactorySymbol = "\033[33mF\033[0m";
const char *const kPlayerSymbol = "\033[32mP\033[0m";
const char *const kEnemySymbol = "\033[31mE\033[0m";
const char *const kAllySymbol = "\033[34mA\033[0m";
const char *const kClearScreenSequence = "\033[H\033[2J\033[3J";
const char *const kSlowCellSymbol = "\033[33m.\033[0m";
#endif  // OOP_CONFIG_GAME_CONSTANTS_H_
