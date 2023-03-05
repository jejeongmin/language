# demo.py

help(print)

result = "aaa"
print(result)

# 다중 문자열을 묶을 때는 따옴표 3개로
print("""
    한국어로
    in English
    다되네.
""")

# escape 문자는 C++ 과 유사함
print("c:\\test.txt \' \"")

'py''thon'
'py'+'thon'

# python 도 indexing 은 0부터 시작
a='python'
a[0]
a[1]

# python 은 음수 인덱싱도 지원함
# 인덱싱에 : 으로 범위 지정하는 것 어디에서 봤나 했더니
# AI 공부할 때, jupiter note book 에서 봤네
a[0:4]
a[:4]
a[4:]
a[-1]
a[-3:]
a[:-3]

# list
listNumber = ["one", "two", "three"]
listNumber
listNumber.append("five")
listNumber.insert(3, "four")
listNumber
listNumber.pop()
listNumber.remove()
type(listNumber)

# set
# |, &, - 으로 각각 합집합, 교집합, 차집한 연산 지원
setNumber = {1,2,3,3}
setNumber   # 중복을 허용하지 않음
type(setNumber)

# tuple
a,b,c = 1,2,3
tupleNumber = (4,5,6)
print(a,b,c)
len(tupleNumber)
tupleNumber
type(tupleNumber)

# 아래의 경우 유용하게 활용
def calc(a,b):
    return a+b,a*b

# 1. 함수에서 하나 이상의 값을 리턴하거나
# 2. 출력하는 경우 활용거나
calc(3,4)

# 3. 함수 입력 인자가 여럿이어서 묶어서 전달할 때
argc = (5,6)
calc(*argc)     # *를 붙이면 여러 개 인자가 넘어간다는 의미

# 타입 변경은 서로 자유롭게 변경 가능
type(setNumber)
b = list(setNumber)
c = tuple(b)
type(c)

# dictionary
dic = dict(a=1, b=2, c=3)
dic
type(dic) 
del dic["a"]
dic
dic["a"] = 1
dic
for key in dic.keys():
    print(key, dic[key])

for value in dic.values():
    print(value)

color = {"apple":"red", "banana":"yello"}
color
for item in color.items():
    print(item)

 # 얕은 복사
a = [1,2,3]
b = a
a[0] = 38
a
b
id(a), id(b)

 # 깊은 복사
a = [1,2,3]
b = a[:]
a[0] = 38
a
b
id(a), id(b)

# copy func
import copy
src = [1,2,3]
swallow_copy_dst = copy.copy(src)
deep_copy_dst = copy.deepcopy(src)
src[0] = 38
src
swallow_copy_dst
deep_copy_dst
id(src), id(swallow_copy_dst), id(deep_copy_dst)

# 산술 연산자와 관계 연산자는 다른 언어와 동일
# 논리 연산자는 기호를 쓰지 않고 영어를 그대로 사용
x = 10
y = 20
x > 5 and y < 15
x > 5 or y < 15
not (x>5)

# 결과를 잃지 않도록 알아서 형 변환을 해주는 건 c++ 과 다르다.
5 / 2

# 메모리에 있는 객체의 값을 보여주는 내장함수
globals()

def intersect(preList, postList):
    retList = []
    for x in preList:
        if x in postList and x not in retList:
            retList.append(x)
    return retList

intersect("HAM", "SPAM")

# 가변형, 불변형
# python 은 스택에서의 전달 방식 기본은 call by reference 이다.
# 그래서 call by value 는 일부러 작성해줘야 한다.
def change_ref(x):
    x[0] = 'H'

def change_value(x):
    x = x[:]
    x[0] = 'H'

words = ['J','A','M']
words
change_value(words)
words
change_ref(words)
words

# Python 에서 변수 해석하는 순서
# LGB, Local -> Global -> Built-in

g = 1
def testScope(a):
    global g    # 로컬 외부의 g 를 내부에서 참조한다고 선언
    g = 2
    return g+a

testScope(1)
g

# *는 가변인자를 의미
def test(*args):
    print(type(args))
test(1,2)

def union(*ar):
    res = []
    for item in ar:
        for x in item:
            if not x in res:
                res.append(x)
    return res
union("HAM", "EGG", "SPAM")

# ** 는 정의되지 않은 인자를 dictionary 형태로 사용할 것을 의미
def userURIBuiler(server, port, **user):
    str = "http://" + server + ":" + port + "/?"
    for key in user.keys():
        str += key + "=" + user[key] + "&"
    return str
userURIBuiler("test.com", "8080", id='userid', passwd='1234')

# lambda
lambdafunc = lambda x,y : x*y
lambdafunc(2,3)

(lambda x,y : x*y)(4,5)

# help 에 대한 문서화, __doc__
help(lambdafunc)
lambdafunc.__doc__ = "help에 대한 내용을 이런 방식으로 정의 가능하다."
help(lambdafunc)

# pass 아무것도하지 않고 그냥 넘어가도록 할 경우
# ReadMe.txt 에 이것과 관련해 AI 와 질답한 내용 참고
# while True:
#     pass    # 빠져나가라면 키보드에서 ctrl+c 를 누름


# iterator, for 루프가 아니어도 iter 함수를 이용해 iterator 를 만들 수 있다.
iteratorLoop = "1234"
it = iter(iteratorLoop)
it
next(it)
next(it)
next(it)
next(it)
next(it)

it = iter([1, 2, 3])
try:
    while True:
        value = next(it)
        print(value)
except StopIteration:
    print("End of iteration")