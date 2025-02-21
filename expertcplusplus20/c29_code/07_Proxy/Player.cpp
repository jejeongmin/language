#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

std::string Player::getName() const
{
	return "Player";
}

std::string Player::sendInstantMessage(std::string_view message) const
{
	cout << "Player send : " << message.data() << endl;

	return "yes";
}

PlayerProxy::PlayerProxy(std::unique_ptr<IPlayer> player) : _player(std::move(player))
{
}

std::string PlayerProxy::getName() const
{
	return "PlayerProxy";
}

bool PlayerProxy::hasNetworkConnectivity() const
{
	return _hasNetworkConnectivity;
}

std::string PlayerProxy::sendInstantMessage(std::string_view message) const
{
	if (hasNetworkConnectivity())
	{
		return _player->sendInstantMessage(message);
	}
	else
	{
		return "no";
	}	
}