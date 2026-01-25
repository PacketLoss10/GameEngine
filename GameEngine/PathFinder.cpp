#include "PathFinder.h"
#include "NavMesh.h"

std::vector<std::pair<FVector, float>> PathFinder::valid_adjacent_nodes(const FVector& position, const NavMesh& navmesh) const
{
	std::vector<std::pair<FVector, float>> adjacents;
	adjacents.reserve(8);

	for (const FVector& dir : directions)
	{
		FVector adjacent = position + dir;
		if (navmesh.contains_point(adjacent))
		{
			adjacents.emplace_back(adjacent, dir.size());
		}
	}

	return adjacents;
}

PathFinder& PathFinder::instance()
{
	static PathFinder instance;
	return instance;
}

std::optional<std::stack<FVector>> PathFinder::find_path(const FVector& start, const FVector& end, const NavMesh& navmesh, const PathFinderHeuristic& heuristic)
{
	if (navmesh.empty())
	{
		return std::nullopt;
	}

	int iterations = 0;
	FVector target = end;

	if (!navmesh.contains_point(end))
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
				FVector adjacent = current + dir;
				if (visited.count(adjacent))
					continue;
				visited.insert(adjacent);
				if (navmesh.contains_point(adjacent))
				{
					target = adjacent;
					found = true;
					break;
				}
				bfs.push(adjacent);
			}
			if (found)
			{
				break;
			}
		}
		if (!found)
		{
			return std::nullopt;
		}
	}

	std::priority_queue<std::pair<float, FVector>, std::vector<std::pair<float, FVector>>, decltype(fCompare)> pq(fCompare);
	std::unordered_set<FVector> visited;
	std::unordered_map<FVector, FVector> prev;
	std::unordered_map<FVector, float> g;
	std::unordered_map<FVector, float> f;

	g[start] = 0.f;
	f[start] = heuristic.invoke(start, target);
	pq.emplace(f[start], start);

	while (!pq.empty() && iterations < maxIterations)
	{
		iterations++;

		FVector current = pq.top().second;
		pq.pop();

		if (visited.count(current))
			continue;
		visited.insert(current);

		if ((current - target).size_squared() <= stepSize * stepSize)
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

		for (const auto& [adjacent, cost] : valid_adjacent_nodes(current, navmesh))
		{
			if (visited.count(adjacent)) continue;
			float tentativeG = g[current] + cost;
			if (!g.count(adjacent) || tentativeG < g[adjacent])
			{
				prev[adjacent] = current;
				g[adjacent] = tentativeG;
				f[adjacent] = tentativeG + heuristic.invoke(adjacent, target);
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