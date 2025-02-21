#pragma once

template<typename T>
class TD;

/*********************************************************
	�Ʒ��� ��� ���ܵ��� ǥ�ؿ��� ������ ������ ����ϵ��� �ǰ��� ��,
	��Ȯ�� ������ �ݵ�� ����� ���� �����ϰ� ������ �ʴ�.
	���� �Ʒ� ������ 100% �ŷ��� �� �����Ƿ�, ���� ������ ���� ��Ģ�� ������
	���α׷��Ӱ� ��Ȯ�� �˾ƾ� �� �����̴�.

	runtime Ÿ�� ���� Ȯ�ν� ǥ�ؿ� ���Ե� typeid �̿ܿ���
	��ǥ���̱� �ϳ� boost::typeindex::type_id_with_cvr �� ����� �� �ִ�.
**********************************************************/
class chapter04 : public chapter
{
	class Widget
	{
	};

	template<typename T>
	void f(const T& param)
	{
		std::cout << "T = " << typeid(T).name() << std::endl;
		std::cout << "param = " << typeid(param).name() << std::endl;
	}


	std::vector<Widget> createVec()
	{
		std::vector<Widget>	vw;
		
		vw.push_back(Widget());
		vw.push_back(Widget());

		return vw;
	}

	virtual int chapterMain()
	{
		const int	theAnswer = 42;

		// �ٷ� �Ʒ� 2�ٰ� ���� ������ �Ǵ� �ڵ��̸� intellisense �� �̿��� ���� ������ ��������.
		auto x = theAnswer;
		auto y = &theAnswer;

		// �ٷ� �Ʒ� �ڵ�� ���� �Ϻη� ������ ������ �Ͻ� �߻�����, �����Ϸ��� ���� �޽����� Ȱ��.
		//TD<decltype(x)> xType;

		// ��Ÿ�ӽ�, typeid �� �̿��� ���� ������ Ȯ���� �� �ִ�.
		std::cout << " type x is " << typeid(x).name() << std::endl;

		const auto vw = createVec();

		if (!vw.empty())
		{
			f(&vw[0]);
		}

		return 0;
	}
};

/*
	�����Ϸ��� �����ϴ� ������ IDE �����⳪ �����Ϸ� ���� �޽���, Boost TypeIndex ���̺귯����
	�̿��ؼ� �ľ��� �� �ִ� ��찡 ����.

	�Ϻ� ������ ����� ���������� �ʰ� ��Ȯ������ ���� �� �����Ƿ�,
	C++ ���� ���� ��Ģ���� ����� �����ϴ� ���� ������ �ʿ��� ���̴�.
*/