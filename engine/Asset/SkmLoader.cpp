/*
author : 변한빛
description : skm(애니메이션) 파일 포맷의 import/export를 위한 클래스 소스파일

version: 1.0.0
date: 2024-12-23
*/

#include "pch.h"
#include "SkmLoader.h"
using namespace HBSoft;

void SkmLoader::WriteSKMHeader(SKMFileHeader& skmHeader, std::shared_ptr<AnimationClip> animation)
{
    skmHeader.version     = SKM_VERSION;
    skmHeader.aniNameSize = animation->m_aniName.size();
    skmHeader.numBornObj  = animation->m_keyFrame.size();
    skmHeader.startFrame  = animation->m_startFrame;
    skmHeader.lastFrame   = animation->m_lastFrame;
    skmHeader.numFrame    = animation->m_numFrame;
}

void SkmLoader::WriteSKMAsciiFile(SKMFileHeader& skmHeader, std::shared_ptr<AnimationClip> animation)
{
    m_outputAsciiFile << "< SKM HEADER >" << std::endl;
    m_outputAsciiFile << "skm version: " << skmHeader.version << std::endl;
    m_outputAsciiFile << "animation name : " << animation->m_aniName << std::endl;
    m_outputAsciiFile << "start frame : " << animation->m_startFrame << std::endl;
    m_outputAsciiFile << "last frame : " << animation->m_lastFrame << std::endl;
    m_outputAsciiFile << "frame count : " << animation->m_numFrame << std::endl;
    m_outputAsciiFile << "born obj count : " << animation->m_keyFrame.size() << std::endl;

    WriteSKMAsciiFileFromAnimation(animation);
}

void SkmLoader::WriteSKMAsciiFileFromAnimation(std::shared_ptr<AnimationClip> animation)
{
    m_outputAsciiFile << std::endl << std::endl;
    m_outputAsciiFile << "-----------------------------------------------";
    m_outputAsciiFile << std::endl << std::endl;

    m_outputAsciiFile << std::endl;

    for (size_t j = 0; j < animation->m_keyFrame.size(); j++)
    {
        m_outputAsciiFile << "keyframe " << std::endl;
        m_outputAsciiFile << "born index : " << j << std::endl;
        for (size_t k = 0; k < animation->m_keyFrame[j].size(); k++)
        {
            KeyFrame key = animation->m_keyFrame[j][k];

            m_outputAsciiFile << " [Pos] : " << key.pos.x << ", " << key.pos.y << ", " << key.pos.z;
            m_outputAsciiFile << " [Rotation(quat wxyz)] : " << key.rot.w << ", " << key.rot.x << ", "
                              << key.rot.y << ", " << key.rot.z;
            m_outputAsciiFile << " [Scale] : " << key.scale.x << ", " << key.scale.y << ", "
                              << key.scale.z;
            m_outputAsciiFile << std::endl;
        }

        m_outputAsciiFile << std::endl;
    }
    m_outputAsciiFile << std::endl;
}

void SkmLoader::WriteSKMFile(SKMFileHeader& skmHeader, std::shared_ptr<AnimationClip> animation)
{
    m_outputFile.write(reinterpret_cast<const char*>(&skmHeader), sizeof(SKMFileHeader));
    m_outputFile.write(reinterpret_cast<const char*>(&animation->m_aniName.at(0)),
                       sizeof(char) * animation->m_aniName.size());

    for (size_t j = 0; j < animation->m_keyFrame.size(); j++)
        m_outputFile.write(reinterpret_cast<const char*>(&animation->m_keyFrame[j].at(0)),
                           sizeof(KeyFrame) * skmHeader.numFrame);
}

bool SkmLoader::Export(std::shared_ptr<AnimationClip> animation, const wstringV filePath)
{
    auto [fileDir, fileName] = HBSoft::GetFileDirAndName(filePath);

    std::string           folderPath = HBSoft::ToMultiByte(fileDir + fileName + L"\\");
    std::filesystem::path path(folderPath);

    if (!std::filesystem::exists(path.parent_path()))
        std::filesystem::create_directories(path.parent_path());

    std::string skmAsciiFormat = folderPath + animation->m_aniName + ".txt";
    std::string skmFormat      = folderPath + animation->m_aniName + ".skm";

    SKMFileHeader fileHeader;

    m_outputAsciiFile.open(skmAsciiFormat.c_str(), std::ios::out);
    m_outputFile.open(skmFormat.c_str(), std::ios::binary);

    if (!m_outputAsciiFile.is_open())
    {
        MessageBoxA(nullptr, "fbx파일 -> skm파일 변환 오류[txt 생성 불가]", "Converter error", MB_OK);
        return false;
    }

    if (!m_outputFile.is_open())
    {
        MessageBoxA(nullptr, "fbx파일 -> skm파일 변환 오류[skm 생성 불가]", "Converter error", MB_OK);
        return false;
    }

    WriteSKMHeader(fileHeader, animation);
    WriteSKMAsciiFile(fileHeader, animation);
    WriteSKMFile(fileHeader, animation);
    m_outputAsciiFile.close();
    m_outputFile.close();
    return false;
}

std::shared_ptr<AnimationClip> SkmLoader::Load(const wstringV filePath)
{
    SKMFileHeader skmHeader;

    std::string                    fileDir   = HBSoft::ToMultiByte(filePath);
    std::shared_ptr<AnimationClip> animation = std::make_shared<AnimationClip>();

    m_inputFile.open(fileDir, std::ios::in | std::ios::binary);
    if (!m_inputFile.is_open())
    {
        MessageBoxA(nullptr, "skm 파일 로드 오류", "load error", MB_OK);
        return nullptr;
    }

    m_inputFile.read(reinterpret_cast<char*>(&skmHeader), sizeof(SKMFileHeader));

    if (m_inputFile.fail())
    {
        MessageBoxA(nullptr, "skm파일 로드 오류[헤더를 읽을 수 없음]", "load error", MB_OK);
        return nullptr;
    }

    if (skmHeader.version != SKM_VERSION)
    {
        MessageBoxA(nullptr, "skm파일 로드 오류[버전 불일치 최신 skm로 컨버터]", "load error", MB_OK);
        return nullptr;
    }
    animation->m_startFrame = skmHeader.startFrame;
    animation->m_lastFrame  = skmHeader.lastFrame;
    animation->m_numFrame   = skmHeader.numFrame;

    animation->m_aniName.resize(skmHeader.aniNameSize);
    m_inputFile.read(reinterpret_cast<char*>(&animation->m_aniName.at(0)),
                     sizeof(char) * animation->m_aniName.size());

    animation->m_keyFrame.resize(skmHeader.numBornObj);

    for (size_t j = 0; j < skmHeader.numBornObj; j++)
    {
        animation->m_keyFrame[j].resize(skmHeader.numFrame);
        m_inputFile.read(reinterpret_cast<char*>(&animation->m_keyFrame[j].at(0)),
                         sizeof(KeyFrame) * skmHeader.numFrame);
    }

    m_inputFile.close();
    return animation;
}
