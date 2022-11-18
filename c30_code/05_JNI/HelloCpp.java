/*
	0. jre 를 설치해서

	1. javac HelloCpp.java 를 컴파일한다.

	2. javah HelloCpp 를 해서 HelloCpp.h 파일을 생성한다.

	3. HelloCpp.cpp 파일을 구현한다.

	JNI ( Java Native Interface ) 는 Java 코드에서 C++ 를 호출하게 해준다.
	성능이 중요한 모듈을 c++ 로 구현해서 활용할 수 있다.

	그 반대의 케이스도 가능하다. c++ 코드 내에서 Java 코드를 호출할 수 있다.
	이렇게 쓰는 용례는 거의 들어본 적이 없어서 뭐에 활용할 수 있을 지 모르겠다.
*/

public class HelloCpp {

    static {
        System.loadLibrary("hellocpp");
    }

    // 이 메서드는 C++로 구현한다.
    public static native void callCpp();

    public static void main(String[] args)
    {
        System.out.println("Hello from Java!");
        callCpp();
    }
}
