pub fn main() !void {
    var context: *zimq.Context = try .init();
    defer context.deinit();

    try context.set(.blocky, false);

    var socket: *zimq.Socket = try .init(context, .@"pub");
    defer socket.deinit();

    try socket.set(.linger, 0);

    try socket.bind("ipc://greeting");
    std.Thread.sleep(1 * std.time.ns_per_s);
    defer socket.sendConstSlice("die", .{}) catch {};

    try socket.sendConstSlice("hello", .{});

    try socket.sendConstSlice("goodbye", .{});
    try socket.sendConstSlice("goodbye", .{});
}

const zimq = @import("zimq");
const std = @import("std");
