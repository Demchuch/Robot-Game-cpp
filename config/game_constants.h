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

const int kHealUpgrade = 5;
const int kHealAmount = 30;
const int kHealCost = 20;
const int kAbilityTypeCount = 4;
const int kAiHealThresholdPercent = 50;
const int kAiTeleportMinDistance = 3;
const int kAreaStrikeRadius = 1;
const int kAreaStrikeDamage = 15;
const int kAreaStrikeCost = 30;
const int kAreaStrikeRadiusUpgrade = 1;
const int kRangedStrikeRadius = 3;
const int kRangedStrikeDamage = 25;
const int kRangedStrikeCost = 30;
const int kRangedStrikeDamageUpgrade = 10;
const int kTeleportRadius = 5;
const int kTeleportCost = 40;
const int kTeleportCostUpgrade = 10;
const int kTeleportMinCost = 10;
const int kBurnDamage = 5;
const int kSlowDuration = 1;
const int kBurnDuration = 3;
const int kShieldCapacity = 20;

const int kMaxCellStatuses = 2;
const int kStatusTypeCount = 4;
const int kPercentTotal = 100;
const int kNoStatusChance = 90;
const int kOneStatusChance = 5;


const int kVisionRadius = 50;


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
const char kFirstAbilityKey = '1';
const char *const kKeyChangeDisplayMode = "m";
const int kDisplayModeCount = 4;
const int kAbilityColumnWidth = 10;
const char *const kControlsHelp = "w/a/s/d - move, e - end turn, 1-4 - use ability, m - display mode";


const char *const kUnknownCellSymbol = " ";
const char *const kFloorSymbol = ".";
const char *const kWallSymbol = "#";
const char *const kFactorySymbol = "\033[33mF\033[0m";
const char *const kPlayerSymbol = "\033[32mP\033[0m";
const char *const kEnemySymbol = "\033[31mE\033[0m";
const char *const kAllySymbol = "\033[34mA\033[0m";
const char *const kClearScreenSequence = "\033[H\033[2J\033[3J";
const char *const kSlowCellSymbol = "\033[33m.\033[0m";
const char *const kEnemyHighlightSymbol = "\033[41;97mE\033[0m";
const char *const kWallHighlightSymbol = "\033[47;30m#\033[0m";
const char *const kStatusCellSymbol = "\033[45;97m.\033[0m";
#endif  // OOP_CONFIG_GAME_CONSTANTS_H_
