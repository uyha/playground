const S = struct {
    const a: S = .{};
};

fn f(ptr: *const S) void {
    std.debug.print("{*}\n", .{ptr});
}
pub fn main() !void {
    f(&S.a);
    f(&.a);
}

const std = @import("std");
const Allocator = std.mem.Allocator;
