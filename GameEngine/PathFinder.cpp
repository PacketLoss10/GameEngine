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

std::optional<std::stack<FVector>> PathFinder::find_path(const FVector& start, const FVector& end, float acceptance)
{
	int iterations = 0;
	FVector target = end;
	if (is_goal_blocked(end))
	{
		std::queue<FVector> bfs;
		std::unordered_set<FVector> visited;
		bfs.push(end);
		visited.insert(end);
		bool found = false;

		while (!bfs.empty())
		{
			FVector current = bfs.front();
			bfs.pop();
			for (const FVector& dir : directions)
			{
				FVector adj = current + dir;
				if (visited.count(adj))
					continue;
				visited.insert(adj);
				if (!is_goal_blocked(adj))
				{
					target = adj;
					found = true;
					break;
				}
				bfs.push(adj);
			}

			if (found)
				break;
		}

		if (!found)
			return std::nullopt;
	}

	std::priority_queue<std::pair<float, FVector>, std::vector<std::pair<float, FVector>>, decltype(fCompare)> pq(fCompare);
	std::unordered_map<FVector, FVector> prev;
	std::unordered_map<FVector, float> g;
	std::unordered_map<FVector, float> f;

	g[start] = 0.f;
	f[start] = manhattan(start, target);
	pq.emplace(f[start], start);

	while (!pq.empty() && iterations < maxIterations)
	{
		iterations++;
		FVector current = pq.top().second;
		pq.pop();

		if (manhattan(current, target) < acceptance)
		{
			std::stack<FVector> path;
			while (prev.count(current))
			{
				path.push(current);
				current = prev[current];
			}

			path.push(start);
			return path;
		}

		for (const auto& [adjacent, cost] : valid_adjacent_nodes(current))
		{
			float tentativeG = g[current] + cost;
			if (!g.count(adjacent) || tentativeG < g[adjacent])
			{
				prev[adjacent] = current;
				g[adjacent] = tentativeG;
				f[adjacent] = tentativeG + manhattan(adjacent, target);
				pq.emplace(f[adjacent], adjacent);
			}
		}
	}

	return std::nullopt;
}

float PathFinder::get_stepSize() const
{
	return stepSize;
}
