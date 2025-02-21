$NumOfShots = 0
While($True)
{
    $MovingTarget = (Get-Date).Second
    if( $MovingTarget -eq $NumOfShots)
    {
        Write-Host "이동 목표를 맞추는데 사용된 슈팅 회수(s):$NumOfShots"
        Break
    }
    $NumOfShots++
}