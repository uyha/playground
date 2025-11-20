fn juicyMain(gpa: Allocator, io: Io) !void {
    _ = &gpa;
    const now = try Clock.real.now(io);
    std.debug.print("{}\n", .{now});
}

pub fn main() !void {
    var allocator: std.heap.DebugAllocator(.{}) = .init;
    defer _ = allocator.deinit();
    const gpa = allocator.allocator();

    var runtime: std.Io.Threaded = .init(gpa);
    defer runtime.deinit();

    try juicyMain(gpa, runtime.io());
}

const std = @import("std");
const Allocator = std.mem.Allocator;
const Io = std.Io;
const Clock = Io.Clock;
