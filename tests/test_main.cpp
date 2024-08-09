#include "../include/HttpServer.h"
#include <cassert>
#include <iostream>

// Функция для тестирования запуска сервера
void TestServerStart(HttpServer& server) {
    assert(server.start());
    std::cout << "Test 1 - Server start - PASSED" << std::endl;
}

// Функция для тестирования остановки сервера
void TestServerStop(HttpServer& server) {
    server.stop();
    assert(!server.isRunning());
    std::cout << "Test 2 - Server stop - PASSED" << std::endl;
}

// Новый тест: Функция для проверки, что сервер возвращает корректный порт
void TestServerGetPort(HttpServer& server, unsigned short expectedPort) {
    assert(server.getPort() == expectedPort);
    std::cout << "Test 3 - Get Server Port - PASSED" << std::endl;
}

int main() {
    const unsigned short testPort = 8080;
    HttpServer server(testPort); // Предполагаем, что 8080 - это тестовый порт

    TestServerStart(server);      // Выполнение теста запуска
    TestServerGetPort(server, testPort); // Выполнение теста получения порта
    TestServerStop(server);       // Выполнение теста остановки

    return 0;
}
