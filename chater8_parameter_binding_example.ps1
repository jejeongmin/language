[CmdletBinding()]
Param(
    [Parameter(Mandatory=$True)]
    [string]$ComputerName,
    [int]$EventID = 4634
)

# 디버깅 메시지 출력
Write-Debug -Message "`$ComputerName: $ComputerName"
Write-Verbose -Message "로그 이름을 입력 받습니다"
$LogName = Read-Host "로그 이름을 입력하세요."

Write-Debug -Message "`$LogName: $LogName"
Write-Verbose -Message "'$ComputerName' 에서 '$LogName' 로그 추출 시작."

Get-EventLog -LogName Security -ComputerName $ComputerName | 
Where-Object EventID -eq $EventID |
Select-Object -First 10
