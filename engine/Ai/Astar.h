/*
author : ������
description : ���̽�Ÿ ��

version: 1.0.4
date: 2024-12-12
*/

#pragma once

#include "pch.h"
#include "Core.h"
#include "Mesh/Grid.h"

  // ���� ��ǥ�� �����ϱ� ���� ������
#define GRID_SIZE   (40)  // (-50 ~ 50 ���� ����)

#define INFINITY_DISTANCE (9999)

namespace HBSoft
{
    struct Node
    {
        int                   x, y;
        float                 gCost, hCost;
        std::shared_ptr<Node> parent;
        bool                  isObstacle;  // ��ֹ� ����

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

        void  InitGrid();
        float heuristic(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);
        float distance(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);
        std::vector<std::shared_ptr<Node>> getNeighbors(
        const std::shared_ptr<Node>& node, std::vector<std::vector<std::shared_ptr<Node>>>& grid);
        std::vector<std::shared_ptr<Node>> aStar(const std::shared_ptr<Node>&                     start,
                                                 const std::shared_ptr<Node>&                     goal,
                                                 std::vector<std::vector<std::shared_ptr<Node>>>& grid);

        int GRID_OFFSET = 20;
        /*  void aStarMain();*/


        /*   int rows = 5;
           int cols = 5;*/
    };

}  // namespace HBSoft