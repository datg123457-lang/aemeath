#include "quests/Quest.h"
#include <algorithm>

Quest::Quest(int id, const std::string& title, const std::string& description, int targetCount, int rewardGold, int rewardExp)
    : id(id), title(title), description(description), targetCount(targetCount), currentCount(0),
      rewardGold(rewardGold), rewardExp(rewardExp), completed(false) {}

int Quest::getId() const { return id; }
std::string Quest::getTitle() const { return title; }
std::string Quest::getDescription() const { return description; }
int Quest::getTargetCount() const { return targetCount; }
int Quest::getCurrentCount() const { return currentCount; }
int Quest::getRewardGold() const { return rewardGold; }
int Quest::getRewardExp() const { return rewardExp; }
bool Quest::isCompleted() const { return completed; }

void Quest::addProgress(int amount) {
    if (!completed) {
        currentCount = std::min(targetCount, currentCount + amount);
    }
}

void Quest::setCompleted(bool value) { 
    completed = value; 
}