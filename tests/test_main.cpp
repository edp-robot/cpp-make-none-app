#include "../include/HttpServer.h"
#include <cassert>
#include <iostream>

// Function for testing server start
void TestServerStart(HttpServer& server) {
    assert(server.start());
    std::cout << "Test 1 - Server start - PASSED" << std::endl;
}

// Function for testing server stop
void TestServerStop(HttpServer& server) {
    server.stop();
    assert(!server.isRunning());
    std::cout << "Test 2 - Server stop - PASSED" << std::endl;
}

// New test: Function to check that the server returns the correct port
void TestServerGetPort(HttpServer& server, unsigned short expectedPort) {
    assert(server.getPort() == expectedPort);
    std::cout << "Test 3 - Get Server Port - PASSED" << std::endl;
}

int main() {
    const unsigned short testPort = 8080;
    HttpServer server(testPort); // Assume that 8080 is the test port

    TestServerStart(server);      // Execute start test
    TestServerGetPort(server, testPort); // Execute get port test
    TestServerStop(server);       // Execute stop test

    return 0;
}
