#pragma once
#include "AbstractImageAnalyzer.h"

#include "AsstBattleDef.h"

namespace asst
{
    class BattleImageAnalyzer : public AbstractImageAnalyzer
    {
    public:
        enum Target          // 需要识别的目标
        {
            None = 0,
            HP = 1,          // 剩余生命值
            Home = 2,        // 蓝色的家门
            Oper = 4,        // 下方的干员信息
            Skill = 8,       // cd 转好了可以使用的技能
            Kills = 16,      // 击杀数
            Cost = 32,       // 费用
            Vacancies = 64,  // 剩余可部署干员数
            // 肉鸽模式需要用到的识别
            Roguelike = Home | HP | Oper | Skill
        };
    public:
        using AbstractImageAnalyzer::AbstractImageAnalyzer;
        virtual ~BattleImageAnalyzer() = default;

        bool set_target(int target);
        virtual bool analyze() override;

        virtual const std::vector<BattleRealTimeOper>& get_opers() const noexcept;
        virtual const std::vector<Rect>& get_homes() const noexcept;

        const std::vector<Rect>& get_ready_skills() const noexcept;
        int get_hp() const noexcept;
        int get_kills() const noexcept;

        void clear() noexcept;

    protected:
        bool opers_analyze();   // 识别干员
        BattleRole oper_role_analyze(const Rect& roi);
        bool oper_cooling_analyze(const Rect& roi);
        int oper_cost_analyze(const Rect& roi);
        bool oper_available_analyze(const Rect& roi);

        bool home_analyze();    // 识别蓝色的家门
        bool skill_analyze();   // 识别技能是否可用
        bool hp_analyze();      // 识别剩余生命值
        bool kills_analyze();   // 识别击杀数
        bool cost_analyze();    // 识别费用
        bool vacancies_analyze();// 识别剩余可部署人数

        int m_target = 0;                           // 待识别的目标

        /* 识别结果缓存 */
        std::vector<BattleRealTimeOper> m_opers;    // 下方干员信息
        std::vector<Rect> m_homes;                  // 蓝色的家门位置
        std::vector<Rect> m_ready_skills;           // 可以释放的技能（Rect实际是干员的位置）
        int m_hp = 0;                               // 剩余生命值
        int m_kills = 0;                            // 击杀数
        int m_cost = 0;                             // 部署费用
    };
}
