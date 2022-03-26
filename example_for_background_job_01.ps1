# 백그라운드로 실행
Start-Job -ScriptBlock { Dir C:\ -Recurse } -Name ListingDrive_C

# 원격 컴퓨터를 대상으로 백그라운드로 실행, AsJob 을 붙이면 된다.
Invoke-Command -ScriptBlock { Dir C:\ -Recurse } -ComputerName jeongminje-d -AsJob -JobName RemoteListingDrive_C

# WMI ( Windows Management Infra ) 에서도 원격 작업이 백그라운드로 처리 가능하다.
Get-WmiObject -Class Win32_NTEventLogFile -ComputerName jeongminje-D -AsJob

# workflow 도 백그라운드로 실행 가능
Say-HelloWF -AsJob -JobName SayHelloWFJob

# Job 조회, 각 작업은 최소 2개의 작업 개체로 구성된다. ChildJob 은 해당 작업을 수행하는 각 컴퓨터별로도 수행된다.
Get-Job

# Child Job 조회
Get-Job -Name ListingDrive_C | Select-Object -ExpandProperty ChildJobs
Get-Job -Name ListingDrive_C -IncludeChildJob

# Job 일시 중지
Get-Job -Name ListingDrive_C | Suspend-Job

# Job 재시작
Get-Job -Name ListingDrive_C | Resume-Job

# 진행 중인 Job 내용 중간에 메모리로부터 받아오기
Receive-Job -Id 1 keep

# Job 중지
Stop-Job -Name ListingDrive_C | Suspend-Job

# Job 제거
Remove-Job -Name ListingDrive_C | Suspend-Job

# Job 대기, 앞서의 파워쉘 실행 완료를 전제로 이후 작업이 진행되어야 할 경우, Wait-Job 을 통해 결과 대기
Get-Job | Wait-Job Any

