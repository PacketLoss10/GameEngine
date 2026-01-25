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
	struct hash<FVector> { size_t operator()(const FVector& key) const noexcept { return std::hash<float>()(key.x) ^ (std::hash<float>()(key.y) << 1); } };
}

struct PathFinderHeuristic
{
	virtual float invoke(const FVector& A, const FVector& B) const = 0;
};

struct EuclideanHeuristic: public PathFinderHeuristic
{
	float invoke(const FVector& A, const FVector& B) const override
	{
		return (A - B).size();
	}
};

struct ManhattanHeuristic :public PathFinderHeuristic
{
	float  invoke(const FVector& A, const FVector& B) const override
	{
		return std::abs(B.x - A.x) + std::abs(B.y - A.y);
	}
};

struct ChebyshevHeuristic :public PathFinderHeuristic
{
	float invoke(const FVector& A, const FVector& B) const override
	{
		return std::max(std::abs(B.x - A.x), std::abs(B.y - A.y));
	}
};

class PathFinder
{
private:
	const float stepSize = 20.f;
	const FVector directions[8] = { FVector(stepSize, stepSize), FVector(-stepSize, stepSize), FVector(stepSize, -stepSize), FVector(-stepSize, -stepSize), FVector(stepSize, 0.f), FVector(-stepSize, 0.f), FVector(0.f, stepSize), FVector(0.f, -stepSize) };
	inline static auto fCompare = [](const std::pair<float, FVector>& a, const std::pair<float, FVector>& b) { return a.first > b.first; };
	int maxIterations = 10000;

	PathFinder() = default;
	PathFinder(const PathFinder&) = delete;
	PathFinder& operator=(const PathFinder&) = delete;

	std::vector<std::pair<FVector, float>> valid_adjacent_nodes(const FVector& position, const NavMesh& navmesh) const;
public:
	static PathFinder& instance();
	std::optional<std::stack<FVector>> find_path(const FVector& start, const FVector& end, const NavMesh& navmesh, const PathFinderHeuristic& heuristic);
	float get_stepSize() const;
};