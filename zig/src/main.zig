pub fn main() !void {
    std.debug.print("{}\n", .{@sizeOf([16]u2)});
}

const std = @import("std");
