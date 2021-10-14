﻿#pragma once
#include "AbstractImageAnalyzer.h"

namespace asst {
    class MultiMatchImageAnalyzer : public AbstractImageAnalyzer
    {
    public:
        using AbstractImageAnalyzer::AbstractImageAnalyzer;
        MultiMatchImageAnalyzer(const cv::Mat& image, const Rect& roi, std::string templ_name, double templ_thres);
        virtual ~MultiMatchImageAnalyzer() = default;

        virtual bool analyze() override;

        void sort_result();
        void set_templ_name(std::string templ_name) noexcept {
            m_templ_name = std::move(templ_name);
        }
        void set_threshold(double templ_thres) noexcept {
            m_templ_thres = templ_thres;
        }
        const std::vector<MatchRect>& get_result() const noexcept {
            return m_result;
        }

    protected:
        virtual bool multi_match_templ(const cv::Mat& templ);

        std::string m_templ_name;
        double m_templ_thres = 0.0;
        std::vector<MatchRect> m_result;
    };
}
