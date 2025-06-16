fn array(arr: []const []const usize) void {
    for (arr) |first| {
        for (first) |second| {
            std.debug.print("{}\n", .{second});
        }
    }
}
pub fn main() !void {
    array(&.{
        &.{
            @as(usize, 1),
        },
        &.{
            @as(usize, 2),
        },
    });
}

const std = @import("std");
