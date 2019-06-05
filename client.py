import socket
import sys
import os
from termcolor import colored


IP = "127.0.0.1"
PORT = 8821
BUFFER_SIZE = 1024


def make_numbers_visible(s):
    for i in range(0, len(s)):
            if 10 >= ord(s[i]) >= 0:
                s = s.replace(s[i], chr(ord(s[i])+48))
    return s


def main():
    messages = ['I' + chr(0) + chr(0) + chr(38) + chr(4) + chr(4)+" {\nusername:\"raz1\"\npassword:\"raz2\"\n}",
                'I' + chr(0) + chr(0) + chr(38) + chr(4) + chr(4)+" {\nusername:\"yee1\"\npassword:\"raz2\"\n}",
                'U'+chr(0) + chr(0) + chr(52) + chr(4) + chr(4) + chr(4) + " {\nusername:\"rez1\"\npassword:\"raz2\"\nemail:\"raz3\"\n}",
                'J'+chr(0) + chr(0)+chr(0),
                'X'+chr(0) + chr(0)+chr(0)]
    msg = """Enter what you want to do:
1. Valid Login
2. Invalid Login
3. Signup
4. Irrelevant Request
5. Exit
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
            data_msg = messages[choice-1]
            print("Client Says: " + make_numbers_visible(data_msg))
            data_msg = data_msg.encode()
            sock.sendall(data_msg)
            data = (sock.recv(BUFFER_SIZE)).decode()
            if data == "x" or data[0] == 'i' or data[0] == 'u':
                print("Server Says: Goodbye")
                return
            data = make_numbers_visible(data)
            print("Server Says: " + data)
            input()
            os.system('cls' if os.name == 'nt' else 'clear')  # clear screen
    except Exception as e:
        print("the error is:")
        print(e)


if __name__ == '__main__':
    main()

