#include "HttpServer.h"
#include <iostream>
#include <csignal>

volatile sig_atomic_t stop;

void handle_signal(int signal) {
    stop = 1;
}

int main() {
    HttpServer server(8080);
    if (!server.start()) {
        std::cerr << "Failed to start the server\n";
        return 1;
    }

    std::cout << "Server started on http://localhost:8080\n";
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    while (!stop) {
        // The server continues to run until it receives a stop signal
    }

    server.stop();
    std::cout << "Server stopped.\n";

    return 0;
}
