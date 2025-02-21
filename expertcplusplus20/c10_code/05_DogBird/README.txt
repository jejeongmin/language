두 소스 파일을 따로 컴파일한다.

static 함수는 override 할 수 없다. virtual 키워드도 안먹는다. 당연하다. 정적 바인딩이니까.

베이스 클래스에 다양한 버전으로 overload 된 메서드가 여럿 있는데, 그 중 한 버전만 파생 클래스에서 override 하면, 
파생 클래스에서는 나머지 base 클래스의 overload 된 메서드도 가린다.
다분히 정책적인 이유이다.
컴파일러 입장에서 볼 때 어느 한 버전만 override 했다는 것은
작성자가 원래 같은 이름을 가진 다른 메서드들도 override 할 의도를 가지고 있었는데 깜빡했다고 간주하는 것이다.
그래서 이대로 놔두면 로직 에러가 발생할 수도 있으므로 나머지 메서드를 가려주는 것이다.

c++ 에서는 private, protected 접근자로 선언된 메서드도 override 할 수 있다.
참고로 C# 과 java 에서는 private 메서드는 override 할 수 없다.

c++ 에서는 default 인자를 컴파일 타임에 결정하기 때문에 override 할 수 없다. 

파생 클래스에서는 메서드를 override 할 때, public 으로 선언한 것을 protected 로 바꾼다던가 하는 접근자를 좁히는 방향으로는 override 할 수 없다.