const std = @import("std");

fn mod(slice: *[]u8) void {
    slice.ptr = undefined;
    slice.len = 0;
}
pub fn main() void {
    var a: [10]u8 = .{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    var b: []u8 = &a;
    std.debug.print("{any}\n", .{b});
    mod(&b);
    std.debug.print("{any}\n", .{b});
}
