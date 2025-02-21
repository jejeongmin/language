# PowerShell DSC 를 사용하는 핵심 목적은
# SE 입장에서는 코드로 인프라 자동화 구성을 쉽게 해서 인프라 운영 비용을 줄이고
# 개발 입장에서는 DevOps 환경 구성을 더 용이하게 하기 위해서이다.

# AWS, Azure 등에도 비슷한 Cmd 기반 솔루션이 있을 것이고, 환경 배포라는 측면에서는 maven 과도 유사한 면이 있다.

###################### DSC 기본 ###################################

# DSC 구성에 있어서 대부분의 작업은 아래 모듈에 포함되어 있다.
Get-Command -Module PSDesiredStateConfiguration | Select-Object -Property CommandType, Name

# DSC 에서 관리하는 DSC 리소스를 확인할 때 사용
Get-DscResource | Select-Object -Property Name, Properties

# 파워쉘 갤러리( https://www.powershellgallery.com/ ) 로부터 모듈이나 DSC 리소스 다운로드 설치 가능

# 파워쉘 설치 여부와 버전 확인
Get-Module -ListAvailable PowerShellGet | ft -AutoSize

# 파워쉘 최신 버전 설치
Install-Module -Name PowerShellGet -Force

# 인터넷에 연결되지 않은 다른 컴퓨터에 설치하기 위해 다운로드 받아 별도 저장이 필요할 경우
Save-Module -Name PowerShellGet -Path C:\Temp

# 웹 관리를 위한 DSC 모듈이 필요하다면 다음 명령으로 설치
Install-Module -Name xWebAdministration -Force

# 아래와 같이 . 를 한 칸 띄고 실행하면 스크립트 실행이 끝나도 함수와 변수가 메모리에 유지된다. 이를 도트 소싱이라고 한다.
. .\example_for_dsc_01.ps1

# 대상 컴퓨터 이름을 지정해서 DSC 구성 가능, 스크립트 실행 위치에서 mof 파일 컴파일 생성
EnableServer2016Backup -ComputerName DESKTOP-FOIF80S

###################### DSC Push 구성 ###################################

# 실제 web1 서버에 mof 파일을 Push 방식으로 배포
Start-DscConfiguration -Path D:\powershell\example_for_dsc_01.ps1 -Wait -Verbose


###################### DSC Pull Server 구성 ###################################

# 끌어오기 서버는 https or smb 방식으로 구성할 수 있다. 범용적으로는 web server 를 이용한 https 방식을 많이 이용한다.

# 1. 다음 명령으로 끌어오기 서버에서 xPSDesiredStateConfiguration
Install-Module -Name xPSDesiredStateConfiguration -Force

# 2. 끌어오기 서버에서 WS-Management 리스너가 활성화되지 않았다면, 파워쉘 원격을 활성화한다. 아래 둘 중 하나를 실행한다.
Enable-PSRemoting -SkipNetworkProfileCheck -Force
winrm qc

# 3. Pull Server DSC 구성 메모리에 적재
.\example_for_dsc_03.ps1

# 4. PullServer 를 이용해 대상 노드(pull.mydomain.local)를 위한 MOF 파일을 만든다.
PullServer -ComputerName pull.mydomain.local

# 5. 컴파일이 생성해서 현재 위치에 PullServer 폴더가 만들어지고 그 안에 pull.mydomain.local.mof 파일이 생성되었다면
#    다음 명령을 사용해서 pull.mydomain.local 서버에 구성을 밀어넣는다.
Start-DscConfiguration -Path .\PullServer -Wait

# 6. 끌어오기 서버가 제대로 구성되었다면 아래 사이트를 통해 끌어오기 서버의 웹 서비스에 접근 가능할 수 있는지 확인한다.
http://pull:8080/PSDSCPullServersvc/


###################### DSC Pull Client 구성 ###################################

# 끌어오기 클라이언트는 구성이름을 통해서, 혹은 구성 ID 를 통해서 설정할 수 있다. GUID 를 통한 구성 ID 설정 방식이 더 보편적이다.

# 1. Pull Client DSC 구성 메모리에 적재
.\example_for_dsc_04.ps1

# 2. web1, web2 노드에 배포할 MOF 파일을 컴파일한다.
MyDomainWebsite -ComputerName web1.mydomain.local, web2.mydomain.local

# 3. 구성 ID 방식으로 클라이언트를 구성할 것이므로 각 노드에 대한 GUID 를 만들고 변수에 저장한다.
$Web1Guid = New-Guid
$Web2Guid = New-Guid

# 4. 이제 각 GUID 이름으로 앞서 만든 mof 파일의 이름을 변경해 끌어오기 서버를 구성할 때 지정한 경로에 복사한다.
    # 원본 mof 파일 위치
    $Web1Src = ".\MyDomainWebSite\web1.mydomain.local.mof"
    $Web2Src = ".\MyDomainWebSite\web2.mydomain.local.mof"

    # 원본 mof 이름을 GUID로 변경 후 복사할 위치 끌어오기 서버에 복사
    $Dest = "\\pull\c$\Program Files\WindowsPowerShell\DscService\Configuration\"
    $Web1Dest = $Dest + "$Web1Guid.mof"
    $Web2Dest = $Dest + "$Web2Guid.mof"

    # 끌어오기 서버로 mof 파일 복사
    Copy-Item -Path $Web1Src -Destination $Web1Dest
    Copy-Item -Path $Web2Src -Destination $Web2Dest

# 5. mof 파일을 잘 복사했다면, 각각에 대한 체크썸 파일을 만들어야 한다. 
#    끌어오기 클라이언트에서 자신에게 할당된 구성을 끌어오려고 할 때, 이 체크썸 파일을 사용해 mof 파일의 무결성을 확인한다.
New-DscChecksum $Web1Dest
New-DscChecksum $Web2Dest

# 6. 메타 mof 파일을 생성한다.
PullClient -TargetNode web1.mydomain.local -GUID $Web1Guid
PullClient -TargetNode web2.mydomain.local -GUID $Web2Guid

# 7. 6번에서 만든 메타 mof 파일을 각각의 끌어오기 클라이언트에 적용한다.
Set-DscLocalConfigurationManager -ComputerName web1.mydomain.local -Path .\PullClient -Verbose
Set-DscLocalConfigurationManager -ComputerName web2.mydomain.local -Path .\PullClient -Verbose

# 8 서비스 설치되었는지 구성 확인
Invoke-Command -ComputerName web1, web2 -ScriptBlock { Get-DscConfigurationStatus }
