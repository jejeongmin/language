Configuration MyDomainWebSite
{
    param(
        [string[]]$ComputerName="localhost"
    )

    Import-DscResource -ModuleName PSDesiredStateConfiguration

    Node $ComputerName
    {
        # IIS 역할 설치
        WindowsFeature IIS
        {
            Ensure = "Present"
            Name = "Web-Server"
        }

        # ASP.NET 4.6 설치
        WindowsFeature ASPNET46
        {
            Ensure = "Present"
            Name = "Web-Asp-Net45"
        }
    }
}

# 끌어오기 클라이언트 구성 스크립트
Configuration PullClient
{
    param(
        $GUID,
        $TargetNode
    )

    Node $TargetNode
    {
        LocalConfigurationManager
        {
            ConfigurationID = $GUID;
            RefreshMode = 'PULL';
            DownloadManagerName = 'WebDownloadManager';
            RebootNodeIfNeeded = $true
            ConfigurationModeFrequencyMins = 15;
            ConfigurationMode = 'ApplyAndAutoCorrect';
            DownloadManagerCustomData = @{
                ServerUrl = "http://pull:8080/PSDSCPullServer.svc";
                AllowUnsecureConnection = $true
            }
        }
    }
}

