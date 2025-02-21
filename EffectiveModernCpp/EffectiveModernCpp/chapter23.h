#pragma once

#include <functional>
#include <memory>


/*********************************************************
std::move �� std::forward �� �׳� ĳ������ �����ϴ� �Լ�(��ü�����δ� �Լ� ���ø�)�̴�.
std::move �� �־��� �μ��� ������ ���������� ĳ�����ϰ�,
std::forward �� Ư�� ������ ������ ������ �׷� ĳ������ �����Ѵ�.
**********************************************************/

using namespace std;

class chapter23 : public chapter
{
	// std::move ������ �뷫 �Ʒ��� ����. �� �� �ƴ�. ĳ������ ����
	template<typename T>
	decltype(auto) move(T&& param)
	{
		using ReturnType = remove_reference_t<T>&&;
		return static_cast<ReturnType>(param);
	}

	class Annotation
	{
	public:
		explicit Annotation()	{}

		explicit Annotation(const std::string text) : _value(std::move(text))
		{
			// ���� �ۼ����� �ǵ��ʹ� �ٸ��� _value �� text �� �̵��ϴ°� �ƴ϶� ���� �ȴ�.
			// ������ std::string �� �����ڸ� ���� �˼� �ִµ�, const string �� ���, ���� �����ڸ� ���ǵǾ� �ֱ� �����̴�.
			// string&& �� ���� �̵� �����ڰ� ���ǵǾ� �ֱ� ������, const string ���� �����ڰ� �� �����ε� ���ǿ� �����ϱ� ������ �켱 ȣ��ȴ�.
			// �⺻������ '�̵�'�̶� ���� ��ü�� ��ü�� ������ ������ �ϱ� ������ const �� ���ؼ��� �̵����ٴ� ���簡 �켱�Ǵ� �� Ÿ���ϴ�.

			// �� ������ ��� ���� �� ���� �ִ�.
			// ù°, �̵��� ������ ��ü�� const �� �������� ���ƾ� �Ѵ�. const ��ü�� ���� �̵� ��û�� �Ҹ����� ���翬������ ��ȯ�ȴ�.
			// ��°, std::move �� �ƹ��͵� ������ �̵����� ���� �� �ƴ϶�, ĳ���õǴ� ��ü�� �̵� �ڰ��� ���߰� �ȴٴ� ���嵵 �������� �ʴ´�.
		}

	private:
		std::string		_value;
	};

	void process(const Annotation& lvalArg) {}
	void process(Annotation&& rvalArg) {}

	/*
		�Լ� �Ű������� �ᱹ �ϳ��� �ް��̴�. �׷��� std::forward �� ���� �������� ������
		void process( lvalArg ) �� ȣ��ȴ�.
		std::forward �� �Ű������� �ް��̸� �ް�����, �������̸� ���������� �� ���� �״�� ���������� ĳ�����ؼ� �����Ѵ�.
		�׷��� std::forward �� ���Ǻ� ĳ������ �����Ѵٰ� �ϴ� ���̴�.
	*/
	template<typename T>
	void logAndProcess(T&& param)
	{
		// log entry
		process(std::forward<T>(param));
	}

	virtual int chapterMain()
	{
		Annotation	w;

		logAndProcess(w);

		// std::move �� std::forward �� �� �� �ᱹ ĳ���ø� �����ϴ� �Լ��̰�, ���� ������ ���̴� std::move �� �׻� ĳ���������� std::forward �� ���ǿ� ���󼭸� �Ѵٴ� ���� �����ϸ�,
		// std::move �� �ƿ� �ؾ������ �׻� std::forward �� ����ϸ� ���� �ʴ��Ĵ� �ǹ��� �� ���� �ִ�. �����ϰ� ������� ���������� �´�.
		// �� std::forward �� ��� ���� �� �� �ִ�. �׷��� std::move �� �ŷ��� �Ʒ� �ڵ忡�� ������ �� ª��, ������ ������ ���ٴ� ���̴�. �ڵ��� ��Ȯ���� ��������
		logAndProcess(std::move(w));
		logAndProcess(std::forward<Annotation>(w));

		return 0;
	}
};

/*
	std::move �� ������������ ������ ĳ������ �����Ѵ�. std::move ��ü�� �ƹ� �͵� �̵����� �ʴ´�.

	std::forward �� �־��� �μ��� �������� ���� ��쿡�� �װ��� ���������� ĳ�����Ѵ�.

	std::move �� std::forward �� ��, ���� ���������� �ƹ� �ϵ� ���� �ʴ´�.
*/