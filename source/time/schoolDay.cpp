// schoolDay.cpp

#include <iostream>
#include <chrono>

using namespace std::literals::chrono_literals;
using namespace std::chrono;
using namespace std;

int main(){

  cout << endl;

  constexpr auto schoolHour= 45min;	// std::chrono::duration< int, std::ratio<int, 60i64> >

  constexpr auto shortBreak= 300s;	// std::chrono::duration< int, std::ratio<long long> >
  constexpr auto longBreak= 0.25h;	// std::chrono::duration< int, std::ratio<int, 3600i64> >

  constexpr auto schoolWay= 15min;	// std::chrono::duration< int, std::ratio<int, 60i64> >
  constexpr auto homework= 2h;		// std::chrono::duration< int, std::ratio<int, 3600i64> >

  // 결국 서로 다른 단위를 다 곱하면 가장 아래 쪽 단위인 sec 이 나옵니다.
  // constexpr std::chrono::duration<double> schoolDaySec = ((27300.0))
  constexpr auto schoolDaySec= 2*schoolWay + 6 * schoolHour + 4 * shortBreak + 
                               longBreak + homework;

  cout << "School day in seconds: " << schoolDaySec.count() << endl;

  constexpr duration<double, ratio<3600>> schoolDayHour = schoolDaySec;
  constexpr duration<double, ratio<60>> schoolDayMin = schoolDaySec;
  constexpr duration<double, ratio<1,1000>> schoolDayMilli= schoolDaySec;

  cout << "School day in hours: " << schoolDayHour.count() << endl;
  cout << "School day in minutes: " << schoolDayMin.count() << endl;
  cout << "School day in milliseconds: " << schoolDayMilli.count() << endl;

  cout << endl;

}
