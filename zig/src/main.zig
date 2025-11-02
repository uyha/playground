const ComptimeField = struct {
    comptime value: u8 = 1,
};
pub fn main() !void {
    var a: ComptimeField = .{};
    _ = &a;
    std.debug.print("{} {}\n", .{ @sizeOf([*]u8), @sizeOf(usize) });
}

const std = @import("std");
