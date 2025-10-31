const ComptimeField = struct {
    comptime value: u8 = 1,
};
pub fn main() !void {
    var a: ComptimeField = .{};
    _ = &a;
    std.debug.print("{}\n", .{a});
}

const std = @import("std");
