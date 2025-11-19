pub fn main() !void {
    const clock = std.Io.Clock;

    var threaded: std.Io.Threaded = .init_single_threaded;
    const io: std.Io = threaded.io();

    const now = try clock.real.now(io);
    const seed: u64 = @intCast(now.nanoseconds & ((1 << 64) - 1));
    var engine: std.Random.DefaultPrng = .init(seed);
    const random: std.Random = engine.random();

    const a: u8 = @max(0, random.int(i8));
    std.debug.print("{} {}\n", .{ a, @TypeOf(@max(0, random.int(i8))) });
}

const std = @import("std");
