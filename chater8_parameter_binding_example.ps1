[CmdletBinding()]
Param(
    [Parameter(Mandatory=$True)]
    [string]$ComputerName,
    [int]$EventID = 4634
)

Get-EventLog -LogName Security -ComputerName $ComputerName | 
Where-Object EventID -eq $EventID |
Select-Object -First 10