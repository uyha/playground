pub fn main() !void {
    var engine = std.Random.DefaultPrng.init(0);
    const eh: u8 = @as(u8, switch (engine.random().int(u8)) {
        1 => 2,
        else => 3,
    }) + 1;
    _ = eh;
}

const std = @import("std");
