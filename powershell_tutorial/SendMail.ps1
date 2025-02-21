[CmdletBinding()]
Param(
    [Parameter(Mandatory=$False)]
    [string]$From = "제정민<jjmyann@gmail.com>",
    [Parameter(Mandatory=$True)][string] $To,
    [Parameter(Mandatory=$False)]
    [string]$Cc = "제정민<jjmyann123@naver.com>",
    [Parameter(Mandatory=$True)][string] $Subject,
    [Parameter(Mandatory=$False)]
    [string]$Body = "mail from powershell",
    [Parameter(Mandatory=$True)]
    [PSCredential] $Cred = (Get-Credential)
)

$SmtpSvr = "smtp.gmail.com"
$SmtpPort = 587

Send-MailMessage -From $From -To $To -Cc $Cc -Subject $Subject -Body $Body -SmtpServer $SmtpSvr -Port $SmtpPort -UseSsl -Credential $Cred -Encoding UTF8