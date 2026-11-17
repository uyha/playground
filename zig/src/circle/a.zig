pub fn main() void {
    std.debug.print("{}\n", .{B.b});
}

const std = @import("std");

pub const a: u8 = if (B.b == 1) 1 else 2;
const B = @import("B");
