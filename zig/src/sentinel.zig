const std = @import("std");

pub fn main() void {
    const MyStruct = struct {};

    const array = [1:MyStruct{}]MyStruct{MyStruct{}};

    std.debug.print("{any}\n", .{array});
}
