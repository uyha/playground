const std = @import("std");

pub fn main() !void {
    var a: u16 = 0xAA_BB;
    var sa: []u8 = undefined;
    sa.ptr = @ptrCast(&a);
    sa.len = @sizeOf(@TypeOf(a));
    std.mem.reverse(u8, sa);
    std.debug.print("0x{X}\n", .{a});
}
