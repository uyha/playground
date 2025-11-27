pub fn main() !void {
    var buffer: [255]u8 = undefined;
    const context: *zimq.Context = try .init();
    defer context.deinit();

    const socket: *zimq.Socket = try .init(context, .pull);
    defer socket.deinit();

    try socket.bind("ipc:///tmp/tententen");
    const received: usize = try socket.recv(&buffer, .{});

    std.debug.print("{s}\n", .{buffer[0..received]});
}

const std = @import("std");
const zimq = @import("zimq");
