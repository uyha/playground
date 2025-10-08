#include <cstddef>
#include <cstdint>
#include <fmt/format.h>

using u8    = std::uint8_t;
using u16   = std::uint16_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using usize = std::size_t;

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using byte = std::byte;

using f32 = float;
using f64 = double;

using namespace fmt;

struct CanBitTiming {
  enum class SilentMode : u8 { normal = 0, silent = 1 };
  enum class LoopBackMode : u8 { disabled = 0, enabled = 1 };
  enum class SynchronizationJumpWidth : u8 { n1 = 0, n2 = 1, n3 = 2, n4 = 3 };

  SilentMode silent_mode                              = SilentMode::normal;
  LoopBackMode loop_back_mdoe                         = LoopBackMode::disabled;
  SynchronizationJumpWidth synchronization_jump_width = SynchronizationJumpWidth::n1;

  /**
   * The clock frequency of APB1
   */
  u32 clock_frequency;
  /**
   * The bitrate of the CAN bus
   */
  u32 bitrate;
  /**
   * The sampling point (87.5% should passed as 0.875).
   */
  f32 sampling = 0.875;
  /**
   * The prescaler value (see formula 1).
   */
  u8 prescaler;

  /**
   * Calculate the bit timing value (bit 0 - 22 of CAN_BTR)
   *
   * The formula for time segment 1 and 2 (`ts1` and `ts2`)
   *
   * (1) `tq` = `prescaler` / `clock_frequency`
   *
   * (2) `ts1` = `bs1` * `tq`
   *
   * (3) `ts2` = `bs2` * `tq`
   *
   * (4) `bitrate` = 1 / (`tq` + `ts1` + `ts2`)
   *
   * (5) `sampling` = `ts1` / (`ts1` + `ts2`)
   *
   * @return a timing value that can be assigned to CAN_BTR.
   */
  constexpr auto calculate() -> u32 {
    auto const tq  = float(prescaler) / clock_frequency;
    auto const ts1 = static_cast<u8>(sampling / (bitrate * tq) - 1);
    auto const ts2 = static_cast<u8>(1 / (bitrate * tq)) - 1 - ts1;

    return (static_cast<u8>(silent_mode) << 31)                //
         | (static_cast<u8>(loop_back_mdoe) << 30)             //
         | (static_cast<u8>(synchronization_jump_width) << 24) //
         | (ts2 << 20)                                         //
         | (ts1 << 16)                                         //
         | prescaler;
  }
};

int main() {
  print("{:08x}\n",
        CanBitTiming{
            .clock_frequency = 32'000'000,
            .bitrate         = 1'000'000,
            .prescaler       = 4,
        }
            .calculate());
}
