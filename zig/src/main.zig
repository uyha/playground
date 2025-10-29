fn bad() []u8 {
    var data: [8]u8 = @splat(1);
    return &data;
}

const A = packed union {
    a: u6,
    b: f32,
};

fn rangeArrayLen(
    comptime start: usize,
    comptime end: usize,
    comptime step: usize,
) usize {
    return (end - start) / step + if ((end - start) % step > 0) 1 else 0;
}
fn rangeArray(
    comptime start: usize,
    comptime end: usize,
    comptime step: usize,
) [rangeArrayLen(start, end, step)]usize {
    var result: [rangeArrayLen(start, end, step)]usize = undefined;
    var current = start;

    for (0..result.len) |i| {
        result[i] = current;
        current += step;
    }

    return result;
}

pub fn main() !void {
    std.debug.print("{any}\n", .{rangeArray(0, 11, 2)});
}

const std = @import("std");
