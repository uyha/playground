pub fn main() !void {
    const values = @Vector(3, u8){ 0x13, 0x15, 0x14 };
    std.debug.print(
        "0x{X:02}\n",
        .{values},
    );
}

const std = @import("std");
