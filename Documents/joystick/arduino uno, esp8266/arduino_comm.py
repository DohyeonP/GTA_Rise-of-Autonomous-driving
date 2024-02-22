import socket

# Server settings
host = '10.10.15.58'  # Your PC's IP address
port = 12345           # Choose a port number

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen(1)

print(f"Listening for connections on {host}:{port}...")

while True:
    client, address = server.accept()
    print(f"Connection from {address}")

    while True:
        data = client.recv(1024).decode()
        if not data:
            break  # No more data from client, close the connection

        print(f"Received data from ESP8266: {data}")
        # Process the received data as needed

    print("Client disconnected.")
    client.close()
