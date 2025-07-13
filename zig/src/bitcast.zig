const Binary = packed struct(u24) {
    @"0": u16,
    @"1": u8,
};

pub fn main() !void {
    const buffer = [_]u8{ 0x12, 0x34, 0x56, 0x78, 0x9A };
    const slice = buffer[1..4];

    std.debug.print("{}\n", .{@as(Binary, @bitCast(slice.*))});
}

const std = @import("std");
