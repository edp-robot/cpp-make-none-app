#include "../../cache/Unity/src/unity.h"
#include "../include/HttpServer.h"
#include "../../cache/microhttpd/include/microhttpd.h"

void setUp(void) {
    // Set up code, runs before every test
}

void tearDown(void) {
    // Tear down code, runs after every test
}

void test_HttpServer_StartAndStop(void) {
    HttpServer server(8080);
    TEST_ASSERT_TRUE(server.start());
    server.stop();
}

void test_HttpServer_HandleRequest(void) {
    HttpServer server(8080);

    // Start the server to initialize the daemon
    server.start();

    struct MHD_Connection *connection = NULL;
    const char *url = "/";
    const char *method = "GET";
    const char *version = "HTTP/1.1";
    const char *upload_data = NULL;
    size_t upload_data_size = 0;
    void *con_cls = NULL;

    enum MHD_Result result = server.handleRequest(NULL, connection, url, method, version, upload_data, &upload_data_size, &con_cls);
    TEST_ASSERT_EQUAL(MHD_NO, result);

    // Stop the server after the test
    server.stop();
}

void test_HttpServer_InvalidPort(void) {
    HttpServer server(0);  // Invalid port
    TEST_ASSERT_FALSE(server.start());
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_HttpServer_StartAndStop);
    RUN_TEST(test_HttpServer_HandleRequest);
    RUN_TEST(test_HttpServer_InvalidPort);

    return UNITY_END();
}
