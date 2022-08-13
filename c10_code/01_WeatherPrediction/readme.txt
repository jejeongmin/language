기본적으로 데이터 멤버는 모두 private 으로 선언하는 게 바람직하다.
파생 클래스에서 접근할 일이 있으면 그때 protected 로 전환하거나, 처음부터 설계에 의해 protected 로 해야 한다.
method 도 마찬가지다.

method 는 일반적으로 virtual로 선언하는게 바람직하다.
혹시 virtual 선언을 안해서 이후에 파생 클래스에서 나도 모르게 overriding 이 아닌, overloading 해버릴 수 있기 때문이다.

또 파생 클래스에서는 overriding 된 함수에는 override 선언을 해주는 게 좋다.
virtual void showResult() const override;

유지보수하는 과정에서 Base 클래스의 virtual function 의 원형을 수정하는 경우 ( 리턴 타입이나 인자 ),
깜빡하고 Derived 클래스의 virtual function 을 함께 수정해주지 않을 때, override 키워드가 없다면, 
아무런 문법적 에러를 일으키지 않고, overloading 으로 바뀐다.
작성자가 overloading 을 의도하지 않았기 때문에 발견하기 어려운 논리적 오류를 발생시킨다.