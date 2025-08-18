pub fn main() void {
    while (true) : ({
        std.debug.print("{s}:{} ({s})\n", .{ @src().file, @src().line, @src().fn_name });
        break;
    }) {
        defer std.debug.print("{s}:{} ({s})\n", .{ @src().file, @src().line, @src().fn_name });
        std.debug.print("{s}:{} ({s})\n", .{ @src().file, @src().line, @src().fn_name });
    }
}

const std = @import("std");
