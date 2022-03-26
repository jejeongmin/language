####################### 스케줄 작업 등록 ########################

# 작업 옵션 개체
$JobOpt = New-ScheduledJobOption -RequireNetwork -RunElevated -WakeToRun

# 작업 트리거 개체
$Trigger = New-JobTrigger -Weekly -DaysOfWeek Thursday -At '5:00PM'

# 작업 구문
$JobAction = {
    Get-Service -Name 'DNS', 'ADWS', 'NTDS', 'KDC' -ComputerName DC1, DC2 | Sort-Object -Property Machinename | Format-Table -GroupBy Machinename -Property Name, DisplayName, Status
}

# 예약 작업 등록
Register-ScheduledJob -Trigger $Trigger -ScheduledJobOption $JobOpt -ScriptBlock $JobAction -MaxResultCount 10 -Name "Check DC Service"


####################### 스케줄 작업 관리 ########################

# 작업 조회
Get-ScheduledJob

# 트리거 조회
Get-JobTrigger -Name "Check DC Service"

# 예약 작업 활성화/비활성화
Enable-ScheduledJob -Name "Check DC Service"
Disable-ScheduledJob -Name "Check DC Service"

# 예약 작업 설정 변경
Set-ScheduledJob -Name "Check DC Service"


# 예약 작업 등록 제거
Unregister-ScheduledJob -Name "Check DC Service"