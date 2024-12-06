const std = @import("std");

pub fn main() void {
    @import("shared_var_comptime.zig").a = 2;

    std.debug.print("{} {}\n", .{ @import("shared_var_comptime.zig").a, .use_shared_var });
}
