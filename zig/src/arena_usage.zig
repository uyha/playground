const std = @import("std");
const assert = std.debug.assert;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer assert(!gpa.detectLeaks());

    const arena = std.heap.ArenaAllocator.init(gpa.allocator());

    var copy_arena = arena;
    defer copy_arena.deinit();

    var list = std.ArrayList(u8).init(copy_arena.allocator());
    try list.append(1);
}
