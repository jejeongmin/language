############### WinRM Service 활성화 ###############
Enable-PSRemoting -SkipNetworkProfileCheck -Force

Get-ChildItem WSMan:\localhost\Client\TrustedHosts

# https 를 설정하지 않고 비도메인 컴퓨터에 연결하려는 TrustedHosts 목록은 보안에 취약할 수 있다.
# TrustedHosts 목록은 보안이 강하게 관제되는 데이터 센터에 있는 서버들과 같이 쉽게 접근하기 어려운 컴퓨터들에 한해서만 사용해야 한다.
# 정말 필요한 경우가 아니라면, 비도메인 컴퓨터는 https 를 사용해 구성하는 것이 더 안전한 솔루션이다.

Set-Item WSMan:\localhost\Client\TrustedHosts -Value "192.168.35.205"

# 다른 컴퓨터에서 이 컴퓨터로 아래와 같이 파워쉘 세션 형성
Enter-PSSession -ComputerName 192.168.35.205 -Credential DESKTOP-FOIF80S\admin
# 다른 컴퓨터에서 파워쉘 스크립트 블록 실행
Invoke-Command -ComputerName DESKTOP-FOIF80S -ScriptBlock {Get-Service}

# WinRM Service 비활성화
Disable-PSRemoting

# 원격 파워쉘 실행 환경을 힘들게 구성하느니, Jenkins 와 같은 분산 실행 환경을 구성해서 powershell 을 실행하는 게 다 나은 방법 같다.


############### 원격 컴퓨터에 매개변수 전달하기 ###############

# evtLog, Count 두 변수는 아래 파워쉘이 실행되는 컴퓨터의 세션에 존재하는 변수이며 jeongminje-D 에 존재하는 변수는 아니다.
$evtLog = 'Security'
$Count = 7
Invoke-Command -Computer jeongminje-D -ScriptBlock {
    Get-EventLog -LogName $evtLog -Newest $Count
}

# 원격의 컴퓨터로 파워쉘 명령을 실행할 때는 지역 변수를 ArgmentList 에 포함해서 전달해줘야 한다.
$evtLog = 'Security'
$Count = 7
Invoke-Command -Computer jeongminje-D -ScriptBlock {
    Param($x, $y)
    Get-EventLog -LogName $x -Newest $y
} -ArgumentList $evtLog, $Count

# PowerShell 3.0 이면 좀더 간단하게 수정할 수 있다.
$evtLog = 'Security'기
$Count = 7
Invoke-Command -Computer jeongminje-D -ScriptBlock {
    Get-EventLog -LogName $Using:evtLog -Newest $Using:Count
}


############### 멀티 홉 원격 관리 ###############
# CL1 host -> WEB1 host -> DC1 host
# 파워쉘 원격 연결을 위한 자격 증명을 이용해 Target 서버에 접속할 수 있지만, Target Server 로부터 또 다른 서버로 자격 증명을 이어나갈 순 없다.
# 그럴 경우 CredSSP ( Credential Security Support Provider ) 라는 인증 프로토콜 서비스를 이용해야 한다.


# 자격 증명을 위임할 서버를 지정한다. 이 명령을 CL1 컴퓨터에서 실행
Enable-WSManCredSSP -Role Client -DelegateComputer WEB1

# 자격 증몀을 다시 위임할 서버에서 위임 작업을 가능하게 설정한다. 이 명령을 WEB1 컴퓨터에서 실행
Enable-WSManCredSSP -Role Server

# 클라이언트에서 원격 서버인 WEB1 에 원격 세션을 열어 WEB1 에서 DC1 에 설치된 윈도우의 기능을 확인한다.
Enter-PSSession -ComputerName WEB1 -Credential SGE\Administrator -Authentication Credssp
Invoke-Command -ComputerName DC1 -ScriptBlock {
    Get-WindowsFeatures | Where-Object {$_.InstallState -eq 'Installed'}}

# 작업이 끝나면 멀티홉 위임을 다시 제거해서 보안위협을 줄여야 한다.
# CL1 에서 수행
Disable-WSManCredSSP -Role Client
# WEB1 에서 수행
Disable-WSManCredSSP -Role Server

############### 영구적인 연결 관리 ###############
#1. 영구 연결 세션 만들기
$RemoteSS = New-PSSession -Name WEB1Session -ComputerName WEB1
#2. 만든 세션을 이용해 작업 실행하기
Invoke-Command -Session $RemoteSS -ScriptBlock {
    $dll = Get-ChildItem -Path C:\Windows\system32 -Recurse | Where-Object {$_.Extension -eq ".dll"}
}
#3. 세션 끊기
Disconnect-PSSession -Session $RemoteSS
#4. 원격 컴퓨터의 끊어진 세션 확인하기
Get-PSSession -ComputerName WEB1
#5. 끊어진 세션 연결하기
$LocalSS = Connect-PSSession -ComputerName WEB1 -Name WEB1Session
#6. 연결된 세션의 작업 결과 확인
Invoke-Command -Session $LocalSS -ScriptBlock {$dll}
#7. 세션 제거 ( 재사용 못함 )
Remove-PSSession -Name WEB1Session

############### 묵시적인 원격 작업 ###############
# 파워쉘 버전이 맞지 않거나, 원격 컴퓨터와 사용할 수 있는 명령이 다를 경우 필요한 명령만 원격 컴퓨터로부터 가져와서 프록시처럼 사용할 수 있다.

#0. 실행 정책 변경
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned

#1. WEB1 서버에 파일서버 리소스 관리자 역할 서비스 설치
Install-WindowsFeature -Name FS-Resource-Manager -IncludeAllSubFeature -includeManagementTools

#2. CL1 에서 WEB1 서버와 원격 세션 수립
$file = New-PSSession -ComputerName WEB1

#3. 원격 컴퓨터에서 사용 가능한 모듈 확인
Get-Module -PSSession $file -ListAvailable

#4. 파일 서버 리소스 관리자 모듈을 로드하고 명령에 접두어 표시
Import-Module -PSSession $file -Name FileServerResourceManager -Prefix Rem

#5. 도움말 확인
Get-Help Set-RemFSrmQuota -Full

#6. 클라이언트에서 할당량 템플릿을 조회하는 명령 실행
Get-RmsFSrmQuotaTemplate | Format-Wide

#7. 암시적 원격 작업 세션 제거와 세션 자동 다시 연결
Get-PSSession | Remove-PSSession
Get-RmsFSrmQuotaTemplate | Format-Wide


############### 파워쉘 웹 액세스 ###############
# 이게 있는데.. 왜 힘들게 위의 것들을... ㅎㅎ.
# 한 장비만 PowerShell Gateway 삼아, 인증서 설치해서 SSL 통신하고, 그 장비와 나머지 내부 장비들을 PSSession 연결하면 심플하겠는데.
Install-WindowsFeature -Name WindowsPowerShellWebAccess -IncludeManagementTools
