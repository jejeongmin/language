[CmdletBinding()]
Param(
    [Parameter(Position=0,Mandatory=$True)]
    [double]$Height,
    [Parameter(Position=1,Mandatory=$True)]
    [double]$Weight
)

# BMI 계산 함수
# 파워셀에서는 .NET 함수[Math] 를 아래와 같은 형식으로 사용할 수 있다.
function Calcurate-BMI([double]$Hieght, [double]$Weight)
{
    $BMI = $Weight / ([Math]::Pow($Hieght, 2))
    return $BMI
}

# 비만도 체크 함수
function Check-ObesityIndex([double]$BMI)
{
    Write-Debug "`$BMI 는 $BMI"

    if($BMI -ge 35)
    {
        Write-Host "아주 위험! 고도 비만입니다."
        Write-Debug "'$BMI'는 35보다 크거나 같다."
    }
    elseif(($BMI -ge 30) -and ($BMI -lt 35))
    {
        Write-Host "위험! 증등도 비만입니다."
        Write-Debug "'$BMI'는 30이상 35미만이다."
    }
    elseif(($BMI -ge 25) -and ($BMI -lt 30))
    {
        Write-Host "경고! 경도 비만입니다."
        Write-Debug "'$BMI'는 25이상 30미만이다."
    }
    elseif(($BMI -ge 23) -and ($BMI -le 24.9))
    {
        Write-Host "주의! 과체중입니다."
        Write-Debug "'$BMI'는 23이상 24.9 이하이다."
    }
    elseif(($BMI -ge 18.5) -and ($BMI -lt 22.9))
    {
        Write-Host "와우! 정상입니다."
        Write-Debug "'$BMI'는 18.5이상 22.9이하이다."
    }
    else
    {
        Write-Host "주의! 저체중입니다."
        Write-Debug "'$BMI'는 18.5미만이다."
    }
}

#BMI 계산 함수를 호출하고 계산 결과를 변숭 저장한다.
$ResultBMI = Calcurate-BMI $Height $Weight
#BMI 값을 전달 받아 비만도 체크 함수를 호출한다.
Check-ObesityIndex $ResultBMI

# Set-PSBreakpoint -Line 11 -Script .\example_for_debug_01.ps1
# Set-PSBreakpoint -Variable BMI -Script .\example_for_debug_01.ps1
# Set-PSBreakpoint -Command Write-Host -Script .\example_for_debug_01.ps1
# Get-PSBreakpoint
# Disable-PSBreakpoint -Id 4,5
# Enable-PSBreakpoint -Id 4,5
# Remove-PSBreakpoint -Id 4,5

# 위와 같이 다양한 명령으로 대화식 디버깅을 수행할 수 있다.
# 그런데 ISE 나 VS 와 같은 툴 사용하면 GUI 환경에서 동일한 대화식 디버깅을 더 편리하게 사용할 수 있다.
# 위의 콘솔 명령은 이런 게 있다 정도 참고만.