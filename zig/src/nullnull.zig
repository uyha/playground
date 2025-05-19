pub fn main() !void {
    var value: ??u8 = null;

    std.debug.print("{}\n", .{value == null});
    value = @as(?u8, null);
    std.debug.print("{}\n", .{value != null});
    value = 1;
    std.debug.print("{}\n", .{value == 1});
}

const std = @import("std");
