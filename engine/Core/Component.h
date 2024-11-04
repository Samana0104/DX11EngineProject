#pragma once
#include "pch.h"

namespace HBSoft
{
    class Composite
    {
    protected:
        virtual void Init()    = 0;
        virtual void Release() = 0;
        virtual void Update()  = 0;
        virtual void Render()  = 0;
        virtual void Clone()   = 0;
    };
}  // namespace HBSoft