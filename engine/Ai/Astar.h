/*
author : 정찬빈
description : 에이스타 갱

version: 1.0.4
date: 2024-12-12
*/

#pragma once

#include "pch.h"
#include "Core.h"
#include "Mesh/Grid.h"

// 음수 좌표를 보정하기 위한 오프셋
#define GRID_SIZE (40)  // (-50 ~ 50 범위 지원)

#define INFINITY_DISTANCE (9999)

namespace HBSoft
{
    struct Node
    {
        int                   x, y;
        float                 gCost, hCost;
        std::shared_ptr<Node> parent;
        bool                  isObstacle;  // 장애물 여부

        Node(int x, int y)
            : x(x),
              y(y),
              gCost(std::numeric_limits<float>::max()),
              hCost(0),
              isObstacle(false),
              parent(nullptr)
        {}

    public:
        bool operator>(const Node& other) const { return (gCost + hCost) > (other.gCost + other.hCost); }

        int GetLocationX() const { return x; }

        int GetLocationY() const { return y; }
    };

    class Astar
    {
    public:
        Astar()  = default;
        ~Astar() = default;

        std::vector<std::vector<std::shared_ptr<Node>>> InitGrid();
        float heuristic(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);
        float distance(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);
        std::vector<std::shared_ptr<Node>> getNeighbors(
        const std::shared_ptr<Node>& node, std::vector<std::vector<std::shared_ptr<Node>>>& grid);
        std::vector<std::shared_ptr<Node>> aStar(const std::shared_ptr<Node>&                     start,
                                                 const std::shared_ptr<Node>&                     goal,
                                                 std::vector<std::vector<std::shared_ptr<Node>>>& grid);


        float gridLength = 61.44f;
        int   gridNum    = 40;

        float GetGridLength();
        int   GetGridNum();

        int GRID_OFFSET = 20;

        int rows = 20;
        int cols = 20;
        /*  void aStarMain();*/


        /*   int rows = 5;
           int cols = 5;*/
    };

}  // namespace HBSoft