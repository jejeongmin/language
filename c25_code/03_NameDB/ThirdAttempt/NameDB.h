#pragma once

#include <string_view>
#include <string>
#include <map>

/*
	이 버전에서는 생성자의 코드를 코드 관점에서 조금 더 최적화했다.
	성능항샹은 01 -> 02 로 간 것에 비하면 미미하다.

	이 예제 전반을 통해서 핵심은
	프로파일러 사용 및 분석을 통해 생성자 구간에서 최적화를 시도해야 한다는 사실을 발견하는 것이다.
*/
class NameDB
{
public:
	// nameFile에 담긴 이름 목록을 읽어서 데이터베이스에 저장한다.
    // nameFile을 열 수 없거나 읽을 수 없으면 invalid_argument 익셉션을 던진다.
	NameDB(std::string_view nameFile);

	// 이름의 인기순위를 리턴한다(1st, 2nd 등).
	// 주어진 이름이 데이터베이스에 없으면 -1을 리턴한다.
	int getNameRank(std::string_view name) const;

	// 주어진 이름을 가진 아기가 몇 명인지 리턴한다.
	// 입력한 이름을 가진 아기가 없으면 -1을 리턴한다.
	int getAbsoluteNumber(std::string_view name) const;

private:
	std::map<std::string, int> mNames;
};
