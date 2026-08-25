#ifndef QUESTSYSTEM_H
#define QUESTSYSTEM_H

#include "quests/Quest.h"
#include <vector>

class Character; // Forward declaration

class QuestSystem {
private:
    std::vector<Quest> questList;

public:
    QuestSystem();
    void openQuestLog(Character& player);
    void updateProgress(int questId, int amount);
};

#endif // QUESTSYSTEM_H