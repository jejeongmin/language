#include "Logger.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;

void logSomeMessages(int id, Logger& logger)
{
	for (int i = 0; i < 10; ++i) {
		stringstream ss;
		ss << "Log entry " << i << " from thread " << id;
		logger.log(ss.str());
	}
}

/*
	Logger 내부이 thread 가 종료되기 전에 main process 가 먼저 종료되기 때문에 terminate 되어 오류가 발생한다.
	thread 내부에서 펜딩 중인 로그 메시지들도 전부 출력되지 않는다.
	이 문제를 개선한 버전은 06_logger_02 버전이다.
*/
int main()
{
	Logger logger;

	vector<thread> threads;
	// 동일한 Logger 인스턴스를 사용하는 스레드를 여러 개 생성한다.
	for (int i = 0; i < 10; ++i) {
		threads.emplace_back(logSomeMessages, i, ref(logger));
		// 위 문장 대신 다음과 같이 작성해도 된다.
		// threads.push_back(thread{ logSomeMessages, i, ref(logger) });
	}

	// 모든 스레드가 끝날 때까지 기다린다.
	for (auto& t : threads) {
		t.join();
	}

	return 0;
}
