#pragma once

class IPlayer
{
public:
	virtual std::string getName() const = 0;

	// 네트워크로 연결된 사용자에게 메시지를 보내고, 상대방의 응답을 스트링으로 리턴한다.
	virtual std::string sendInstantMessage(std::string_view message) const = 0;
};

class Player : public IPlayer
{
public:
	virtual std::string getName() const override;

	// 네트워크 연결이 필요하다.
	virtual std::string sendInstantMessage(std::string_view message) const override;
};

class PlayerProxy : public IPlayer
{
public:
	// 전달받은 플레이어에 대한 소유권을 갖는 PlayerProxy 를 생성한다.
	PlayerProxy(std::unique_ptr<IPlayer> player);

	virtual std::string getName() const override;

	// 네트워크 연결은 선택사항이다.
	virtual std::string sendInstantMessage(std::string_view message) const override;

private:
	bool	hasNetworkConnectivity() const;

private:
	std::unique_ptr<IPlayer>	_player;
	bool						_hasNetworkConnectivity = false;
};