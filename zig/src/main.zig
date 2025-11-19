pub fn main() !void {
    const clock = std.Io.Clock;

    var threaded: std.Io.Threaded = .init_single_threaded;
    const io: std.Io = threaded.io();

    const now = try clock.real.now(io);
    std.debug.print("{}\n", .{now});
}

const std = @import("std");
