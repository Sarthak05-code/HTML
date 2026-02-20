import socket

HEADER = 64
PORT = 5050
FORMAT = "utf-8"
DISCONNECT_MESSAGE = "Disconnected!"
SERVER = socket.gethostbyname(socket.gethostname())
ADDRESS = (SERVER  , PORT)
CLIENT = socket.socket(socket.AF_INET , socket.SOCK_STREAM)

CLIENT.connect(ADDRESS)

def messages(msg):
    message  = msg.encode(FORMAT)
    msg_length = len(message)

    send_length = str(msg_length).encode(FORMAT)
    send_length += b' ' * (HEADER - len(send_length))
    CLIENT.send(send_length)
    CLIENT.send(message)
    print(CLIENT.recv(2048).decode(FORMAT))

messages("Hello World")

messages(DISCONNECT_MESSAGE)