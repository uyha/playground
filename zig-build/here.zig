const std = @import("std");
const zmq = @import("zmq");

pub fn main() void {
    var buff: [255]u8 = undefined;
    const context = zmq.zmq_ctx_new();
    const socket = zmq.zmq_socket(context, zmq.ZMQ_PULL);
    _ = zmq.zmq_bind(socket, "ipc:///tmp/tententen");
    const received: u32 = @intCast(zmq.zmq_recv(socket, &buff, buff.len, 0));
    std.debug.print("{s}\n", .{buff[0..received]});
}
