#pragma once

#include <string>
#include <string_view>

class Logger
{
public:
	enum class LogLevel {
		Error,
		Info,
		Debug
	};

	Logger();
	virtual ~Logger() = default;  // 항상 가상 소멸자로 정의한다.

	void log(LogLevel level, std::string message);

private:
	// 로그 수준을 사람이 읽을 수 있는 스트링 포맷으로 변환한다.
	std::string_view getLogLevelString(LogLevel level) const;
};

/*
	간혹 내부 추상화가 현재 디자인과 맞지 않지만 변경할 수 없을 때가 있다.
	혹은 이미 구현을 바꿀 수 없는, 또는 소스가 없는 모듈의 인터페이스를 변경해서 사용하는 경우가 될 수도 있다.
	이럴 때는 Adapter 혹은 Wrapper 를 만들어서 해결한다.
	어댑터는 어떤 기능의 구현 코드에 대한 바람직한 추상화를 제공하면서 그 기능의 사용자와 구현 코드를 연결해주는 역할을 한다.	
*/
class NewLoggerInterface
{
public:
	virtual ~NewLoggerInterface() = default;  // 항상 가상 소멸자로 정의한다.
	virtual void log(std::string_view message) = 0;
};

class NewLoggerAdaptor : public NewLoggerInterface
{
public:
	NewLoggerAdaptor();
	virtual void log(std::string_view message) override;

private:
	Logger mLogger;
};
