switch(Get-Service) {
    {$_.status -eq "Running"}{ "실행 중인 서비스:"+$_.name }
    {$_.status -eq "Stopped"}{ "중단된 서비스:"+$_.name }
}