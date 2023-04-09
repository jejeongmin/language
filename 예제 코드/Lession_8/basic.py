# -*- coding: utf-8 -*-

# 메일을 전송하기 위해 smtplib 라이브러리를 등록합니다.
import smtplib

def send_mail():
    # 메일에서 사용할 메일 주소들과 제목, 본문을 사전에 정의합니다.
    from_addr = '[송신자 메일]'
    to_addr = '[수신자 메일]'

    subject = 'Title'
    body = 'Body'

    # 앞서 정의한 값들을 message 라는 변수에 저장합니다.
    # 메시지의 형식이 있는데, 수신자의 메일(From), 송신자의 메일(To), 제목(Subject),
    # 수신 참조(Cc), 숨은 수신 참조(Bcc) 와 같이 표시하고, 개행 문자로 구분하여 작성합니다.
    # 메일의 본문은 타이틀 없이 그냥 사용합니다.
    message = ('From: %s\nTo: %s\nSubject: %s\n%s' % (from_addr, to_addr, subject, body))

    # 사용자가 메일을 보낼 SMTP 서버의 접속 계정입니다.
    username = '[송신자 메일 계정 아이디]'
    password = '[송신자 메일 계정 패스워드]'

    # SMTP 라이브러리를 사용해서, 사용하는 SMTP 의 주소와 포트를 입력합니다.
    # 예제에서는 GMail 을 사용했기 때문에 GMail 의 SMTP 주소와 포트를 사용했습니다.
    server = smtplib.SMTP('smtp.gmail.com:587')

    # SMTP 서버와의 연결 채널을 TLS 라는 보안 프로토콜로 설정하겠다는 의미입니다.
    # 안전한 통신을 위해서 TLS 보안을 사용하는 것을 권고합니다.
    server.starttls()

    # SMTP 서버에 로그인을 하는 과정입니다.
    server.login(username, password)

    # 정상적으로 로그인이 되면, sendmail 을 통해서 메시지를 전송할 수 있습니다.
    # 앞서 설정한 메시지 변수를 인자로 사용하는데, 한글의 경우 글자가 깨질 수도 있기 때문에
    # 인코딩 설정을 'euc-kr' 이나 'utf-8' 로 설정해서 전달합니다.
    server.sendmail(from_addr, to_addr, message.encode('euc-kr'))
    server.quit()

def main():
    send_mail()


if __name__ == '__main__':
    main()
