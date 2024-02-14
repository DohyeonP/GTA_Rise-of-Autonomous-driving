import socket
import time

HOST = '10.10.15.200'  # NodeMCU의 IP 주소
PORT = 12345            # NodeMCU에서 열어둔 포트

try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print("서버에 연결됨")
        #한번 전송하고 연결을 끊지않고 유지, \n를 통해 데이터 패킷을 구분함.
        while True:
            # 데이터 전송
            i =123;
            data_to_send = "PC!: " + f"{i}\n"  # 데이터 끝에 개행 문자를 추가하여 구분
            s.sendall(data_to_send.encode('utf-8'))
            print(f"전송된 데이터: {data_to_send}")

            time.sleep(0.1)  # 0.1초 대기

except KeyboardInterrupt:
    print("프로그램 종료")
