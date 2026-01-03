fn juicyMain(gpa: Allocator, io: Io) !void {
    _ = &io;

    var allocating: std.Io.Writer.Allocating = .init(gpa);
    defer allocating.deinit();

    const writer: *std.Io.Writer = &allocating.writer;

    try writer.print("{s}\n", .{"hello"});

    std.debug.print("{}\n", .{allocating.written().len});
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
