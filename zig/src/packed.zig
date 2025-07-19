pub fn main() !void {
    const a: Packed = @bitCast(@as(u32, 1));
    std.debug.print("{}\n", .{a});
}

const Child = packed struct(u32) {
    value: i2,
    e: enum(i3) { a, b, c },
    _1: u27,
};
const Packed = packed struct {
    child: Child,
};

const std = @import("std");
