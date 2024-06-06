const std = @import("std");

pub fn main() !void {
    const va = blk: while (true) {
        break :blk 1;
    };
    std.debug.print("{}\n", .{va});
}
