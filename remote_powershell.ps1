# WinRM Service 활성화
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
