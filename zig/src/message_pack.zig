pub fn main() !void {
    const allocator = std.heap.page_allocator;

    var allocWriter: std.Io.Writer.Allocating = .init(allocator);
    defer allocWriter.deinit();

    const writer: *std.Io.Writer = &allocWriter.writer;

    try mzg.pack(
        "a string with some characters for demonstration purpose",
        writer,
    );

    var string: []const u8 = undefined;
    const size = try mzg.unpack(writer.buffer[0..writer.end], &string);
    std.debug.print("Consumed {} bytes\n", .{size});
    std.debug.print("string: {s}\n", .{string});
}

const std = @import("std");
const mzg = @import("mzg");
