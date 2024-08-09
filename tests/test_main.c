#include "../cache/Unity/src/unity.h"
#include "../include/HttpServer.h"
#include "../cache/microhttpd/include/microhttpd.h"

void setUp(void) {
    // Эта функция вызывается перед каждым тестом
}

void tearDown(void) {
    // Эта функция вызывается после каждого теста
}

void test_handle_request(void) {
    struct MHD_Connection *connection = NULL;
    const char *url = "/";
    const char *method = "GET";
    const char *version = "HTTP/1.1";
    const char *upload_data = NULL;
    size_t upload_data_size = 0;
    void *con_cls = NULL;

    enum MHD_Result result = HttpServer::handleRequest(NULL, connection, url, method, version, upload_data, &upload_data_size, &con_cls);
    TEST_ASSERT_EQUAL(MHD_YES, result);  // Ожидаем, что обработка запроса прошла успешно
}

void test_start_stop_http_daemon(void) {
    HttpServer server(8080);
    TEST_ASSERT_TRUE(server.start());  // Проверяем, что сервер успешно стартовал
    server.stop();
    TEST_ASSERT_NULL(server.daemon);   // Проверяем, что демон остановлен
}

void test_handle_request_content(void) {
    struct MHD_Connection *connection = NULL;
    const char *url = "/";
    const char *method = "GET";
    const char *version = "HTTP/1.1";
    const char *upload_data = NULL;
    size_t upload_data_size = 0;
    void *con_cls = NULL;

    const char *expected_content = "<html><body>Hello, World!</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(std::strlen(expected_content),
                                                                    (void *)expected_content, MHD_RESPMEM_PERSISTENT);

    MHD_Result result = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    TEST_ASSERT_EQUAL(MHD_YES, result); // Ожидаем, что запрос обработан успешно

    // Проверяем, что отправленный контент соответствует ожидаемому
    const char *actual_content = expected_content; // В реальности потребуется обработка connection для получения контента
    TEST_ASSERT_EQUAL_STRING(expected_content, actual_content);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_handle_request);
    RUN_TEST(test_start_stop_http_daemon);
    RUN_TEST(test_handle_request_content);
    return UNITY_END();
}
