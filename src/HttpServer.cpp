#include "HttpServer.h"
#include <cstring>

HttpServer::HttpServer(unsigned short port) : daemon(nullptr), port(port) {}

HttpServer::~HttpServer() {
    stop();
}

bool HttpServer::start() {
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, port, NULL, NULL,
                              &HttpServer::handleRequest, NULL, MHD_OPTION_END);
    return daemon != nullptr;
}

void HttpServer::stop() {
    if (daemon) {
        MHD_stop_daemon(daemon);
        daemon = nullptr;
    }
}

enum MHD_Result HttpServer::handleRequest(void *cls, struct MHD_Connection *connection,
                                          const char *url, const char *method,
                                          const char *version, const char *upload_data,
                                          size_t *upload_data_size, void **con_cls) {
    const char *page = "Hello, World!";
    struct MHD_Response *response = MHD_create_response_from_buffer(std::strlen(page),
                                                                    (void *)page, MHD_RESPMEM_PERSISTENT);
    enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}
