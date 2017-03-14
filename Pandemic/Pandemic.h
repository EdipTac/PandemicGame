#pragma once

//  ----  Forward declarations  ----  //
void directConnectionReport();
void displayCities();
void displayReferenceCard();
void infect();
void loadGame();
void newGame();
void quit();
void waitForExit();

bool actionQuit();
bool buildResearchStation();
bool charterFlight();
bool cureDisease();
bool directFlight();
bool driveOrFerry();
bool giveKnowledge(Player& target);
bool performAction();
bool report();
bool saveGame();
bool shareKnowledge();
bool shuttleFlight();
bool takeKnowledge(Player& target);
bool treatDisease();

size_t solicitSize(const size_t min, const size_t max);

std::string solicitFileName(const std::string& msg);
std::string solicitPlayerName(const size_t number);
std::string titleFont(const std::string& original);

City& solicitConnection(const City& source);

template <typename T> void list(const T& collection);
template <typename T> T validateInput(const std::map<std::string, T>& validInputs, const std::string& errMsg);
template <typename T> T validateInput(const std::vector<T>& valid, const std::string& errMsg);

const auto& saveGameAction = static_cast<bool(*)()>(saveGame);

//  ----  Game pointer - global data  ----  //
std::unique_ptr<GameState> game;

//  ----  Constants  -----  //
constexpr size_t minPlayers = 1;
constexpr size_t maxPlayers = 4;
constexpr size_t actionsPerTurn = 4;
constexpr size_t cardsPerTurn = 2;
