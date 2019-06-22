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
    message = """Enter what you want to do:
1. Login
2. Signup
3. GetRooms
4. GetPlayersInRoom
5. GetHighscore
6. JoinRoom
7. CreateRoom
8. Logout
9. Exit(not build yet)
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
            elif choice == 3:
                msg = 'G' + chr(0) + chr(0) + chr(0)
            elif choice == 4:
                roomid = input("Enter Room ID: ")
                msg = 'P' + chr(0) + chr(0) + chr(1) +chr(int(roomid))
            elif choice == 5:
                msg = 'H' + chr(0) + chr(0) + chr(0)
            elif choice == 6:
                roomid = input("Enter Room ID: ")
                msg = 'J' + chr(0) + chr(0) + chr(1) + chr(int(roomid))
            elif choice == 7:
                roomName = input("Enter room name: ")
                maxUsers = input("Enter max users: ")
                questionsCount = input("Enter question count: ")
                answerTime = input("EnterAnswerTime: ")
                msg = 'C' + chr(0) + chr(0) + chr(60 + len(roomName) + len(maxUsers)+ len(questionsCount)+ len(answerTime)) + chr(len(roomName))+chr(len(maxUsers))+chr(len(questionsCount))+chr(len(questionsCount)) + " {\nRoomName:\"" + roomName + "\"\nMaxUsers:" + chr(int(maxUsers)) + "\nQuestionsCount:" + chr(int(questionsCount)) + "\nanswerTime:\"" + answerTime + "\"\n}"
            elif choice == 8:
                msg = 'O' + chr(0) + chr(0) + chr(14) + chr(0) + " {\nusername:\""
            else:
                msg = 'X' + chr(0) + chr(0) + chr(14) + chr(0) + " {\nusername:\""
            print("Client Says: " + msg)
            data_msg = msg.encode()
            sock.sendall(data_msg)
            data = (sock.recv(BUFFER_SIZE)).decode()
            print("Server Says: " + make_numbers_visible(data))
            if data == "x":
                print("Server Says: Goodbye")
                return

            # if data[0] == 'i' or data[0] == 'u':
            #    return
            input()
            os.system('cls' if os.name == 'nt' else 'clear')  # clear screen
    except Exception as e:
        print("the error is:")
        print(e)


if __name__ == '__main__':
    main()

