import socket
import sys
import os

IP = "172.16.25.101"
PORT = 8821
BUFFER_SIZE = 1024


def main():
    strdata =  " {\nusername:\"raz1\"\npassword:\"raz2\"\nemail:\"raz3\"\n}"
    strDataLen = len(strdata) + 2
    print(strDataLen)

    messages = ['I' + chr(0) + chr(0) + chr(38) + chr(4) + chr(4)+" {\nusername:\"raz1\"\npassword:\"raz2\"\n}",
                'U'+chr(0) + chr(0) + chr(52) + chr(4) + chr(4) + chr(4) + " {\nusername:\"rez1\"\npassword:\"raz2\"\nemail:\"raz3\"\n}",
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
            if len(data) > 2 and (ord(data[2]) == 1 or ord(data[2]) == 0):
                data = list(data)
                data[2] = chr(ord(data[2])+48)
                data = "".join(data)
            print("Server Says:" + data)
    except Exception as e:
        print("the error is:")
        print(e)



if __name__ == '__main__':
    main()

