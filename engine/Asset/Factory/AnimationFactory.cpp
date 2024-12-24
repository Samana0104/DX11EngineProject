/*
author : ���Ѻ�
description : �ܺ� �ִϸ��̼��� �����ϴ� �ҽ�����

version: 1.0.0
date: 2024-12-23
*/
#include "pch.h"
#include "AnimationFactory.h"
using namespace HBSoft;

std::shared_ptr<AnimationClip> AnimationFactory::Create(const wstringV path)
{
    static SkmLoader               skmLoader;
    std::shared_ptr<AnimationClip> animation;

    animation = skmLoader.Load(path);

    if (animation == nullptr)
        assert(false);

    return animation;
}

bool AnimationFactory::IsAnimationFormat(const wstringV ext)
{
    if (ext.compare(L".skm") == 0)
        return true;

    return false;
}
