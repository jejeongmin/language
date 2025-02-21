Configuration PullServer
{
    param(
        [string[]]$ComputerName="localhost"
    )

    Import-DscResource -ModuleName xPSDesiredStateConfiguration

    Node $ComputerName
    {
        # Windows Server DSC 서비스 기능 로드
        WindowsFeature DSCServiceFeature
        {
            Ensure = "Present"
            Name = "DSC-Service"
        }

        # 웹 서비스 배포를 단순화하기 위해 DSC 리소스 사용
        xDSCWebService PSDSCPullServer
        {
            Ensure = 'Present'
            EndpointName = 'PSDSCPullServer'
            Port = 8080
            PhysicalPath = "$env:SYSTEMDRIVE\inetpub\wwwroot\PSDSCPullServer"
            CertificateThumbPrint = 'AllowUnencryptedTraffic'
            ModulePath = "$env:PROGRAMFILES\WindowsPowerShell\DscService\Module\Configuration"
            State = 'Started'
            DependsOn = '[WindowFeature]DSCServiceFeature'
            UseSecurityBestPractices = $false
        }
    }
}