const some = @embedFile("some");

pub fn main() !void {
    std.debug.print("{s}\n", .{some});
}

const std = @import("std");
