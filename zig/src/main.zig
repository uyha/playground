fn juicyMain(gpa: Allocator, io: Io) !void {
    _ = &gpa;
    _ = &io;

    std.debug.print("{}\n", .{&false});
    std.debug.print("{}\n", .{&true});
    std.debug.print("{}\n", .{&@as(u8, 1)});
}

pub fn main() !void {
    var allocator: std.heap.DebugAllocator(.{}) = .init;
    defer _ = allocator.deinit();
    const gpa = allocator.allocator();

    var runtime: std.Io.Threaded = .init_single_threaded;
    defer runtime.deinit();

    try juicyMain(gpa, runtime.io());
}

const std = @import("std");
const Allocator = std.mem.Allocator;
const Io = std.Io;
const Clock = Io.Clock;
