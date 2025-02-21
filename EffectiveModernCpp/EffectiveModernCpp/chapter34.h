#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
	c++11 ������ ���ٰ� ���� �׻� std::bind ���� ���� �����̴�. ������ c++14 ������ '����'�� �ƴ϶� Ȯ���ϰ� ���� �����̴�.
	�׷����� �ұ��ϰ� bind �� �˾Ƶ� �ʿ䰡 �ִ� ����, �׷� �ڵ带 ���������� �ʿ䰡 �ֱ� ����.
	bind �� �׻� �� �� ���忡����, ���ٰ� �� �ȵ���.. ������鼭 ���߱� ������ 34�� ������ ���ｺ���� ���� ����.
	�ٸ� bind ������ �ȵǴ� �� �˾Ҵ� ������� ���⼭ �ڴʰ� �߰��ؼ� ��Ÿ��� ��.

**********************************************************/

using namespace std;
using namespace std::chrono;
using namespace std::placeholders;

class chapter34 : public chapter
{
	class Widget
	{};

	using Time = std::chrono::steady_clock::time_point;

	enum class Sound { Beep, Siren, Whistle };

	using Duration = std::chrono::steady_clock::duration;

	static void setAlarm(Time t, Sound s, Duration d)
	{}

	enum class CompLevel { Low, Normal, High };
	static Widget compress(const Widget&w, CompLevel lev)
	{
		return w;
	}

	class PolyWidget
	{
	public:
		template<typename T>
		void operator()(const T& param) const
		{}
	};

	virtual int chapterMain()
	{
		auto setSoundL1 = 
			[&](Sound s)
		{
			setAlarm(steady_clock::now() + hours(1), s, seconds(30));
		};

		// c++14 ������ c++11 �� ����� ���� ���ͷ� ��ɿ� �����ϴ� ǥ�� ���̻�(suffix)���� �̿��ؼ� �ڵ带 ���� �����ϰ� ���� �� �ִ�.
		// �̸��׸� �ʴ� s, �и��ʴ� ms, �ð��� h ��� ���̻縦 �̿��ؼ� �����ϸ� �ȴ�.
		auto setSoundL2 =
			[&](Sound s)
		{
			using namespace std::chrono;

			setAlarm(steady_clock::now() + 1h, s, 30s);
		};

		// �Ʒ� �ڵ忡�� �ɰ��� ���� ������ �ִ�.
		// �ۼ� �ǵ���ζ�� setAlarm �� ȣ��Ǵ� ������ 'steady_clock::now() + 1h' �� �򰡵Ǿ�� �Ѵ�.
		// ������ �Ʒ� �ڵ忡���� bind �Ǵ� ������ 'steady_clock::now() + 1h' �� �򰡵ǰ� �ȴ�.
		// ���ٿ����� �׷� ������ ����.
		auto setSoundB1 =
			std::bind(chapter34::setAlarm, steady_clock::now() + 1h, _1, 30s);

		// �ٷ� �� ������ ������ bind �����̴�.
		// �� ������ �ٷ� ��������, ù std::bind �ȿ� �� ���� �Լ� ȣ���� �������Ѿ� �Ѵ�.
		// c++14 ������ std::plus<> ���� steady_clock::time_point �� ���� �����ϴ�.
		auto setSoundB2 =
			std::bind(chapter34::setAlarm, 
				std::bind(std::plus<steady_clock::time_point>(), std::bind(steady_clock::now), 1h),
				_1, 30s);

		// setAlarm �� �Ʒ��� ���� �����ε� �ϰ� �Ǹ� ���ο� ������ �߻��Ѵ�.
		// void setAlarm(Time t, Sound s, Duration d, Volume v);
		// ������ �����Ϸ��μ��� �� setAlarm �Լ� �� � ���� std::bind �� �Ѱ��־�� �� �� ������ ����� ���ٴ� ���̴�.
		// �����Ϸ��� �˰� �ִ� ���� �Լ� �̸����̸�, �̸������δ� ���Ǽ��� �ؼ��� �� ����.
		// std::bind �� ȣ��ǰ� �Ϸ��� setAlarm �� ������ �Լ� ������ �������� ĳ���� �ؾ� �Ѵ�.
		using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d);
		auto setSoundB3 =
			std::bind(static_cast<SetAlarm3ParamType>(chapter34::setAlarm),
				std::bind(std::plus<steady_clock::time_point>(), std::bind(steady_clock::now), 1h),
				_1, 30s);

		Widget w;

		// ���ٿ����� w �� by value ����, by ref ���� ��������� �巯����.
		auto compressRateL =
			[w](CompLevel lev)
		{
			return compress(w, lev);
		};

		// ������ bind ������ bind ���� �۵� ����� ���� ���ϴ� �� �� �� ����. 
		// ���� �����ڸ� bind ������ by value �� �����Ѵ�.
		using namespace std::placeholders;
		auto compressRateB = std::bind(compress, w, _1);

		// �μ� ���� ��ĵ� ���������̴�.
		compressRateL(CompLevel::Low);		// ���ٿ����� �ڵ� �󿡼� by value ����, by ref ���� �巯����.
		compressRateB(CompLevel::Low);		// bind ������ �ڵ� �󿡼��� by value �� �� ��������, �����δ� ��� �μ��� ������ ���޵ȴ�.

		// �̵� �������� ������ �Լ� ��ü���� c++11 �� ���ٿ����� ������ �������� �ʾ�, bind �� ���� �ǹ̰� �־�����,
		// c++14 ������ ���ٷ� �� ������ Ǯ�Ⱑ �ξ� �������� ������ �׳��� �ִ� �������� �������

		PolyWidget pw;
		auto boundPW1 = std::bind(pw, _1);

		// ���� boundPW �� ���� �ٸ� ������ �μ���� ȣ���� �� �ִ�.
		boundPW1(1930); 
		boundPW1(nullptr);
		boundPW1("Rosebud");

		// c++11 ���ٷδ� ���� ������ �Ұ���������, c++14 ������ �Ʒ��� ���� ������ Ǯ �� �ִ�.
		auto boundPW2 = 
			[pw](const auto& param)
		{
			pw(param);
		};

		boundPW2(1930);
		boundPW2(nullptr);
		boundPW2("Rosebud");

		return 0;
	}
};

/*
	std::bind �� ����ϴ� �ͺ��� ���ٰ� �� �б� ���� ǥ������ ����. �׸��� �� ȿ������ �� �ִ�.

	c++14�� �ƴ� c++11������ �̵� �������� �����ϰų� ��ü�� ���ø�ȭ�� �Լ� ȣ�� �����ڿ� ������ �� �� std::bind �� ������ �� �ִ�.
*/