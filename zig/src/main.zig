const ComptimeField = struct {
    comptime value: u8 = 1,
};

fn slice(_: []const i32) void {}

pub fn main() !void {
    const a: ?i32 = 1;
    std.debug.print("{}\n", .{&a});
    if ((&a).*) |*ptr| {
        std.debug.print("{}\n", .{ptr});
    }
}

const std = @import("std");
