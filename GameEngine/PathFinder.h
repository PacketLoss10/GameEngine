#pragma once

#include "queue"
#include "stack"
#include "unordered_map"
#include "unordered_set"
#include "shared_mutex"
#include "NavBlock.h"

#define PATHFINDER PathFinder::instance()

namespace std 
{
	template<>
	struct hash<FVector> { size_t operator()(const FVector& key) const noexcept { return std::hash<float>()(key.x) ^ (std::hash<float>()(key.y) << 1); } };
}

//class PathFinder 
//{
//private:
//	PathFinder() = default;
//	PathFinder(const PathFinder&) = delete;
//	PathFinder& operator=(const PathFinder&) = delete;
//	mutable std::shared_mutex navBlocksMutex;
//	std::vector<NavBlock*> navBlocks;
//	const float stepSize{ 20.f };
//	int maxIterations{ 10000 };
//	const sf::Vector2f directions[8]{ {stepSize,stepSize},{-stepSize,stepSize},{stepSize,-stepSize},{-stepSize,-stepSize},{stepSize,0.f},{-stepSize,0.f},{0.f,stepSize},{0.f,-stepSize} };
//	inline static auto fcompare{ [](const std::pair<float, sf::Vector2f>& p1, const std::pair<float, sf::Vector2f>& p2) {return p1.first > p2.first; } };
//	inline static auto euclideanHeuristic{ [](const sf::Vector2f& v1,const sf::Vector2f& v2) { return (v1 - v2).length(); } };
//	inline static auto manhattanHeuristic{ [](const sf::Vector2f& v1,const sf::Vector2f& v2) { return std::abs(v2.x - v1.x) + std::abs(v2.y - v1.y); } };
//	inline static auto chebyshevHeuristic{ [](const sf::Vector2f& v1,const sf::Vector2f& v2) { return std::max(std::abs(v2.x - v1.x), std::abs(v2.y - v1.y)); } };
//	bool goalBlocked(const sf::Vector2f& target, CollisionArea* collision) const;
//	std::vector<std::pair<sf::Vector2f, float>> validAdjecentNodes(const sf::Vector2f& position, CollisionArea* collision) const;
//public:
//	static PathFinder& instance();
//	void clear();
//	void addNavBlock(NavBlock* navBlock);
//	const std::vector<NavBlock*>& get_navBlocks() const;
//	std::optional<std::stack<sf::Vector2f>> findPath(const sf::Vector2f& start, const sf::Vector2f& targetPosition, CollisionArea* collision, float acceptance);
//	float get_stepSize() const { return stepSize; }
//};

class PathFinder
{
private:
	std::vector<NavBlock> navBlocks;
	mutable std::shared_mutex navBlocksMutex;
	const float stepSize = 20.f;
	int maxIterations = 10000;
	const FVector directions[8] = { FVector(stepSize, stepSize), FVector(-stepSize, stepSize), FVector(stepSize, -stepSize), FVector(-stepSize, -stepSize), FVector(stepSize, 0.f), FVector(-stepSize, 0.f), FVector(0.f, stepSize), FVector(0.f, -stepSize) };
	inline static auto fCompare = [](const std::pair<float, FVector>& a, const std::pair<float, FVector>& b) {return a.first > b.first; };
	inline static auto euclidean = [](const FVector& a, const FVector& b) {return (a - b).size(); };
	inline static auto manhattan = [](const FVector& a, const FVector& b) {return std::abs(b.x - a.x) + std::abs(b.y - a.y); };
	inline static auto chebyshev = [](const FVector& a, const FVector& b) {return std::max(std::abs(b.x - a.x), std::abs(b.y - a.y)); };

	PathFinder() = default;
	PathFinder(const PathFinder&) = delete;
	PathFinder& operator=(const PathFinder&) = delete;

	bool is_goal_blocked(const FVector& goal) const;
	std::vector<std::pair<FVector, float>> valid_adjacent_nodes(const FVector& position) const;
public:
	static PathFinder& instance();
	std::optional<std::stack<FVector>> find_path(const FVector& start, const FVector& end, float acceptance = 20.f);
	float get_stepSize() const;
};