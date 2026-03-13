#pragma once

#include "queue"
#include "stack"
#include "unordered_map"
#include "unordered_set"
#include "shared_mutex"
#include "Transform.h"

class NavMesh;

#define PATHFINDER PathFinder::instance()

namespace std 
{
	template<>
	struct hash<Vector2> { size_t operator()(const Vector2& key) const noexcept { return std::hash<float>()(key.x) ^ (std::hash<float>()(key.y) << 1); } };
}

struct PathFinderHeuristic
{
	virtual float invoke(const Vector2& A, const Vector2& B) const = 0;
};

struct EuclideanHeuristic: public PathFinderHeuristic
{
	float invoke(const Vector2& A, const Vector2& B) const override
	{
		return (A - B).size();
	}
};

struct ManhattanHeuristic :public PathFinderHeuristic
{
	float  invoke(const Vector2& A, const Vector2& B) const override
	{
		return std::abs(B.x - A.x) + std::abs(B.y - A.y);
	}
};

struct ChebyshevHeuristic :public PathFinderHeuristic
{
	float invoke(const Vector2& A, const Vector2& B) const override
	{
		return std::max(std::abs(B.x - A.x), std::abs(B.y - A.y));
	}
};

class PathFinder
{
private:
	const float stepSize = 20.f;
	const Vector2 directions[8] = { Vector2(stepSize, stepSize), Vector2(-stepSize, stepSize), Vector2(stepSize, -stepSize), Vector2(-stepSize, -stepSize), Vector2(stepSize, 0.f), Vector2(-stepSize, 0.f), Vector2(0.f, stepSize), Vector2(0.f, -stepSize) };
	inline static auto fCompare = [](const std::pair<float, Vector2>& a, const std::pair<float, Vector2>& b) { return a.first > b.first; };
	int maxIterations = 10000;

	PathFinder() = default;
	PathFinder(const PathFinder&) = delete;
	PathFinder& operator=(const PathFinder&) = delete;

	std::vector<std::pair<Vector2, float>> valid_adjacent_nodes(const Vector2& position, const NavMesh& navmesh) const;
public:
	static PathFinder& instance();
	std::optional<std::stack<Vector2>> find_path(const Vector2& start, const Vector2& end, const NavMesh& navmesh, const PathFinderHeuristic& heuristic);
	float get_stepSize() const;
};