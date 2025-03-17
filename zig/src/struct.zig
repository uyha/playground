const std = @import("std");
pub fn main() void {
    std.debug.print("{any}\n", .{
        .{ .adsf = 1 } ++ .{ .zcx = 1 },
    });
}
