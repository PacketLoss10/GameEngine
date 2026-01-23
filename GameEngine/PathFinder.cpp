#include "PathFinder.h"
//#include "PathFinder.h"
//
//bool PathFinder::goalBlocked(const sf::Vector2f& target, CollisionArea* collision) const
//{
//	std::shared_lock lock(navBlocksMutex);
//	collision->set_position(target);
//	for (auto navBlock : navBlocks)
//		if (navBlock->isOverlapping(*collision))
//			return true;
//	return false;
//}
//
//std::vector<std::pair<sf::Vector2f, float>> PathFinder::validAdjecentNodes(const sf::Vector2f& position, CollisionArea* collision) const
//{
//	std::shared_lock lock(navBlocksMutex);
//	std::vector<std::pair<sf::Vector2f, float>> adjecents;
//	adjecents.reserve(8);
//	for (sf::Vector2f direction : directions)
//	{
//		sf::Vector2f adjecent = position + direction;
//		collision->set_position(adjecent);
//		bool blocked{ false };
//		for (auto navBlock : navBlocks)
//			if (navBlock->isOverlapping(*collision))
//			{
//				blocked = true;
//				break;
//			}
//		if (!blocked)
//			adjecents.emplace_back(adjecent, direction.length());
//	}
//	return adjecents;
//}
//
//PathFinder& PathFinder::instance()
//{
//	static PathFinder instance;
//	return instance;
//}
//
//void PathFinder::clear()
//{
//	navBlocks.clear();
//}
//
//void PathFinder::addNavBlock(NavBlock* navBlock)
//{
//	std::unique_lock lock(navBlocksMutex);
//	navBlocks.push_back(navBlock);
//}
//
//const std::vector<NavBlock*>& PathFinder::get_navBlocks() const
//{
//	std::shared_lock lock(navBlocksMutex);
//	return navBlocks;
//}
//
//std::optional<std::stack<sf::Vector2f>> PathFinder::findPath(const sf::Vector2f& start, const sf::Vector2f& targetPosition, CollisionArea* collision, float acceptance)
//{
//	int iterations = 0;
//	sf::Vector2f end = targetPosition;
//	if (goalBlocked(targetPosition, collision))
//	{
//		std::queue<sf::Vector2f> bfs;
//		std::unordered_set<sf::Vector2f> visited;
//		bfs.push(targetPosition);
//		visited.insert(targetPosition);
//		bool found = false;
//		while (!bfs.empty())
//		{
//			sf::Vector2f current{ bfs.front() };
//			bfs.pop();
//			for (const sf::Vector2f& dir : directions)
//			{
//				sf::Vector2f adj = current + dir;
//				if (visited.count(adj))
//					continue;
//				visited.insert(adj);
//				if (!goalBlocked(adj, collision))
//				{
//					end = adj;
//					found = true;
//					break;
//				}
//				bfs.push(adj);
//			}
//			if (found)
//				break;
//		}
//		if (!found)
//			return std::nullopt;
//	}
//	std::priority_queue<std::pair<float, sf::Vector2f>, std::vector<std::pair<float, sf::Vector2f>>, decltype(fcompare)> pq(fcompare);
//	std::unordered_map<sf::Vector2f, sf::Vector2f> prev;
//	std::unordered_map<sf::Vector2f, float> g;
//	std::unordered_map<sf::Vector2f, float> f;
//	g[start] = 0.f;
//	f[start] = manhattanHeuristic(start, end);
//	pq.emplace(f[start], start);
//	while (!pq.empty() && iterations < maxIterations)
//	{
//		iterations++;
//		sf::Vector2f current = pq.top().second;
//		pq.pop();
//		if (manhattanHeuristic(current, end) < acceptance)
//		{
//			std::stack<sf::Vector2f> path;
//			while (prev.count(current))
//			{
//				path.push(current);
//				current = prev[current];
//			}
//			path.push(start);
//			return path;
//		}
//		for (const auto& [adjacent, cost] : validAdjecentNodes(current, collision))
//		{
//			float tentativeG = g[current] + cost;
//			if (!g.count(adjacent) || tentativeG < g[adjacent])
//			{
//				prev[adjacent] = current;
//				g[adjacent] = tentativeG;
//				f[adjacent] = tentativeG + manhattanHeuristic(adjacent, end);
//				pq.emplace(f[adjacent], adjacent);
//			}
//		}
//	}
//	return std::nullopt;
//}
#include "iostream"

