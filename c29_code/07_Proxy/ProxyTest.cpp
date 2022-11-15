#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

bool informWinner(const IPlayer& player)
{
	auto result = player.sendInstantMessage("You have won! Player again?");

	if (result == "yes")
	{
		cout << player.getName() << " want to play again." << endl;
		return true;
	}
	else
	{
		cout << player.getName() << " does not want to play again." << endl;
		return false;
	}
}

int main()
{
	auto	onlinePlayer = make_unique<Player>();
	onlinePlayer->sendInstantMessage("hello");
	informWinner(*onlinePlayer);

	PlayerProxy		offlinePlayer(std::move(onlinePlayer));
	offlinePlayer.sendInstantMessage("hello again");
	informWinner(offlinePlayer);

	return 0;
}