#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

using namespace std;

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    string request(buffer);
    string file_path = "www/index.html"; // Default file

    if (request.find("GET /") == 0) {
        size_t start = 5; // Skip "GET /"
        size_t end = request.find(' ', start);
        file_path = "www" + request.substr(start, end - start);
        if (file_path.back() == '/') {
            file_path += "index.html"; // Default to index.html
        }
    }

    ifstream file(file_path);
    stringstream buffer_stream;

    if (file.is_open()) {
        buffer_stream << file.rdbuf();
        string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer_stream.str();
        send(client_socket, response.c_str(), response.size(), 0);
    } else {
        string not_found = "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n<h1>404 Not Found</h1>";
        send(client_socket, not_found.c_str(), not_found.size(), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        thread client_thread(handle_client, client_socket);
        client_thread.detach();
    }

    return 0;
}
