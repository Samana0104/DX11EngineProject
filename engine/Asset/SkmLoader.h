/*
author : 변한빛
description : skm(애니메이션) 파일 포맷의 import/export를 위한 클래스 헤더파일

version: 1.0.0
date: 2024-12-23
*/

#pragma once

#include "pch.h"
#include "AnimationClip.h"

namespace HBSoft
{
#define SKM_VERSION 100

    struct SKMFileHeader
    {
        UINT   version;  // 버전
        size_t aniNameSize;
        size_t numBornObj;
        int    startFrame;
        int    lastFrame;
        int    numFrame;

        // struct KeyFrame
        //{
        //     vec3 pos;
        //     quat rot;
        //     vec3 scale;
        // };

        // class AnimationClip
        //{
        // public:
        //     std::string m_aniName;
        //     int         m_startFrame;
        //     int         m_lastFrame;

        //    std::vector<std::vector<KeyFrame>> m_keyFrame;
        //};
    };

    class SkmLoader
    {
    private:
        std::ofstream m_outputAsciiFile;
        std::ofstream m_outputFile;
        std::ifstream m_inputFile;

    private:
        void WriteSKMHeader(SKMFileHeader& skmHeader, std::shared_ptr<AnimationClip> animation);
        void WriteSKMAsciiFile(SKMFileHeader& skmHeader, std::shared_ptr<AnimationClip> animation);
        void WriteSKMAsciiFileFromAnimation(std::shared_ptr<AnimationClip> animation);
        void WriteSKMFile(SKMFileHeader& skmHeader, std::shared_ptr<AnimationClip> animation);

    public:
        bool Export(std::shared_ptr<AnimationClip> animation, const wstringV filePath);
        std::shared_ptr<AnimationClip> Load(const wstringV filePath);
    };
}  // namespace HBSoft
