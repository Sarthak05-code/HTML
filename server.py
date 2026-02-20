import socket
import threading

HEADER = 64
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
FORMAT = "utf-8"
DISCONNECT_MESSAGE = "Disconnected!"

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)


def handle_client(connection, address):
    print(f"[New Connection] {address} connected")

    connected = True
    while connected:
        msg_length = connection.recv(HEADER).decode(FORMAT)

        if not msg_length:
            break

        msg_length = int(msg_length.strip())
        msg = connection.recv(msg_length).decode(FORMAT)

        if msg == DISCONNECT_MESSAGE:
            connected = False

        print(f"[{address}] : {msg}")
        connection.send("Message received. ".encode(FORMAT))

    connection.close()
    print(f"[Disconnected] {address}")


def start():
    server.listen()
    print(f"[Listening] Server is listening on {SERVER}")

    while True:
        connection, address = server.accept()
        thread = threading.Thread(
            target=handle_client,
            args=(connection, address)
        )
        thread.start()

        print(f"[Active Connections] {threading.active_count() - 1}")


print("Starting server...")
start()
