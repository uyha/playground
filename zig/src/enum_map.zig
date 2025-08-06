pub fn main() !void {
    const map: std.EnumArray(enum { foo, bar }, []const u8) = .init(.{
        .foo = @embedFile("2d.zig"),
        .bar = @embedFile("2d.zig"),
    });
    std.debug.print("{s}\n", .{map.get(.foo)});
}

const std = @import("std");
