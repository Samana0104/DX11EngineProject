#include "pch.h"
#include "Astar.h"
using namespace HBSoft;

int Astar::heuristic(const std::shared_ptr<Node> a, const std::shared_ptr<Node> b)
{
    return std::abs(abs(a->x) - abs(b->x)) + std::abs(abs(a->y) - abs(b->y));  // Manhattan distance
}

float Astar::distance(const std::shared_ptr<Node> a, const std::shared_ptr<Node> b)
{
    return 1.0f;
}

// 이웃 노드 가져오기 함수 (8방향: 상, 하, 좌, 우, 대각선)
std::vector<std::shared_ptr<Node>> Astar::getNeighbors(
const std::shared_ptr<Node> node, std::vector<std::vector<std::shared_ptr<Node>>>& grid)
{
    std::vector<std::shared_ptr<Node>> neighbors;
    int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};  // 상, 하, 좌, 우, 좌상, 좌하, 우상, 우하
    int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

    for (int i = 0; i < 8; ++i)
    {
        int nx = node->x + dx[i];
        int ny = node->y + dy[i];

        if (nx >= -GRID_OFFSET && ny >= -GRID_OFFSET && nx < GRID_OFFSET && ny < GRID_OFFSET)
        {
            auto neighbor = grid[nx + GRID_OFFSET][ny + GRID_OFFSET];
            if (!neighbor->isObstacle)
            {  // 장애물이 아닌 경우만 추가
                neighbors.push_back(neighbor);
            }
        }
    }

    return std::move(neighbors);
}

std::vector<std::shared_ptr<Node>> Astar::aStar(const std::shared_ptr<Node>                      start,
                                                const std::shared_ptr<Node>                      goal,
                                                std::vector<std::vector<std::shared_ptr<Node>>>& grid)
{
     std::vector<std::shared_ptr<Node>> initList;

    auto compare = [](const std::shared_ptr<Node> a, const std::shared_ptr<Node> b)
    { return (a->gCost + a->hCost) > (b->gCost + b->hCost); };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(compare)>
    openSet(compare);

    start->gCost = 0;
    start->hCost = heuristic(start, goal);
    openSet.push(start);

     initList.push_back(start);
     initList.push_back(goal);

    while (!openSet.empty())
    {
        auto current = openSet.top();
        openSet.pop();

        if (current == goal)
        {
            std::vector<std::shared_ptr<Node>> path;
            while (current)
            {
                path.push_back(current);
                current = current->parent;
            }

            std::reverse(path.begin(), path.end());

             for (auto initPath : initList)
            {
                 initPath->gCost  = 99999.f;
                 initPath->hCost  = 0.f;
                 initPath->parent = nullptr;
             }
            return std::move(path);
        }

        auto neighborSet = std::move(getNeighbors(current, grid));
        for (auto neighbor : neighborSet)
        {
             initList.push_back(neighbor);
            float tentativeGCost = current->gCost + distance(current, neighbor);

            if (tentativeGCost < neighbor->gCost)
            {
                neighbor->parent = current;
                neighbor->gCost  = tentativeGCost;
                neighbor->hCost  = heuristic(neighbor, goal);
                openSet.push(neighbor);
            }
        }
    }

    return {};
}