const std = @import("std");

pub fn main() void {
    const Data = union(enum) {
        int: i32,
        boolean: bool,
    };

    const data = Data{ .int = 1 };
    std.debug.print("{}\n", .{data});
    std.debug.print("{}\n", .{@intFromEnum(data)});
}
