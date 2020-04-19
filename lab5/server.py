import socket
import select
import string

def broadcast_data (sock, message, sockets, server_socket):
# відсилає повідомлення message усім клієнтам приєднаним до чата
    for socket in sockets:
        if socket != server_socket and socket != sock:
            socket.send(message)


def main():
    CONNECTION_LIST=[]

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("127.0.0.1", 5000))
    server_socket.listen()

    CONNECTION_LIST.append(server_socket)

    print("TCP/IP Chat server.")

    while True:
        read_sockets, write_sockets, error_sockets = select.select(CONNECTION_LIST,[],[])

        for sock in read_sockets:

            if sock == server_socket:
                # Handle the case in which there is a new connection recieved
                # through server_socket
                sockfd, addr = server_socket.accept()
                CONNECTION_LIST.append(sockfd)
                print(f"Client ({addr}, {addr}) connected")
                broadcast_data(sockfd, f"Client ({addr}, {addr}) connected".encode("utf8"), CONNECTION_LIST, server_socket)

            else:
                # дані отримані від клієнтів (їх треба обробити)
                try:
                    data = sock.recv(4096)
                except:
                    broadcast_data(sock, f"Client ({addr}, {addr}) is offline".encode("utf8"), CONNECTION_LIST, server_socket)
                    print(f"Client ({addr}, {addr}) is offline")
                    sock.close()
                    CONNECTION_LIST.remove(sock)
                    continue

                if data:
                    # The client sends some valid data, process it
                    if data == "q" or data == "Q":
                        broadcast_data(sock, f"Client ({addr}, {addr}) quits".encode("utf8"), CONNECTION_LIST, server_socket)
                        print(f"Client ({addr}, {addr}) quits")
                        sock.close()
                        CONNECTION_LIST.remove(sock)
                    else:
                        broadcast_data(sock, data, CONNECTION_LIST, server_socket)

    server_socket.close()

if __name__ == "__main__":
    main()
