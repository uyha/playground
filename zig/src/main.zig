fn bad() []u8 {
    var data: [8]u8 = @splat(1);
    return &data;
}

const A = packed union {
    a: u6,
    b: f32,
};

pub fn main() !void {
    const a: *const [0:0]u8 = "";
    std.debug.print("{s}\n", .{@typeName(@TypeOf(a))});
}

const std = @import("std");
