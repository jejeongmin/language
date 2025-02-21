#include <iostream>
#include <locale>

using namespace std;

/*
	로케일은 날짜 포맷, 시간 포맷, 숫자 포맷 등으로 구성되는데, 이러한 요소를 패킷(facet)이라고 부른다.
*/
int main()
{
	locale locUSEng("en-US");       // 윈도우
	//locale locUSEng("en_US");     // 리눅스
	locale locBritEng("en-GB");     // 윈도우
	//locale locBritEng("en_GB");   // 리눅스

	wstring dollars = use_facet<moneypunct<wchar_t>>(locUSEng).curr_symbol();
	wstring pounds = use_facet<moneypunct<wchar_t>>(locBritEng).curr_symbol();
	
	wcout << L"In the US, the currency symbol is " << dollars << endl;
	wcout << L"In Great Britain, the currency symbol is " << pounds << endl;

	return 0;
}
