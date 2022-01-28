Get-Service -Name W32Time

# Get-Service 에 대한 별칭
gsv w32time

# 도움말 확인, -detailed, -full, -examples 등 옵션 사용 가
Get-Help Get-Service

# eventlog 라는 키워드를 가지고 실제 EventLog 에 쌓인 로그 정보 조회 방법을 찾아가는 과정
Get-Command -Noun *eventlog*
Get-Help Get-EventLog -Full
Get-EventLog -LogName Application -Newest 10

# 모듈을 활용해 nslookup 을 활용하는 예
Get-Module
Get-Module -ListAvailable
Import-Module -Name DnsClient제
Get-Command -Module DnsClient
Resolve-DnsName -Name www.smilegate.net

# 운영체제의 프로세스 개체에서 속성과 메서드만 표시, powershell 객체가 .NET Object 를 반환함을 잘 보여줌
Get-Process | Get-Member -MemberType Property, method

Get-Process| Out-File d:\process1.txt
Get-Process > d:\process2.txt

# 둘 이상의 개체가 혼합되어 파이프라인 출력 가능, 아래의 경우 파일과 디됨렉토리 객체가 함께 혼합되어 반환
Get-ChildItem -Path C:\Windows | Get-Member

# 입력 파라메터의 경우 파이프라인을 통해 전달되고 암묵적으로 타입에 맞춰 바인딩된다.
'Dhcp', 'EFS' | Get-Service

Get-Service | Select-Object -First 7
Get-Service | Select-Object -Last 7
Get-Service | Select-Object -Skip 7
Get-Service | Select-Object -index 0,3
Get-Service | Select-Object -index (3..6)

Get-Process | Select-Object -Property Name, ID, PM, VM
Get-Process | Select-Object -Property Name, ID, PM, VM -Last 7

# 로컬 인쇄 스풀러 서비스를 찾는다.
Get-Service -Name Spoo*
#스풀러 서비스와 종속성이 있는 서비스 목록을 확인하는 멤버를 찾는다.
Get-Service -Name Spooler | Get-Member | Select-Object -Last 7
#스풀러 서비스에 종속성이 있는 서비스 목록을 확인한다.
Get-Service -Name Spooler | Select-Object -Property ServicesDependedOn

Get-Volume | Select-Object -Property DriveLetter, Size, SizeRemaining
Get-Volume | Select-Object -Property DriveLetter, @{n='total size(GB)';e={'{0:N2}' -f ($PSItem.Size/1GB)}}, @{n='remaining size(GB)';e={'{0:N2}' -f ($PSItem.SizeRemaining/1GB)}}

# 정렬
Get-Process | Sort-Object -Property workingset

# 집계, 계산
Get-Process | Measure-Object -Property PM -Sum -Average

# 문자열 개체의 글자 수를 센다.
"Hello PowerShell" | Measure-Object -Character

# 다음의 명령으로 www.microsoft.com 에 대한 5번의 응답을 테스트한다.
Test-Connection -Count 5 -Comp www.microsoft.com | Select-Object -Property Address, IPv4Address, ResponseTime

# 다음의 명령으로 www.microsoft.com 에 대한 5번의 응답 시간ㅇ르 구해서 평균, 최대, 최소 응답 시간을 구한다.
Test-Connection -Count 5 -Comp www.microsoft.com | Measure-Object -Property ResponseTime -Average -Minimum -Maximum

# 결과 필터링
Get-Service | Where-Object -Property Status -eq Running

# 아래 세 명령의 결과는 같다. 축약 표현을 사용
Get-Service | Where-Object -FilterScript {$PSItem.Name.Length -gt 7}
Get-Service | Where-Object -FilterScript {$_.Name.Length -gt 7}
Get-Service | ? {$_.Name.Length -gt 7}

# 볼륨의 상태가 정상이 아니거나, 여유 공간이 100MB 이하인 볼륨만 나타내고 싶은 경우
Get-Volume | Where-Object -Filter { $PSItem.HealthStatus-ne 'Healthy' -or $PSItem.SizeRemaining -lt 100MB }

# M으로 시작하는 서비스 중에서 현재 실행 중인 서비스만 출력한다.
Get-Service M* | Where-Object {$_.Status -eq "Running"}
# M으로 시작하는 서비스 중에서 현재 중지된 중인 서비스만 출력한다.
Get-Service M* | Where-Object {$_.Status -eq "Stopped"}
# 위의 두 결과를 합쳐서 출력한다.
Get-Service M* | Where-Object {$_.Status -eq "Running" -or $_.Status -eq "Stopped"}
# 위의 결과에서 먼저 서비스의 상태를 내림차순으로 정렬한 다음 서비스의 이름을 내림차순으로 정렬해서 출력한다.
Get-Service M* | Where-Object {$_.Status -eq "Running" -or $_.Status -eq "Stopped"} | Sort-Object -Property Status, Name -Descending