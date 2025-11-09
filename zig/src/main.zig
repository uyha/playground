const A = struct {
    field: []const []const u8,
};
pub fn main() !void {
    const a: [3][]const u8 = @import("res").field;
    std.debug.print("{any}\n", .{a});
}

const std = @import("std");
