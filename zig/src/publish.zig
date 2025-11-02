pub fn main() !void {
    var thread: std.Io.Threaded = .init_single_threaded;
    const io: std.Io = thread.io();

    var context: *zimq.Context = try .init();
    defer context.deinit();

    try context.set(.blocky, false);

    var socket: *zimq.Socket = try .init(context, .@"pub");
    defer socket.deinit();

    try socket.set(.linger, 0);

    try socket.bind("ipc://greeting");
    try io.sleep(.fromSeconds(1), .awake);
    defer socket.sendConstSlice("die", .{}) catch {};

    try socket.sendConstSlice("hello", .{});

    try socket.sendConstSlice("goodbye", .{});
    try socket.sendConstSlice("goodbye", .{});
}

const zimq = @import("zimq");
const std = @import("std");
const Io = std.Io;
