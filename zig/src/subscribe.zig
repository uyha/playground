pub fn main() !void {
    var context: *zimq.Context = try .init();
    defer context.deinit();

    var socket: *zimq.Socket = try .init(context, .sub);
    defer socket.deinit();

    try socket.set(.subscribe, "");
    try socket.connect("ipc://greeting");

    var message: zimq.Message = .empty();

    while (true) {
        _ = try socket.recvMsg(&message, .{});
        std.debug.print("{s}\n", .{message.slice().?});
    }
}

const zimq = @import("zimq");
const std = @import("std");
