fn f(a: u32, b: u32) void {
    std.debug.print("{} {}\n", .{ a, b });
}

pub fn main() !void {
    var a: u32 = 0;

    f(a: {
        a += 1;
        break :a a;
    }, b: {
        a += 1;
        break :b a;
    });
}

const std = @import("std");
