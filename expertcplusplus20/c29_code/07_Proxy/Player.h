#pragma once

class IPlayer
{
public:
	virtual std::string getName() const = 0;

	// ��Ʈ��ũ�� ����� ����ڿ��� �޽����� ������, ������ ������ ��Ʈ������ �����Ѵ�.
	virtual std::string sendInstantMessage(std::string_view message) const = 0;
};

class Player : public IPlayer
{
public:
	virtual std::string getName() const override;

	// ��Ʈ��ũ ������ �ʿ��ϴ�.
	virtual std::string sendInstantMessage(std::string_view message) const override;
};

class PlayerProxy : public IPlayer
{
public:
	// ���޹��� �÷��̾ ���� �������� ���� PlayerProxy �� �����Ѵ�.
	PlayerProxy(std::unique_ptr<IPlayer> player);

	virtual std::string getName() const override;

	// ��Ʈ��ũ ������ ���û����̴�.
	virtual std::string sendInstantMessage(std::string_view message) const override;

private:
	bool	hasNetworkConnectivity() const;

private:
	std::unique_ptr<IPlayer>	_player;
	bool						_hasNetworkConnectivity = false;
};