/*
	0. jre �� ��ġ�ؼ�

	1. javac HelloCpp.java �� �������Ѵ�.

	2. javah HelloCpp �� �ؼ� HelloCpp.h ������ �����Ѵ�.

	3. HelloCpp.cpp ������ �����Ѵ�.

	JNI ( Java Native Interface ) �� Java �ڵ忡�� C++ �� ȣ���ϰ� ���ش�.
	������ �߿��� ����� c++ �� �����ؼ� Ȱ���� �� �ִ�.

	�� �ݴ��� ���̽��� �����ϴ�. c++ �ڵ� ������ Java �ڵ带 ȣ���� �� �ִ�.
	�̷��� ���� ��ʴ� ���� �� ���� ��� ���� Ȱ���� �� ���� �� �𸣰ڴ�.
*/

public class HelloCpp {

    static {
        System.loadLibrary("hellocpp");
    }

    // �� �޼���� C++�� �����Ѵ�.
    public static native void callCpp();

    public static void main(String[] args)
    {
        System.out.println("Hello from Java!");
        callCpp();
    }
}