bool PathFinder::is_goal_blocked(const FVector& goal) const
{
	//WIP
	return false;
}

std::vector<std::pair<FVector, float>> PathFinder::valid_adjacent_nodes(const FVector& position) const
{
	//TEMP
	std::vector<std::pair<FVector, float>> adjecents;
	adjecents.reserve(8);
	for (const FVector& dir : directions)
	{
		FVector adjecent = position + dir;
		adjecents.emplace_back(adjecent, dir.size());
	}
	return adjecents;
}

PathFinder& PathFinder::instance()
{
	static PathFinder instance;
	return instance;
}

//std::optional<std::stack<FVector>> PathFinder::find_path(const FVector& start, const FVector& end, float acceptance)
//{
//	std::cout << "PATHFINDING STARTED" << std::endl;
//	int iterations = 0;
//
//	std::priority_queue<std::pair<float, FVector>, std::vector<std::pair<float, FVector>>, decltype(fCompare)> pq(fCompare);
//	std::unordered_map<FVector, FVector> prev;
//	std::unordered_map<FVector, float> g;
//	std::unordered_map<FVector, float> f;
//
//	g[start] = 0.f;
//	f[start] = euclidean(start, end);
//	pq.emplace(f[start], start);
//
//	while (!pq.empty() && iterations < maxIterations)
//	{
//		iterations++;
//		FVector current = pq.top().second;
//		pq.pop();
//		std::cout << euclidean(current, end) << std::endl;
//		if (euclidean(current, end) < acceptance)
//		{
//			std::stack<FVector> path;
//			while (prev.count(current))
//			{
//				path.push(current);
//				current = prev[current];
//			}
//
//			path.push(start);
//
//			std::cout << "PATH FOUND" << std::endl;
//			return path;
//		}
//
//		for (const auto& [adjacent, cost] : valid_adjacent_nodes(current))
//		{
//			float tentativeG = g[current] + cost;
//			if (!g.count(adjacent) || tentativeG < g[adjacent])
//			{
//				prev[adjacent] = current;
//				g[adjacent] = tentativeG;
//				f[adjacent] = tentativeG + euclidean(adjacent, end);
//				pq.emplace(f[adjacent], adjacent);
//			}
//		}
//	}
//
//	std::cout << "NO PATH FOUND" << std::endl;
//	return std::nullopt;
//}

std::optional<std::stack<FVector>> PathFinder::find_path(const FVector& start, const FVector& end, float acceptance)
{
    std::cout << "PATHFINDING STARTED" << std::endl;

    std::priority_queue<
        std::pair<float, FVector>,
        std::vector<std::pair<float, FVector>>,
        decltype(fCompare)> openSet(fCompare);

    std::unordered_map<FVector, FVector> cameFrom;
    std::unordered_map<FVector, float> gScore;

    // Snap start and end to the step grid
    auto snapToGrid = [this](const FVector& v) {
        return FVector(
            std::round(v.x / stepSize) * stepSize,
            std::round(v.y / stepSize) * stepSize
        );
        };

    FVector startGrid = snapToGrid(start);
    FVector endGrid = snapToGrid(end);

    gScore[startGrid] = 0.f;
    float fScoreStart = euclidean(startGrid, endGrid);
    openSet.emplace(fScoreStart, startGrid);

    int iterations = 0;

    while (!openSet.empty() && iterations < maxIterations)
    {
        iterations++;
        FVector current = openSet.top().second;
        openSet.pop();

        // Goal check
        if (euclidean(current, endGrid) <= acceptance)
        {
            std::stack<FVector> path;
            while (cameFrom.count(current))
            {
                path.push(current);
                current = cameFrom[current];
            }
            path.push(startGrid);
            std::cout << "PATH FOUND" << std::endl;
            return path;
        }

        // Generate neighbors on the step grid
        for (const FVector& dir : directions)
        {
            FVector neighbor = current + dir;
            neighbor = snapToGrid(neighbor);

            float tentativeG = gScore[current] + dir.size();

            if (!gScore.count(neighbor) || tentativeG < gScore[neighbor])
            {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeG;
                float fScore = tentativeG + euclidean(neighbor, endGrid);
                openSet.emplace(fScore, neighbor);
            }
        }
    }

    std::cout << "NO PATH FOUND" << std::endl;
    return std::nullopt;
}

float PathFinder::get_stepSize() const
{
	return stepSize;
}