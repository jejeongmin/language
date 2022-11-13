메모리 죽는 문제 관련해 가장 까다로운 문제는 heap curruption 으로 인해, 문제 발생 이후 임의 시점에 죽는 버그들이다.
이 문제는 추적하기가 대단히 까다롭다.

pointer 를 직접 관리하지 않고, c++ 표준 라이브리러나, 스마트포인터를 활용하는 코드에서는
대개 multi-thread safe 하지 않는 표준 컨테이너의  부주의한 사용으로 인한 문제가 많았다.

임계 영역 처리가 적절히 되어 있지 않거나,
컨테이너 객체에 값을 사본으로 가지고 있거나, 전달하는 과정에서 객체값(iterator 가 가르키는)이 무효화되어 발생하는 경우들이다.

실제 이 문제를 잡아내는데 가장 도움이 된건 gflag 에 의한 전역 설정과 Application Verify 였다.
Rational Rose 의 Purify 도 괜찮다고 하나, 유료툴이기도 하고, 위의 2개를 활용해서 다행히 문제를 해결할 수 있었기 때문에 다른 툴을 쓸 필요는 없었다.

사전에 잡아내면 좋은데 cppCheck 나 SonarCube 와 같은 정적 분석툴에서 일부 잡아낼 수 있는 문제가 있었으나,
우리가 겪어왔던 전형적인 문제들에 대해서는 만족할만한 정적 분석 결과가 나오지 않았다.
좀더 비싼 정적 분석툴을 도입하면 좀더 좋은 효과가 있을런지도 모르겠다.

https://learn.microsoft.com/ko-kr/windows-hardware/drivers/debugger/gflags-and-pageheap
https://learn.microsoft.com/ko-kr/windows-hardware/drivers/devtest/application-verifier

