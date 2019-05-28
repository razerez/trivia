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
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    data = ""
    try:
        s.connect((IP, PORT))
    except:
        print("failed to connect on:\n  ", sys.exc_info()[0])
        return

    while True:
        try:
            choice = int(input("""
            Enter what you want to do:
            1. Send valid login message
            2. Send invalid login message
            3. Send valid signup message
            4. send exit message
            (All messages will by followed up with a request to exit)
            """))
            print("Sending: " + messages[choice-1])
            s.send(messages[choice-1])
            data = s.recv(BUFFER_SIZE)
            input("received data:" + data)
            os.system('cls')
        except:
            print("failed to connect on:\n  ", sys.exc_info()[0])
        s.close()


if __name__ == '__main__':
    main()
