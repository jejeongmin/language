# -*- coding: utf-8 -*-

import smtplib
from email import encoders
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def send_mail():
    from_addr = '[송신자 이메일]'
    to_addr = '[수신자 이메일]'

    subject = 'Title'
    body = 'Body'

    username = '[송신자 이메일 계정 아이디]'
    password = '[송신자 이메일 계정 패스워드]'

    # MIMEMultipart 객체로 변수를 선언합니다.
    msg = MIMEMultipart()

    # 선언된 변수에 제목(Subject), 송신자 이메일(From), 수신자 이메일(To) 를 작성합니다.
    # CC 나 BCC 가 필요한 경우에는 각각 msg['Cc'], msg['Bcc'] 로 작성해주시면 됩니다.
    # 만약 여러명에게 보내야한다면, ',' 로 구분해서 보낼 수 있습니다.
    # - 'a@a.com, b@b.com'
    msg['Subject'] = subject
    msg['From'] = from_addr
    msg['To'] = to_addr

    # 예제에서는 생략했지만, GMail 이 아닌 다른 SMTP 를 사용하는 경우,
    # 날짜(Date) 필드를 추가해야 메일이 전송되는 경우가 있습니다.
    # - from email.utils import formatdate 를 등록하고, 아래 코드를 추가해야합니다.
    # - msg["Date"] = formatdate(localtime=True)

    # 메일의 본문을 추가하기 위해서 본문 메시지를 MIMEText 를 사용해서,
    # MIME 형태로 변환한 뒤 attach 메소드를 사용해 첨부합니다.
    msg.attach(MIMEText(body))

    # 파일을 첨부하기 위해서는 몇가지 설정을 해줘야 합니다.
    # 먼저, MIMEBase 를 사용해서, 첨부 파일의 속성을 정해줘야하는데,
    # 특별히 정해진 형식이 없으면, application/octect-stream 을 작성해주시면 됩니다.
    attach = MIMEBase('application', 'octet-stream')

    # 다음으로, set_payload 메소드를 사용해서, 첨부할 파일을 등록해주시면 됩니다.
    # 'rb' 모드로 읽기, 바이너리 모드로 등록을 하고, encode_base64 메소드로 base64 인코딩을 해서 보냅니다.
    # base64 인코딩을 하는 이유는 간단하게, 문자 기반의 전송 시스템에서 바이너리 데이터(첨부 파일)를
    # 전달할 때, 사용자의 시스템에 영향을 받지 않게끔 전송/사용 되는 것을 보장하기 위해 사용합니다.
    attach.set_payload(open('./wallpaper_1.jpg', 'rb').read())
    encoders.encode_base64(attach)

    # 마지막으로 add_header 메소드를 사용해서, 'Content-Disposition' 을 작성합니다.
    # 이 값을 설정하면, 메일을 수신한 브라우저나 메일 클라이언트가 첨부 파일을 어떤 이름으로 저장할지에 대한
    # 일종의 가이드를 주게 됩니다.
    # 헤더 작성을 완료하면, 메일 본문을 추가했던 것처럼 attach 메소드를 사용해서 첨부 파일을 등록합니다.
    attach.add_header('Content-Disposition', 'attachment; filename="test.jpg"')
    msg.attach(attach)


    # 나머지 SMTP 를 보내는 과정은 기본 과정에서 설정한 내용과 동일합니다.
    # 다만, sendmail 메소드를 사용할 때, 앞서 설정한 msg 변수를 as_string 메소드를 사용해서,
    # 문자열 형식으로 변경해서 전달하게 됩니다. 이 부분 때문에 위에서 첨부파일을 base64 로 인코딩 한 것입니다.
    server = smtplib.SMTP('smtp.gmail.com:587')
    server.starttls()
    server.login(username, password)
    server.sendmail(from_addr, to_addr, msg.as_string())
    server.quit()

def main():
    send_mail()


if __name__ == '__main__':
    main()
