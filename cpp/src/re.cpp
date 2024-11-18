#include <fmt/core.h>
#include <re2/re2.h>

auto default_options() -> re2::RE2::Options {
  auto options = re2::RE2::Options{};
  options.set_posix_syntax(true);
  options.set_one_line(true);

  return options;
}

static auto options = default_options();

static auto ok        = RE2{"^OK[\r\n]+$"};
static auto error     = RE2{"^ERROR[\r\n]+$"};
static auto cme_error = RE2{"^\\+CME ERROR:.*[\r\n]+$"};
static auto cms_error = RE2{"^\\+CMS ERROR:.*[\r\n]+$"};

auto escape(std::string_view source) -> std::string {
  auto result = std::string{source};

  while (true) {
    auto pos = result.find('\r');
    if (pos == std::string::npos) {
      break;
    }

    result.replace(pos, 1, "\\r");
  }

  while (true) {
    auto pos = result.find('\n');
    if (pos == std::string::npos) {
      break;
    }

    result.replace(pos, 1, "\\n");
  }

  return result;
}

int main() {
  using namespace std::string_view_literals;

  for (auto text : {
           "OK\r"sv,
           "OK\n"sv,
           "OK\r\n"sv,
           "OK\n\r"sv,
       }) {
    fmt::print("{}: {}\n", escape(text), re2::RE2::FullMatch(text, ok));
  }
  for (auto text : {
           "ERROR\r"sv,
           "ERROR\n"sv,
           "ERROR\r\n"sv,
           "ERROR\n\r"sv,
       }) {
    fmt::print("{}: {}\n", escape(text), re2::RE2::FullMatch(text, error));
  }

  for (auto text : {
           "+CME ERROR: 123\r"sv,
           "+CME ERROR: 123\n"sv,
           "+CME ERROR: 123\r\n"sv,
           "+CME ERROR: 123\n\r"sv,
       }) {
    fmt::print("{}: {}\n", escape(text), re2::RE2::FullMatch(text, cme_error));
  }

  auto text = "+CPIN: SIM PIN\r\nOK\r\n";
  auto sub  = std::string_view{text + 16};
  fmt::print("{}: {}\n", escape(text), re2::RE2::FullMatch(text, ok));
  fmt::print("{}: {}\n", escape(sub), re2::RE2::FullMatch(sub, ok));

  static auto cpin = RE2{"^\\+CPIN:.*[\r\n]", default_options()};
  fmt::print("{}\n", re2::RE2::FullMatch("+CPIN: asdfasdf\r\nasdf\r\n", cpin));

  {
    int i0;
    int i1;
    int i2;
    int i3;
    auto pattern = re2::RE2{R"(\+SPIC:\s*(\d+),(\d+),(\d+),(\d+))"};
    fmt::print("{}\n", re2::RE2::FullMatch("+SPIC: 3,10,0,10", pattern, &i0, &i1, &i2, &i3));
  }

  {
    auto lac     = std::string_view{};
    auto cell_id = std::string_view{};
    auto pattern = re2::RE2{R"re(\+CREG: \d+,\d+,"(.{4})","(.{2}|.{4})")re"};
    fmt::print("{}\n", re2::RE2::FullMatch(R"(+CREG: 0,1,"1A2B","03")", pattern, &lac, &cell_id));
    fmt::print("{} {}\n", lac, cell_id);
  }
}
