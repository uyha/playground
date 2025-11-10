const A = struct {
    field: []const []const u8,
};
pub fn main() !void {
    const clock = std.Io.Clock;

    var threaded: std.Io.Threaded = .init_single_threaded;
    const io: std.Io = threaded.io();

    const now = try clock.real.now(io);
    const seed: u64 = @intCast(now.nanoseconds & ((1 << 64) - 1));
    var engine: std.Random.DefaultPrng = .init(seed);
    const random: std.Random = engine.random();
    const array = [_]u8{ random.int(u8), random.int(u8) };

    const result = for (array) |value| {
        if (value % 2 == 0) break value;
    } else null;

    std.debug.print("{any}\n", .{result});
}

const std = @import("std");
