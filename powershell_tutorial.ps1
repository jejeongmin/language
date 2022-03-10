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

# 출력 스트림의 표현 양식을 아래와 같이 처리할 수 있다.
$Msg=@("Hello","Powershell","world")
Write-Host -Object $Msg -ForegroundColor White -BackgroundColor Black -Separator ∥

# GUI 형식의 gridview 로 출력 가
Write-Output @(1..5) | Out-GridView
Write-Output @(1..5) -NoEnumerate | Out-GridView
Get-ChildItem | Out-GridView

# 시스템의 서비스 목록을 가져와서 상태의 이름으로 정렬하고 그리드뷰로 출력한다.
Get-Service | Sort-Object Status, DisplayName | Out-GridView
# 그리드 뷰의 타이틀 이름을 "정렬된 서비스 목록"으로 하고, 서비스 목록을 다중 선택해서 콘솔에 출력한다. '확인' 버튼이 생김
Get-Service | Sort-Object Status, DisplayName | Out-GridView -Title "정렬된 서비스 목록" -OutputMode Multiple
# 첫번째 그리드 뷰에서 다중 선택한 목록을 다시 그리드 뷰로 출력한다.
Get-Service | Sort-Object Status, DisplayName | Out-GridView -Title "정렬된 서비스 목록" -PassThru | Out-GridView -Title "선택한 서비스 목록"

# 서시 목록을 가져와 상태로 정렬한 다음 이름과 상태 속성만 포함하는 ASCII 형식의 ServideList.csv 파일로 출력한다.
Get-Service | Sort-Object -Property Status | Select-Object -Property Name, Status | Out-File -FilePath ServiceList.txt -Encoding ascii

# Microsoft Print to PDF 라는 가상 프린터 형태로 출 
"Hello PowerShell" | Out-Printer -Name "\\jeongminje\Microsoft Print to PDF"력

# 현재 시스템에서사용할 수 있는 프린터 이름 출력
Get-Printer | Select-Object -Property Name, DriverName, PortName

# 현재 디렉토리의 파일 목록을 3개의 열로 출력
Get-ChildItem | Format-Wide -Column 3
# 현재 디렉토리의 파일들의 생성 시간을 창에 맞게 맞게 가로로 배열해서 출력
Get-ChildItem | Format-Wide -Property CreationTime -AutoSize
# 프로세스의 목록과 각 프로세스의 속성 중 이름과 ID, 시작 시간을 표시
Get-Process | Format-List -Property Name, ID, StartTime
# Out-* 동사로 시작하는 명령 중 별칭이 있는 항목의 모든 속성을 구하는 명령
Get-Alias -Definition out-* | Format-Table -Property * -Wrap

# 프로세스별 이름,ID,물리 메모리 크기 출력
# 물리 메모리 크기의 레이블을 PM(MB) 로 바꾸고 값을 MB 단위로 출력
# PM(MB) 열의 값을 소수점 둘째 자리, 왼쪽 맞춤으로 출력
Get-Process | Format-Table -Property Name,ID,@{n='PM(MB)'; e={$PSItem.PM/1MB};formatString='N2';align='Left'}

# 개체를 먼저 그룹화 하고자 하는 속성으로 정렬하는 과정을 거쳐야 한다.
Get-Service | Format-Table -GroupBy Status
Get-Service | Sort-Object -Property Status | Format-Table -GroupBy Status

# csv 나 xml 등 값과 형식을 가진 파일 객체로 출력
Get-Process | ConvertTo-CSV | Out-File Process.csv
Get-Process | Export-Csv Process.csv

Get-Service | Sort-Object -Property Status
Get-Service | Sort-Object -Property Status | Select-Object -Property Name, Status, StartType
Get-Service | Sort-Object -Property Status | Select-Object -Property Name, Status, StartType | ConvertTo-Csv | Out-File -FilePath ServiceList.csv

# 파일로부터 입력 받는 방
Get-Service | Export-Csv Services.csv
Import-Csv Services.csv | Sort-Object -Property Name, Status, StartType -Descending | Select-Object -First 5

