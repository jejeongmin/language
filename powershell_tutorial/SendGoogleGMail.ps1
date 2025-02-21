# https://techexpert.tips/ko/powershell-ko/%ED%8C%8C%EC%9B%8C%EC%89%98-gmail%EC%9D%84-%EC%82%AC%EC%9A%A9%ED%95%98%EC%97%AC-%EC%9D%B4%EB%A9%94%EC%9D%BC-%EB%B3%B4%EB%82%B4%EA%B8%B0/
# gmail 로 외부에서 메일을 보내기 위해서 app 비밀번호 생성을 통해 인증을 처리하도록 설정해줘야 한다.

$SMTPServer = "smtp.gmail.com"
$SMTPPort = "587"
$Username = "jjmyann@gmail.com"
$Password = "????"

$to = "jjmyann@gmail.com"
$cc = "jjmyann123@naver.com"
$subject = "Email Subject"
$body = "Insert body text here"
# $attachment = "C:\test.txt"

$message = New-Object System.Net.Mail.MailMessage
$message.subject = $subject
$message.body = $body
$message.to.add($to)
$message.cc.add($cc)
$message.from = $username
# $message.attachments.add($attachment)

$smtp = New-Object System.Net.Mail.SmtpClient($SMTPServer, $SMTPPort);
$smtp.EnableSSL = $true
$smtp.Credentials = New-Object System.Net.NetworkCredential($Username, $Password);
$smtp.send($message)
write-host "Mail Sent"