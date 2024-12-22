const std = @import("std");

pub fn main() !void {
    struct {
        fn lambda() void {
            return std.debug.print("hello", .{});
        }
    }.lambda();
}
