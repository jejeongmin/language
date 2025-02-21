#include <iostream>

using namespace std;

/*
	���Ϲ��� ���� ����(UCS, Universal Character Set)�� ISO646 �̶�� ���� ǥ���̰�,
	�����ڵ嵵 ���� ǥ�� ���� �����̴�.
	�� �� �ʸ��� �̻��� ���ڸ� ��� ������, �� ���ڸ��� ������ �̸��� �ڵ� ����Ʈ�� �������ִ�.
	�� ǥ�ؿ����� ���� ��ġ�� ���ڿ� �ڵ� ����Ʈ�� �ְ�, �� ǥ�� ��� ���ڵ� ����� ���� �ΰ� �ִ�.

	���� ��� �����ڵ�� �� ���ڸ� 
	1~4���� 8 bit �� ���ڵ��ϴ� UTF-8 ���,
	1~2���� 16 bit �� ���ڵ��ϴ� UTF-16 ���,
	1���� 32 bit �� ���ڵ��ϴ� UTF-32 ����� �ִ�.

	using string = basic_string<char>
	using wstring = basic_string<wchar_t>
	using u16string = basic_string<char16_t>
	using u32string = basic_string<char32_t>

	// �����ڵ�� ����ȭ�� �����ϴ� ��ǥ���� ���̺귯��
	https://github.com/unicode-org/icu
*/
int main()
{
	// u8, L, u, U �� ��� �Ʒ��� ���� �Ϲ� ��Ʈ�� ���ͷ� ���ξ��� R �� ������ �� �ִ�.
	const char* s1 = u8R"(Raw UTF-8 encoded string literal)";
	const wchar_t* s2 = LR"(Raw wide string literal)";
	const char16_t* s3 = uR"(Raw char16_t string literal)";
	const char32_t* s4 = UR"(Raw char32_t string literal)";

	cout << s1 << endl;
	wcout << s2 << endl;
	// ��Ʈ���� char16_t and char32_t Ÿ���� �������� �����Ƿ� s3�� s4�� ��Ʈ���� ����� �� ����.

	const char* formula = u8"\u03C0 r\u00B2";
	cout << formula << endl;

	return 0;
}
