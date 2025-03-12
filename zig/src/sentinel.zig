const std = @import("std");

pub fn main() void {
    const MyStruct = packed struct { a: i1 };

    const array = [1:.{ .a = 0 }]MyStruct{.{
        .a = -1,
    }};

    std.debug.print("{any}\n", .{array});
}
