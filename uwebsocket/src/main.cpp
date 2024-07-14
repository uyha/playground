#include <fmt/format.h>
#include <fmt/ranges.h>

#include <uWebSockets/App.h>

#include <thread>

int main() {
  auto app                          = uWS::App{};
  auto loop                         = uWS::Loop::get();
  us_listen_socket_t *listen_socket = nullptr;

  app.get("/hello",
          [](auto *res, auto *req) {
            fmt::print("{}:{} {}\n", __FILE__, __LINE__, *req);
            (void)::fflush(::stdout);
            res->end("Hello World");
          })
      .listen(8080, [&listen_socket](auto *socket) { listen_socket = socket; });

  auto close = std::jthread([&app, &loop] {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(2s);
    loop->defer([&app] { app.close(); });
  });

  app.run();

  fmt::print("{}:{}\n", __FILE__, __LINE__);
  (void)::fflush(::stdout);
}
