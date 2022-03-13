$ProcessList = Get-Process
ForEach($Process in $ProcessList)
{
    if(($Process.PM/1MB) -le 250)
    {
        continue
    }
    Write-Output ($Process.Name+'은 250MB 이상의 메모리를 사용한다')
}