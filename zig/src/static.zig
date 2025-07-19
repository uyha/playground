fn counter() u64 {
    const static = struct {
        var counter: u64 = 0;
    };
    defer static.counter += 1;
    return static.counter;
}

pub fn main() !void {
    std.debug.print("{}\n", .{counter()});
    std.debug.print("{}\n", .{counter()});
    std.debug.print("{}\n", .{counter()});
}

const std = @import("std");
