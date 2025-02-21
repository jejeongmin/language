//#define MAIN_3

#ifdef MAIN_3
class X {};
class Y {};

/*
	reinterpret_cast �� Ȱ���ϴ� ���δ� �ܼ� ���� ���(��Ʈ������) �� ���� binary I/O �� �����ϴ� ��츦 �� �� �ִ�.
*/
int main()
{
	X x;
	Y y;

	X* xp = &x;
	Y* yp = &y;

	// ���� ���� Ŭ������ �����͸� ��ȯ�� ���� reinterpret_cast()�� ����ؾ� �Ѵ�.
	// static_cast�δ� �� �� ����.
	xp = reinterpret_cast<X*>(yp);

    // �����͸� void*�� ��ȯ�� ���� ĳ������ �ʿ� ����.
    void* p = xp;
    // void*�� �����ͷ� ��ȯ�� ���� reinterpret_cast()�� ����ؾ� �Ѵ�.
    xp = reinterpret_cast<X*>(p);

	// ���� ���� Ŭ������ ���۷����� ��ȯ�� ���� reinterpret_cast()�� ����ؾ� �Ѵ�.
	// static_cast�δ� �� �� ����.
	X& xr = x;
	Y& yr = reinterpret_cast<Y&>(x);

	return 0;
}
#endif