# 사용자 입력 받는 방법
$pwd=Read-Host -Prompt "type password" -AsSecureString

# 100 개의 무작위 수를 얻는다.
1..100 | ForEach-Object { Get-Random }

# $ps 가 null 이면 다 작동 안함.
$ps = Get-Process | Where-Object {$_.processName -eq "asdsvc"}
Write-Host $ps.Handles;
# 아래와 같이 kill 시키거나 속성에 대해 write 동작을 수행할 수도 있음
# $ps.maxworkingset=30x1024x1024
# $ps.kill()

# Windows 에서 기본 제공하는 공급자 목록을 확인
Get-PSProvider

Get-Help FileSystem

# 시스템에서 사용 가능한 모든 드라이브 확인
Get-PSDrive

# 네트워크 드라이브 연결(일시적)
New-PSDrive -Name "SVR1Share" -PSProvider FileSystem -Root "\\cf2_wip"

# 네트워크 드라이브 연결(영구적)
New-PSDrive -Persist -Name "Z" -PSProvider FileSystem -Root "\\cf2_wip"

# 위에서 만든 드라이브 연결 제거
Remove-PSDrive -Name SVR1Share, Z

# C:\Program Files 폴더를 PROGDIR 이라는 임시 드라이브로 매핑한다.
New-PSDrive -Name PROGDIR -Root "C:\Program Files" -PSProvider FileSystem
# 매핑한 드라이브의 파일을 조회한다.
dir PROGDIR:
Get-ChildItem -Path PROGDIR:
# 다시 지운다.
Remove-PSDrive -Name PROGDIR

# 레지스트리 공급자의 HKCU 드라이브에 "PowerShell\School" 이라는 새로운 레지스트리 키를 만든다.
New-Item -Path HKCU:\ -Name PowerShell
New-Item -Path HKCU:\PowerShell -Name School
# School 키 내에 'Class' 라는 속성을 만들고, 'basic' 이라는 값을 설정한다.
New-ItemProperty -Path HKCU:\PowerShell\School -Name Class -Value basic
# 새로 만든 School 키 내의 Class 속성과 값을 확인한다.
Get-ItemProperty -Path HKCU:\PowerShell\School
# PowerShell 레지스트리 삭제
Remove-Item HKCU:\PowerShell -Recurse

# 스크립트 실행 정책 확인
Get-ExecutionPolicy
# Restricted, AllSigned, RemoteSigned, Unrestricted, Bypass, Undefined
Set-ExecutionPolicy Restricted

# $표시는 파우쉘 엔진에 변수 자체가 아니라 변수의 내용을 액세스 한다는 의미이다.
$var = 'daily'
Set-Variable -Name $var -Value 700
Write-Host $var
Write-Host $daily

# 변수로 받는 건 객체형식이기 때문에 앞선 명령의 결과 반환 형식이 뭔지 확인해야 한다.
# 아래 경우는 배열 형태의 결과를 고려해 스크립트 명령을 작성해야 한다.
$file = Get-ChildItem -Path C:\Windows -File
Get-Content -Path $file[0].FullName

# script 실행을 하기 위해서는 실행 정책 변경이 우선 되어 있어야 한다.
Set-ExecutionPolicy Unrestricted
.\chater8_parameter_binding_example.ps1 -ComputerName 'DESKTOP-FOIF80S'
Set-ExecutionPolicy Undefined
.\SendMail.ps1 -To "jjmyann@gmail.com" -Subject "테스트 메일" -Body "Powershell 스크립트에서 보낸 메일입니다."


# 아직 Get-SecurityEvents 함수를 로딩하기 전 함수 목록 체크
cd fucntion:
ls
# Get-SecurityEvents 함수를 로딩
D:\powershell\DeclareFunction_Get-SecurityEvents.ps1
# Get-SecurityEvents 함수를 로딩한 후 함수 목록 체크
ls
# 함수 호출
Get-SecurityEvents DESKTOP-FOIF80S
