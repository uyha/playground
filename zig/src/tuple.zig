pub fn main() !void {
    const a = .{1};
    std.debug.print("{}\n", .{a});
    std.debug.print("{}\n", .{a.@"0"});
}

const std = @import("std");
