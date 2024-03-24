const std = @import("std");
const print = std.debug.print;

fn aFunction() void {}

pub fn main() !void {
    comptime var fn_type = @typeInfo(@TypeOf([_]i32{}));
    print("{any}", .{fn_type.Array});
}
