﻿Configuration EnableServer2016Backup
{
    param(
        [string[]]$ComputerName="localhost"
    )
    Node $ComputerName
    {
        WindowsFeature WindowsServerBackup
        {
            Ensure = "Present"
            Name = "Windows-Server-Backup"            
        }
    }
}

Configuration FileResourceDemo
{
    Node "localhost"
    {
        File DirectoryCopy
        {
            Ensure = "Present"
            Type = "Directory"
            Recurse = $true
            SourcePath = "D:\powershell"
            DestinationPath = "\\File1\DSCDemo\ExampleDestination"
        }

        Log AfterDirectoryCopy
        {
            # 다음 메시지는 Microsoft-Windows-Desired State
            # Configuration/Analytic 로그에 기록됨
            # DirectoryCopy 리소스가 먼저 적용되어야 한다.
            Message = "DirectoryCopy 인스턴스의 파일 리소스 작업이 끝났습니다."
            DependsOn = "[File]DirectoryCopy"
        }
    }
}