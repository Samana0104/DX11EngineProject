#include "pch.h"
#include "Astar.h"
using namespace HBSoft;

float Astar::heuristic(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
{
    return std::abs(a->x - b->x) + std::abs(a->y - b->y);  // Manhattan distance
}

float Astar::distance(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
{
    return 1.0f;
}

// 이웃 노드 가져오기 함수 (8방향: 상, 하, 좌, 우, 대각선)
std::vector<std::shared_ptr<Node>> Astar::getNeighbors(
const std::shared_ptr<Node>& node, std::vector<std::vector<std::shared_ptr<Node>>>& grid)
{
    std::vector<std::shared_ptr<Node>> neighbors;
    int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};  // 상, 하, 좌, 우, 좌상, 좌하, 우상, 우하
    int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

    int rows = grid[0].size();
    int cols = grid.size();

    for (int i = 0; i < 8; ++i)
    {
        int nx = node->x + dx[i];
        int ny = node->y + dy[i];

        if (nx >= 0 && nx < cols && ny >= 0 && ny < rows)
        {
            auto neighbor = grid[nx][ny];
            if (!neighbor->isObstacle)
            {  // 장애물이 아닌 경우만 추가
                neighbors.push_back(neighbor);
            }
        }
    }

    return neighbors;
}

std::vector<std::shared_ptr<Node>> Astar::aStar(const std::shared_ptr<Node>&                     start,
                                                const std::shared_ptr<Node>&                     goal,
                                                std::vector<std::vector<std::shared_ptr<Node>>>& grid)
{
    auto compare = [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
    { return (a->gCost + a->hCost) > (b->gCost + b->hCost); };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(compare)>
    openSet(compare);

    start->gCost = 0;
    start->hCost = heuristic(start, goal);
    openSet.push(start);

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
            return path;
        }

        for (auto neighbor : getNeighbors(current, grid))
        {
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

// void Astar::aStarMain()
//{
//     //int                                             rows = 5;
//     //int                                             cols = 5;
//     //std::vector<std::vector<std::shared_ptr<Node>>> grid(rows,
//     std::vector<std::shared_ptr<Node>>(cols));
//
//     //// 2D 그리드 초기화
//     //for (int y = 0; y < rows; ++y)
//     //{
//     //    for (int x = 0; x < cols; ++x)
//     //    {
//     //        grid[y][x] = std::make_shared<Node>(x, y);  // make_shared 사용
//     //    }
//     //}
//
//     //// 장애물 설정 (예: 좌표 (2,2), (2,3), (3,2)을 장애물로 설정)
//     //grid[2][2]->isObstacle = true;
//     //grid[2][3]->isObstacle = true;
//     //grid[3][2]->isObstacle = true;
//
//     // 시작점과 목표점 설정
//     //auto start = grid[(int)(m_gardener1.GetmPos().x / 1.536f)]
//     //                 [(int)(m_gardener1.GetmPos().z / 1.536f)];  // 가드너 움직이는 거에 따른 좌표
//     //auto goal = grid[(int)(m_goose1.GetmPos().x / 1.536f)]
//     //                [(int)(m_goose1.GetmPos().z / 1.536f)];  // 거위 움직이는 거에 따른 좌표
//
//     //// A* 알고리즘 실행
//     //auto path = aStar(start, goal, grid);
//     // 결과 출력
//     if (!path.empty())
//     {
//         std::cout << "Path found:\n";
//         for (const auto& node : path)
//         {
//             std::cout << "(" << node->x << ", " << node->y << ") ";
//         }
//         std::cout << std::endl;
//     }
//     else
//     {
//         std::cout << "No path found." << std::endl;
//     }
// }
