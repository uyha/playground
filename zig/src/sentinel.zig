const std = @import("std");

pub fn main() void {
    const MyStruct = packed struct { a: u1 };

    const array = [1:.{ .a = 0 }]MyStruct{.{
        .a = 1,
    }};

    std.debug.print("{any}\n", .{array});
}
