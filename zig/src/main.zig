fn Wrap(T: type) type {
    return struct {
        fn wtf(self: Wrap(T)) void {
            std.debug.print("{}\n", .{self});
        }
    };
}
pub fn main() !void {
    const wtf: Wrap(u8) = .{};
    wtf.wtf();
}

const std = @import("std");
