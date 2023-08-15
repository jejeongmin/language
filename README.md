# androidkotlinstudy

[코틀린 & 안드로이드 개념 설명](https://cometome1004.tistory.com/70)

[FoodChoiceApp - nav, 기본 화면 구성](https://la-bontoo.tistory.com/2)

[Kotlin Android - RecycleListView 예제](https://dalgonakit.tistory.com/137)



# Kotlin 클래스 생성자에서 독특한 점
class Person(val name: String, val age: Int, val grade: Int = 1)
와 같이 변수를 val 이나 var 로 선언하면 - 생성자에서만 허용하는 문법 - 자동으로 멤버 변수로 추가된다.


# Diary 모듈 참고할 코드
1. by lazy 에 의한 UI 객체 늦은 초기화
2. NumberPicker 사용 예시
3. Indent 에 의한 화면 전환
4. Runnable 객체 사용을 통한 메인 루프에 Timer 로직 태우기

# lotto number generator 모듈 참고할 코드
1. 랜덤 넘버 생성
2. text 스타일에 백그라운드 컬러 추가

# BMI calcurator 모듈 참고할 코드
1. 버튼 리스너 구현 및 반환 형식에 대한 설명
2. Indent 에 의한 화면 전환 및 데이터 교환

# app 모듈 참고할 코드
1. nav graph 사용 예시
2. fragment 사용 예시

# myapplication 모듈 참고할 코드
1. Toast 메시지
2. layout 과 구현 객체의 auto binding

# mylistapplication 모듈 참고할 코드
1. list view 에 대한 항목 추가/삭제
2. Room 객체 사용을 통한 데이터 저장
3. List 표시 객체 holder, adpater 사용 예시

# LiveData 모듈 참고할 코드
1. LiveData
Data의 변경을 관찰 할 수 있는 Data Holder 클래스
LiveData는 Observable과 다르게 안드로이드의 생명주기를 알고 있다.
활성상태에서만 데이터를 업데이트
LiveData는 Observer 객체와 같이 사용하여 LiveData가 가지고 있는 데이터에 변화가 발생 시 Observer 객체에 알려주고 Observer의 onChanged() 메서드 실행
2. 장점 
Data와 Ui 동기화 : 옵저버 패턴을 이용하여 데이터 변경 마다 Observer 객체에 전달
메모리 누수 방지 : 옵저버 객체를 통해 Destroy될 경우 메모리를 스스로 해제
Stop 상태 액티비티와 크래쉬 발생 방지 : 옵저버의 생명주기가 비활성인 경우 LiveData 이벤트 수신x
항상 최신 데이터 유지
자원 공유
3. 사용법
Generic을 사용하여 관찰할 데이터의 타입을 갖는 LiveData 생성
옵저버 객체 생성

# Fragment
1. Fragment 사용법
2. [동적으로 Fragment 추가하는 법](https://cometome1004.tistory.com/144)
3. Fragment 내의 UI 요소를 정렬하는 방법
4. Fragment -> Fragment를 포함한 Activity 로 데이터를 전송하는 방법