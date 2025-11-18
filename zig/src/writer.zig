pub fn main() !void {
    var allocator: std.heap.DebugAllocator(.{}) = .init;
    defer _ = allocator.deinit();

    const gpa = allocator.allocator();

    var allocating: std.Io.Writer.Allocating = .init(gpa);
    defer allocating.deinit();

    const writer: *std.Io.Writer = &allocating.writer;

    try writer.print("{s}\n", .{"hello"});

    std.debug.print("{}\n", .{allocating.written().len});
}

const std = @import("std");
