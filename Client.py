import socket
import sys
import os

IP = "127.0.0.1"
PORT = 8821
BUFFER_SIZE = 1024


def main():
    messages = ['I'+chr(4) + chr(4) + chr(0)+chr(0)+" {\nusername:raz1\npassword:raz2\n}",
                'I'+chr(4) + chr(4) + chr(0)+chr(0) + " {\nusername:raz1\npassword:raz0\n}",
                'I'+chr(4) + chr(4) + chr(4) + chr(0) + " {\nusername:raz1\npassword:raz2\nemail:raz3\n}",
                'X']
    data = ""
    msg = """Enter what you want to do:
            1. Send valid login message
            2. Send invalid login message
            3. Send valid signup message
            4. send exit message
            (All messages will by followed up with a request to exit)
            """

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (IP, PORT)
    
    try:
        sock.connect(server_address)
    except Exception as e:
        print(e)
        return 

    try:
        while True:
            choice = int(input(msg))
            print("Sending: " + messages[choice-1])
            sock.sendall(messages[choice-1])
            data = s.recv(BUFFER_SIZE)
            print("received data:" + data)
            os.system('cls')

    except Exception as e:
        print(e)



if __name__ == '__main__':
    main()



