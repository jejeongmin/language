# 워크플로는 어떤 일을 완료하는 데 필요한 활동을 정의한 것으로, 
# 이 활동에는 작업의 단계와 규칙, 결정 사항들이 포함된다.
# 워크플로는 함수와 상당히 유사하며 파워쉘 스크립트의 특수한 버전이다.

Workflow Say-HelloWF {
    Write-Output -InputObject "Hello workflow!"
}

Workflow Get-ProcessWF {
    Get-Process -PSComputerName DESKTOP-FOIF80S
}

Workflow Test-ConnectionWF {
    Write-Output "$($PSComputerName)에 대한 ICMP 테스트"
    Test-Connection -ComputerName $PSComputerName
}

# inlineScript 활용 사례 #1, 워크플로에서 실행할 수 없도록 제외된 명령 실행
Workflow Get-AliasWF {
    InlineScript { Out-Host -InputObject "대상 컴퓨터의 별칭을 가져옵니다." }
    InlineScript { Get-Alias }
}

# inlineScript 활용 사례 #2, 외부 스크립트를 실행
Workflow Run-PSScriptWF {
    Param($PSComputerName)
    $MachineInfo = InlineScript {
        D:\powershell\Get-SystemInfo.ps1 -Target $using:PSComputerName
    } -PSPersist $true 

    Write-Output "[### $($MachineInfo.Name) 의 시스템 정보  ###]"
    Write-Output "1. 메인보드는 $($MachineInfo.Motherboard)입니다."
    Write-Output "2. CPU는 $($MachineInfo.CPU)이며 코어는 $($MachineInfo.Cores)개입니다."
    Write-Output "3. 메모리는 $($MachineInfo.RAM) GB 입니다."
    Write-Output "4. 그래픽 카드는 $($MachineInfo.GPU)입니다."
}

# 워크스페이스에 대한 문법 확인
Get-Command -Name Say-HelloWF -Syntax

# 워크 스페이스 호출
Say-HelloWF
Get-ProcessWF
Test-ConnectionWF -PSComputerName DESKTOP-FOIF80S
Get-AliasWF
Run-PSScriptWF -PSComputerName DESKTOP-FOIF80S

# 워크플로는 기본적으로 여러 서버 장비에 대해서 정기적이면서 긴 실행시간을 가지는 패턴화된 작업을 자동화하기 위한 용도이다.
# 간단한 건 파워쉘 기본 기능으로 이용하되, SE 레벨에서 주기적인 작업이 있으면 워크플로를 활용해 자동화를 고려한다.
# 병렬, 순차 실행 지정이 

# 윈도우 서버에서 다수의 VM 을 자동으로 프로비저닝 하기 위한 워크플로 예시, Hyper-V 지원하는 Windows Server 2016 이상에서 실행 가능
Workflow New-VmsWF {
    # 만들 VM 의 개수
    $Vms = 1..10

    Foreach -Parallel ($vm in $Vms)
    {
        # VDI 를 만들기 위한 기본 정보
        $VMName = "VDI$vm"
        [int64]$VMRam = 512MB
        $VMPath = "M:\VMs\VDIs"
        $VHDPath = "M:\VMs\VDIs\$VMName\"
        $HyperV_Host = "LW-MCT-WS2016"
        $VMSwitch = "Private Network"

        # 새로운 가상 하드디스크를 만든다.
        New-VHD -Path "$VHDPath$VMName.vhdx" -SizeBytes 10GB
        # 새로운 가상 머신을 만든다.
        New-VM -Path "$VMPath" -Name $VMName -VHDPath "$VHDPath$VMName.hdx" -MemoryStartupBytes $VMRam -ComputerName $HyperV_Host
        # 만든 가상 머신에 가상 스위치를 연결한다.
        Connect-VMNetworkAdapter -VMName $VMName -SwitchName $VMSwitch -ComputerName $HyperV_Host
    }
}

#Active Directory 계정 프로비저닝 워크플로
Workflow Provision-ADAccountWF {
    $Users = 1..10
    $Computers = 1..10
    $Password = ConvertTo-SecureString -AsPlainText -String "Pa`$`$w0rd" -Force

    Sequence {
        Parallel {
            New-ADOrganizationalUnit -Path "DC=MyDomain,DC=local" -Name Employees
            New-ADOrganizationalUnitA -Path "DC=MyDomain,DC=local" -Name MyComputers
        }

        Foreach -Parallel ($user in $Users)
        {
            New-ADUser -AccountPassword $Password -Name "User$user" -UserPricipalName "User$user@mydomain.local"
            Enable-ADAccount -Identity "User$user"
        }

        Foreach -Parallel ($com in $Computers)
        {
            New-ADComputer -Path "OU=MyComputers,DC=MyDomain,DC=local" -Name "Com$com"
        }
    }
}