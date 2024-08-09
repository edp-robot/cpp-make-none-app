#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <microhttpd.h>
#include <string>

class HttpServer {
public:
    explicit HttpServer(unsigned short port);
    ~HttpServer();

    bool start();
    void stop();

private:
    struct MHD_Daemon *daemon = nullptr;
    unsigned short port;

    static enum MHD_Result handleRequest(void *cls, struct MHD_Connection *connection,
                                         const char *url, const char *method,
                                         const char *version, const char *upload_data,
                                         size_t *upload_data_size, void **con_cls);
};

#endif // HTTPSERVER_H
