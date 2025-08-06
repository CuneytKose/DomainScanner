#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>

void scan_port(const std::string& host, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return;

    struct hostent* server = gethostbyname(host.c_str());
    if (server == NULL) {
        close(sockfd);
        return;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr = *((struct in_addr*)server->h_addr);
    memset(&(serv_addr.sin_zero), 0, 8);

    struct timeval tv;
    tv.tv_sec = 1; // timeout
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == 0) {
        std::cout << "[+] Port " << port << " is OPEN on " << host << std::endl;
    }

    close(sockfd);
}

int main() {
    std::string domain;
    int start_port, end_port;

    std::cout << "Domain: ";
    std::cin >> domain;
    std::cout << "Start port: ";
    std::cin >> start_port;
    std::cout << "End port: ";
    std::cin >> end_port;

    std::vector<std::thread> threads;
    for (int port = start_port; port <= end_port; ++port) {
        threads.emplace_back(scan_port, domain, port);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
