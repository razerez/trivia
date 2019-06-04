import socket
import sys
import os

IP = "127.0.0.1"
PORT = 8821
BUFFER_SIZE = 1024


def main():
    strdata =  " {\nusername:\"raz1\"\npassword:\"raz2\"\nemail:\"raz3\"\n}"
    strDataLen = len(strdata) + 2
    print(strDataLen)

    messages = ['I' + chr(0) + chr(0) + chr(38) + chr(4) + chr(4)+" {\nusername:\"raz1\"\npassword:\"raz2\"\n}",
                'U'+chr(0) + chr(0) + chr(52) + chr(4) + chr(4) + chr(4) + " {\nusername:\"raz1\"\npassword:\"raz2\"\nemail:\"raz3\"\n}",
                'X'+chr(0) + chr(0)+chr(0)]
    data = ""
    msg = """Enter what you want to do:
            1. Send valid login message
            2. Send valid signup message
            3. send exit message
            (All messages will by followed up with a request to exit)
            """

    data_msg = ""
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
            print("Client Says:\n" + data_msg)
            data_msg = data_msg.encode()
            sock.sendall(data_msg)
            data = (sock.recv(BUFFER_SIZE)).decode()
            if data == "x":
                print("Server Says: Goodbye")
                return
            if len(data) > 1 and (ord(data[1]) == 1 or ord(data[1]) == 0):
                data = list(data)
                data[1] = chr(ord(data[1])+48)
                data = "".join(data)
            print("Server Says:" + data)
    except Exception as e:
        print("the error is:")
        print(e)



if __name__ == '__main__':
    main()

