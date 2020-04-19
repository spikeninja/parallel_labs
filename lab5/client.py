import socket
import threading
import sys

def recv_data():
    "Receive data from other clients connected to server"
    while True:
        try:
            recv_data = client_socket.recv(4096)
        except:
            #Handle the case when server process terminates
            print("Server closed connection, thread exiting.")
            #_thread.interrupt_main()
            break
        if not recv_data:
                # Recv with no data, server closed connection
                print("Server closed connection, thread exiting.")
                #_thread.interrupt_main()
                break
        else:
                print("Received data: "), recv_data

def send_data():
    while True:
        send_data = str(input("Enter data to send (q or Q to quit):"))
        if send_data == "q" or send_data == "Q":
            client_socket.send(send_data.encode("utf8"))
            #_thread.interrupt_main()
            break
        else:
            client_socket.send(send_data.encode("utf8"))

if __name__ == "__main__":

    print("========TCP/IP Chat client program========")
    print("Connecting to server at 127.0.0.1:5000")

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 5000))

    print("Connected to server at 127.0.0.1:5000")

    th1 = threading.Thread(target=recv_data,args=())
    th2 = threading.Thread(target=send_data,args=())

    th1.start()
    th2.start()

    try:
        while True:
            continue
    except:
        print("Client program quits....")
        client_socket.close()
