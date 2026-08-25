#include "core/QuestSystem.h"
#include "entities/Character.h"
#include "utils/ConsoleUtils.h"
#include <string>
#include <vector>

QuestSystem::QuestSystem() {
    questList.push_back(Quest(1, "Mối Đe Dọa Goblin", "Đánh bại 5 Goblin tại Rừng Tối", 5, 100, 150));
    questList.push_back(Quest(2, "Cổ Vật Thất Lạc", "Thu thập 3 Cổ Vật Tri Thức", 3, 250, 300));
}

void QuestSystem::openQuestLog(Character& player) {
    while (true) {
        std::vector<std::string> options;
        
        // Tạo danh sách hiển thị các nhiệm vụ
        for (const auto& q : questList) {
            std::string status = q.isCompleted() ? "[ĐA HOAN THANH]" : 
                                 ("(" + std::to_string(q.getCurrentCount()) + "/" + std::to_string(q.getTargetCount()) + ")");
            options.push_back(q.getTitle() + " - " + q.getDescription() + " " + status);
        }
        
        options.push_back("Nhan thuong tat ca nhiem vu da xong");
        options.push_back("Quay lai Menu chinh");

        // Gọi UI từ ConsoleUtils
        int choice = ConsoleUtils::showMenuCustom("NHAT KY NHIEM VU (QUEST SYSTEM)", options, player);

        // Thoát nếu chọn tùy chọn cuối cùng hoặc nhấn ESC
        if (choice == -1 || choice == static_cast<int>(options.size() - 1)) {
            break;
        }

        // Xử lý nhận thưởng khi chọn nút nhận thưởng
        if (choice == static_cast<int>(options.size() - 2)) {
            bool rewarded = false;
            for (auto& q : questList) {
                if (!q.isCompleted() && q.getCurrentCount() >= q.getTargetCount()) {
                    q.setCompleted(true);
                    player.setGold(player.getGold() + q.getRewardGold());
                    player.gainExperience(q.getRewardExp());
                    rewarded = true;

                    std::string rewardMsg = "HOAN THANH: " + q.getTitle() + " (+" + 
                                            std::to_string(q.getRewardGold()) + " Gold, +" + 
                                            std::to_string(q.getRewardExp()) + " EXP)";
                    ConsoleUtils::showMenuCustom(rewardMsg, {"Xac nhan"}, player);
                }
            }
            if (!rewarded) {
                ConsoleUtils::showMenuCustom("Chua co nhiem vu nao dat dieu kien nhan thuong!", {"Quay lai"}, player);
            }
        }
    }
}

void QuestSystem::updateProgress(int questId, int amount) {
    for (auto& q : questList) {
        if (q.getId() == questId) {
            q.addProgress(amount);
            break;
        }
    }
}