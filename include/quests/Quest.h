#ifndef QUEST_H
#define QUEST_H

#include <string>

class Quest {
private:
    int id;
    std::string title;
    std::string description;
    int targetCount;
    int currentCount;
    int rewardGold;
    int rewardExp;
    bool completed;

public:
    Quest(int id, const std::string& title, const std::string& description, int targetCount, int rewardGold, int rewardExp);

    int getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    int getTargetCount() const;
    int getCurrentCount() const;
    int getRewardGold() const;
    int getRewardExp() const;
    bool isCompleted() const;

    void addProgress(int amount);
    void setCompleted(bool value);
};

#endif // QUEST_H