#pragma once

#include <functional>
#include <memory>
#include <mutex>


/*********************************************************
	�̸����� ������ �ٿ��شٴ� �͸����ε� ���� �ִ� enum �� ��ȣ�� ������ ����ϴ�.
	���� ���� �˻� ���� ö���� �Ǳ� ������ �������� �ƶ����� �߻��� �� �ִ� ������ �ٿ��ش�.

	å���� ���� ���� enum �� ���� ������ �ȵȴٰ� �Ǿ� �ִµ�, ��� �� ������ ������
	c++14 ������ �����ϴ�.
**********************************************************/

class chapter10 : public chapter
{
	virtual int chapterMain()
	{
		scopeless_enum();
		scope_enum();
		
		return 0;
	}

	enum class PreColor1;		// ���� ���� ����
	enum PreColor2;				// c++98 ������ ���� ���� �Ұ���

	// enum �� �⺻������ int �̳� ������ ���� ������� �������� �� �ִ�.
	enum class Status1 : std::uint32_t;
	enum Status2 : std::uint8_t;

	// enum �� �Ϲ����� int ĳ������ ����ϴ� �� �� ���� ��..
	// ���� ��� std::tuple �� ����� ��, field index�� �������� ���� enum �� ������ int ��ȯ�� Ȱ���� ��..
	// type checking �� �ִ� �������� �����ϱ� ���� ����, �ټ� Ÿ������ ������ �Ʒ��� ���� ��������
	// enumerator ��  int ��ȯ�� �Ϲ�ȭ�� �� �ִ�.
	// ������ �̰� �� �����ٱ� ���� �ڵ��ΰ�... �̷� ������ �Ű� �Ⱥη��� �ذ��� ����� ����.
	template<typename E>
	constexpr auto
		toUType(E enumerator) noexcept
	{
		return static_cast<std::underlying_type_t<E>>(enumerator;)
	}

	void scopeless_enum()
	{
		enum Color { black, white, red };
		//auto white = false;		// ����. ������ �̹� white �� ����Ǿ� ����

		Color c = red;

		if (c < 14.5)				// Color �� double �� ��!! ������ ������ �ȴ�.
		{
			//...
		}
	}

	void scope_enum()
	{
		enum class Color { black, white, red };

		auto white = false;			// �� ������ �ٸ� white �� ����

		//Color	c1 = white;			// �� ������ white ��� �̸��� �����ڴ� ����
		Color	c2 = Color::white;
		auto	c3 = Color::white;

		//if (c2 < 14.5)				// ������ type checking!! ���� static_cast �� ������ ����ȯ�ϸ� ���۽�ų �� �ִ�.
		{
			//...
		}
	}
};

/*
	c++98 ��Ÿ���� enum �� ������ ���� ���� enum �̶�� �θ���.

	���� �ִ� enum �� �����ڵ��� �� �ȿ����� ���δ�. �� �����ڵ��� ���� ĳ������
	���ؼ��� �ٸ� �������� ��ȯ�ȴ�.

	���� �ִ� enum �� ���� ���� enum ��� ���� ���� ������ �����Ѵ�.
	���� �ִ� enum �� �⺻ ���� ������ int �̴�.
	���� ���� enum ���� �⺻ ���� ������ ����.

	���� �ִ� enum �� �׻� ���� ������ �����ϴ�.
	
	���� ���� enum �� �ػ� ���� ���� ������ �����ϴ� ��쿡�� ���� ������ �����ϴ�.
	( �ƴϴ�. �� ������ c++14, ��� vs2015 ������ ������� �ʴ´�. 
	  vs2015 ���� ���� ������ �������� �ʾƵ� ���� ������ �����ϴ� )
*/