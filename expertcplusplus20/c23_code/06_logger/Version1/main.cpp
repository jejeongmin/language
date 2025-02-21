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
	Logger ������ thread �� ����Ǳ� ���� main process �� ���� ����Ǳ� ������ terminate �Ǿ� ������ �߻��Ѵ�.
	thread ���ο��� ��� ���� �α� �޽����鵵 ���� ��µ��� �ʴ´�.
	�� ������ ������ ������ 06_logger_02 �����̴�.
*/
int main()
{
	Logger logger;

	vector<thread> threads;
	// ������ Logger �ν��Ͻ��� ����ϴ� �����带 ���� �� �����Ѵ�.
	for (int i = 0; i < 10; ++i) {
		threads.emplace_back(logSomeMessages, i, ref(logger));
		// �� ���� ��� ������ ���� �ۼ��ص� �ȴ�.
		// threads.push_back(thread{ logSomeMessages, i, ref(logger) });
	}

	// ��� �����尡 ���� ������ ��ٸ���.
	for (auto& t : threads) {
		t.join();
	}

	return 0;
}
