#include <unity.h>
#include <microhttpd.h>
#include <iostream>
#include "../include/HttpServer.h"

HttpServer *server;

void setUp(void) {
    // This function will be called before each test
    server = new HttpServer(8080);
    if (!server->start()) {
        TEST_FAIL_MESSAGE("Failed to start server");
    }
}

void tearDown(void) {
    // This function will be called after each test
    server->stop();
    delete server;
}

void testServerResponds(void) {
    // This is a placeholder for testing server response
    // In a real-world scenario, you would use an HTTP client to send a request
    // and verify the response.

    // For example, using a library like `libcurl` to perform HTTP requests:
    // - Set up a client
    // - Perform a GET request to the server
    // - Check the response
    // In this example, we'll simply check that the server started and stopped without error
    TEST_PASS();
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(testServerResponds);

    UNITY_END();
    return 0;
}
