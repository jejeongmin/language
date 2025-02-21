# AD의 파워쉘 전문가 그룹 관리
try
{
    $ScriptGuys = Get-Content d:\powershell\scriptguylist.txt -EA Stop
}
catch
{
    $ErrorMsg = $_.Exception.Message     #에러 내용
    $ErrorItem = $_.Exception.ItemName   #에러 항목
    break;
}
finally
{
    $ExceptionTime = Get-Date
    $LogText = "이 스크립트가 '$ExceptionTime' 에 실행되었습니다."
    $LogText | Out-File d:\powershell\ADGroupScript.log -Append
}

$ADPSUser = Get-ADGroupMember "PS_Expert"
Foreach($User in $ADPSUser)
{
    if($ScriptGuys -notcontains $User)
    {
        Remove-ADGroupMember -Identify "PS_Expert" -User $User
    }
}

# 다중 Catch 블록 구현
$Users = Get-Content D:\powershell\users.txt

foreach($User in $Users)
{
    try
    {
        Get-ADUser -Identity $User -ErrorAction Stop
        Write-Output "$user 있음"
    }
    catch [Microsoft.ActiveDirectory.Management.ADIdentityNotFoundException]
    {
        Write-Host "$user 없음" -ForegroundColor Red
    }
    catch
    {
        Write-Output "다른 에러 처리"
    }
}