#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <csignal>
#include "../include/HttpServer.h"

// Мок класс для HttpServer
class MockHttpServer : public HttpServer {
public:
    MockHttpServer(int port) : HttpServer(port) {}
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};

volatile sig_atomic_t stop;

void handle_signal(int signal) {
    stop = 1;
}

class ServerTest : public ::testing::Test {
protected:
    MockHttpServer server;

    ServerTest() : server(8080) {}

    void SetUp() override {
        stop = 0;
    }
};

// Тестирование успешного запуска сервера
TEST_F(ServerTest, StartServer_Success) {
    EXPECT_CALL(server, start())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(server, stop())
        .Times(1);

    ASSERT_TRUE(server.start());

    // Симуляция работы сервера
    std::thread server_thread([this]() {
        while (!stop) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Снижение загрузки ЦП
        }
        server.stop();
    });

    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Подождать немного перед отправкой сигнала
    std::raise(SIGINT);

    server_thread.join(); // Дождаться завершения потока

    EXPECT_EQ(stop, 1); // Проверить, что сигнал был обработан
}

// Тестирование неудачного запуска сервера
TEST_F(ServerTest, StartServer_Failure) {
    EXPECT_CALL(server, start())
        .WillOnce(::testing::Return(false));

    ASSERT_FALSE(server.start());
    EXPECT_EQ(stop, 0); // Проверить, что stop не изменен
}

// Тестирование обработки сигнала
TEST_F(ServerTest, SignalHandling) {
    EXPECT_CALL(server, start())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(server, stop())
        .Times(1);

    ASSERT_TRUE(server.start());

    std::thread server_thread([this]() {
        while (!stop) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Снижение загрузки ЦП
        }
        server.stop();
    });

    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Подождать немного перед отправкой сигнала
    std::raise(SIGINT);

    server_thread.join(); // Дождаться завершения потока

    EXPECT_EQ(stop, 1); // Проверить, что сигнал был обработан
}
