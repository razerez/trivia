import socket
import sys
import os
from termcolor import colored


IP = "192.168.43.213"
PORT = 8821
BUFFER_SIZE = 1024


def make_numbers_visible(s):
    for i in range(0, len(s)):
            if 10 >= ord(s[i]) >= 0:
                s = s.replace(s[i], chr(ord(s[i])+48))
    return s


def main():
    message = """Enter what you want to do:
1. Login
2. Signup
3. Exit
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
            choice = int(input(message))
            if choice == 1:
                username = input("Enter Username: ")
                password = input("Enter Password: ")
                msg = 'I' + chr(0) + chr(0) +chr(30+len(username)+len(password))+chr(len(username))+chr(len(password)) + " {\nusername:\""+username+"\"\npassword:\""+password+"\"\n}"
            elif choice == 2:
                username = input("Enter Username: ")
                password = input("Enter Password: ")
                email = input("Enter Email: ")
                msg = 'U' + chr(0) + chr(0) + chr(40+len(username)+len(password)+len(email))+chr(len(username))+chr(len(password)) + chr(len(email)) + " {\nusername:\""+username+"\"\npassword:\""+password+"\"\nemail:\""+email+"\"\n}"

            else:
                msg = 'X'+chr(0) + chr(0)+chr(0)
            print("Client Says: " + make_numbers_visible(msg))
            data_msg = msg.encode()
            sock.sendall(data_msg)
            data = (sock.recv(BUFFER_SIZE)).decode()
            if data == "x":
                print("Server Says: Goodbye")
                return
            data = make_numbers_visible(data)
            print("Server Says: " + data)
            # if data[0] == 'i' or data[0] == 'u':
            #    return
            input()
            os.system('cls' if os.name == 'nt' else 'clear')  # clear screen
    except Exception as e:
        print("the error is:")
        print(e)


if __name__ == '__main__':
    main()

