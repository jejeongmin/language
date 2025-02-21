# -*- coding: utf-8 -*-

import smtplib
from optparse import OptionParser
from email import encoders
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def get_attach_msg(attach_file):
    # 첨부파일을 보내기 위한 함수입니다.
    attach = MIMEBase('application', 'octet-stream')
    attach.set_payload(open(attach_file, 'rb').read())
    encoders.encode_base64(attach)
    attach.add_header('Content-Disposition', 'attachment; filename="%s"' % attach_file)
    return attach

def send_mail(attach_file, cc, bcc):
    from_addr = '[송신자 이메일]'
    to_addr = '[수신자 이메일]'

    subject = 'Title'
    body = 'Body'

    username = '[송신자 이메일 계정 아이디]'
    password = '[송신자 이메일 계정 패스워드]'

    msg = MIMEMultipart()

    msg['Subject'] = subject
    msg['From'] = from_addr
    msg['To'] = to_addr

    # CC 를 보내기 위한 설정입니다.
    if cc:
        msg['Cc'] = from_addr

    # BCC 를 보내기 위한 설정입니다.
    if bcc:
        msg['Bcc'] = from_addr

    msg.attach(MIMEText(body))

    if attach_file is not None:
        msg.attach(get_attach_msg(attach_file))

    server = smtplib.SMTP('smtp.gmail.com:587')
    server.starttls()
    server.login(username, password)
    server.sendmail(from_addr, to_addr, msg.as_string())
    server.quit()

def main():
    option = OptionParser(usage='%prog', version='%prog 1.0')
    option.add_option('-a', '--attach', dest='attach', type='string', help='Please enter a file to attach.')
    option.add_option('-c', '--use_cc', dest='cc', action='store_true', help='Add my mail address as cc.')
    option.add_option('-b', '--use_bcc', dest='bcc', action='store_true', help='Add my mail address as bcc.')

    (options, args) = option.parse_args()

    send_mail(options.attach, options.cc, options.bcc)


if __name__ == '__main__':
    main()
