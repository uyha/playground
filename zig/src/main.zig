const Tup = struct { u8, u16, bool };
fn T(comptime index: usize) @TypeOf(@as(Tup, undefined)[index]) {
    return if (index != 2) 0 else false;
}
pub fn main() !void {
    std.debug.print("{}\n", .{T(2)});
    init();
}

pub extern fn init() void;

const std = @import("std");
const Allocator = std.mem.Allocator;
const Io = std.Io;
const Clock = Io.Clock;
const Init = std.process.Init;
