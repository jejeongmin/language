#include <string>
#include <string_view>
#include <iostream>

class IParagraph
{
public:
	virtual ~IParagraph() = default;  // 항상 가상 소멸자로 정의한다.
	virtual std::string getHTML() const = 0;
};

class Paragraph : public IParagraph
{
public:
	Paragraph(std::string_view text) : mText(text) { }
	virtual std::string getHTML() const override { return mText; }

private:
	std::string mText;
};

class BoldParagraph : public IParagraph
{
public:
	BoldParagraph(const IParagraph& paragraph) : mWrapped(paragraph) { }

	virtual std::string getHTML() const override
	{
		return "<B>" + mWrapped.getHTML() + "</B>";
	}

private:
	const IParagraph& mWrapped;
};

class ItalicParagraph : public IParagraph
{
public:
	ItalicParagraph(const IParagraph& paragraph) : mWrapped(paragraph) { }

	virtual std::string getHTML() const override
	{
		return "<I>" + mWrapped.getHTML() + "</I>";
	}

private:
	const IParagraph& mWrapped;
};


/*
	데코레이터 패턴은 영어 단어의 뜻 그대로 객체를 꾸미는 역할을 한다. 흔히 래퍼라고 부르기도 한다.
	이 패턴은 객체의 동작을 실행 시간에 추가하거나 변경하는데 사용된다.
	데코레이터는 파생 클래스와 상당히 비슷하지만, 그 효과가 일시적이라는 점이 다르다.
*/
int main()
{
	Paragraph p("A party? For me? Thanks!");

	// 굵게
	std::cout << BoldParagraph(p).getHTML() << std::endl;

	// 굴고 이탤릭체로
	std::cout << ItalicParagraph(BoldParagraph(p)).getHTML() << std::endl;

	return 0;
}
