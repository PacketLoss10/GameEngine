#pragma once

#include <vector>
#include <mutex>
#include <queue>
#include <SFML/Network.hpp>

class GameMessage;

#define GAME_SERVER GameServer::instance()

class GameServer
{
private:
	GameServer() = default;
	GameServer(const GameServer&) = delete;
	GameServer& operator==(const GameServer&) = delete;

	unsigned short TCP_PORT = 4300;
	unsigned short UDP_PORT = 4300;
	
	int maxClients = 4;
	std::vector<sf::TcpSocket*> clients;
	std::mutex clientsMutex;

	std::queue<GameMessage*> messageQueue;
	std::mutex messageQueueMutex;

	void handle_client(sf::TcpSocket* client);
	void broadcast_message(char* message, size_t size, sf::TcpSocket* sender);

	void send_message_to_client(sf::TcpSocket* client, const GameMessage* message);
public:
	static GameServer& instance();
	void tcp_start();
	void udp_start();
	void send_message(const GameMessage& message);
};