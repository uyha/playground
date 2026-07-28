pub fn main(init: Init) !void {
    try std.Io.File.stdout().writeStreamingAll(init.io, "Hello, World!\n");

    var random = std.Random.DefaultPrng.init(
        @bitCast(std.Io.Clock.boot.now(init.io).toMicroseconds()),
    );
    const rng = random.random();

    var a: u8 = 0;
    var b: u8 = 0;

    (&(if (rng.boolean()) a else b)).* += 1;
    std.debug.print("{} {}\n", .{ a, b });
}

const std = @import("std");
const Allocator = std.mem.Allocator;
const Io = std.Io;
const Clock = Io.Clock;
const Init = std.process.Init;
