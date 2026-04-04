#include "GameServer.h"
#include "GameMessage.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <thread>

void GameServer::tcp_start()
{
	sf::TcpListener listener;
	sf::Socket::Status status = listener.listen(TCP_PORT);

	if (status != sf::Socket::Status::Done)
	{
		std::cerr << "Error binding listener to port" << std::endl;
		return;
	}
	std::cout << "TCP Server is listening to port " << TCP_PORT << ", waiting for connections..." << std::endl;

	while (true)
	{
		sf::TcpSocket* client = new sf::TcpSocket;
		status = listener.accept(*client);
		if (status != sf::Socket::Status::Done)
		{
			delete client;
		}
		else
		{
			std::lock_guard<std::mutex> lock(clientsMutex);
			clients.push_back(client);

			auto clientAddress = client->getRemoteAddress();
			if (clientAddress.has_value())
			{
				std::cout << "Client connected: " << clientAddress->toString() << std::endl;
			}
			else
			{
				std::cout << "Client connected: [unknown address]" << std::endl;
			}
			std::thread(&GameServer::handle_client, this, client).detach();
		}
	}
}

void GameServer::udp_start()
{
	sf::UdpSocket socket;
	sf::Socket::Status status = socket.bind(UDP_PORT);

	if (status != sf::Socket::Status::Done)
	{
		std::cerr << "Error binding socket to port " << UDP_PORT << std::endl;
		return;
	}
	std::cout << "UDP Server started on port " << UDP_PORT << std::endl;

	while (true)
	{
		char data[1024];
		std::size_t received = 0;
		std::optional<sf::IpAddress> sender;
		unsigned short senderPort;

		status = socket.receive(data, sizeof(data), received, sender, senderPort);
		if (status != sf::Socket::Status::Done)
		{
			std::cerr << "Error receiving data" << std::endl;
			continue;
		}
		if (sender.has_value())
		{
			std::cout << "Received: " << data << " from " << sender->toString() << ": " << senderPort << std::endl;
		}

		if (sender)
		{
			sf::Socket::Status status = socket.send(data, received, *sender, senderPort);
			if (status != sf::Socket::Status::Done)
			{
				std::cerr << "Error sending data" << std::endl;
			}
		}
	}

	socket.unbind();
	std::cout << "Server stopped" << std::endl;
}

void GameServer::send_message(const GameMessage& message)
{

}

uint32_t get_message_length(sf::TcpSocket* client)
{
	uint32_t length = 0;
	size_t received = 0;

	if (client->receive(reinterpret_cast<char*>(&length), sizeof(length), received) != sf::Socket::Status::Done)
	{
		std::cerr << "Error retreiving incoming message byte size from cleint" << std::endl;
		return 0;
	}

	length = ntohl(length);
	return length;
}

void GameServer::handle_client(sf::TcpSocket* client)
{
	while (true)
	{
		uint32_t length = get_message_length(client);
		size_t received = 0;
		ByteBuffer buffer(length);

		if (client->receive(buffer.data(), length, received) != sf::Socket::Status::Done)
		{
			std::cerr << "Error retreiving incoming message from client" << std::endl;
			break;
		}

		ByteArray ba(buffer);

		GameMessage* receivedMessage = GameMessage::decode(ba);
		if (!receivedMessage)
			continue;

		receivedMessage->execute();

		//std::lock_guard<std::mutex> lock(messageQueueMutex);
		//messageQueue.push(receivedMessage);
	}

	std::lock_guard<std::mutex> lock(clientsMutex);
	clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
	delete client;
}

void GameServer::broadcast_message(char* message, size_t size, sf::TcpSocket* sender)
{
	std::lock_guard<std::mutex> lock(clientsMutex);
	for (auto& client : clients)
	{
		if (client->send(message, size + 1) != sf::Socket::Status::Done)
		{
			std::cerr << "Error sending message to client" << std::endl;
		}
	}
}

void GameServer::send_message_to_client(sf::TcpSocket* client, const GameMessage* message)
{
	ByteArray ba = message->serialize();
	uint32_t length = static_cast<uint32_t>(ba.size());
	uint32_t networkLength = htonl(length);

	ByteBuffer sendBuffer(sizeof(networkLength) + length);
	std::memcpy(sendBuffer.data(), &networkLength, sizeof(networkLength));
	std::memcpy(sendBuffer.data() + sizeof(networkLength), ba.data(), length);

	if (client->send(sendBuffer.data(), sendBuffer.size()) != sf::Socket::Status::Done)
	{
		std::cerr << "Error sending message to client" << std::endl;
		return;
	}
}

int main()
{
	std::thread udp_thread(&GameServer::udp_start, &GAME_SERVER);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	GAME_SERVER.tcp_start();
	udp_thread.join();
	return 0;
}