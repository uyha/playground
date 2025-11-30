fn juicyMain(gpa: Allocator, io: Io) !void {
    _ = &gpa;
    _ = &io;
}

pub fn main() !void {
    var allocator: std.heap.DebugAllocator(.{}) = .init;
    defer _ = allocator.deinit();
    const gpa = allocator.allocator();

    var runtime: std.Io.Threaded = .init_single_threaded;
    defer runtime.deinit();

    try juicyMain(gpa, runtime.io());

    std.debug.print("{}\n", .{@sizeOf(packed struct { u4, u4 })});
}

const std = @import("std");
const Allocator = std.mem.Allocator;
const Io = std.Io;
const Clock = Io.Clock;
