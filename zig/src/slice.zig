const std = @import("std");

fn mod(slice: *[]u8) void {
    slice.ptr = undefined;
    slice.len = 0;
}
pub fn main() void {
    var a: [10]u8 = .{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    var b: []u8 = &a;
    std.debug.print("{any}\n", .{b});
    mod(&b);
    std.debug.print("{any}\n", .{b});

    const c = comptime c: {
        const d = [_]u8{ 1, 2, 3, 4, 5, 6 };
        var c: []const u8 = &d;
        c = c ++ c;
        break :c c;
    };

    std.debug.print("{any}\n", .{c});

    const str: [2:0]u8 = .{ 1, 2 };
    const slice: []const u8 = &str;
    std.debug.print("{any}\n", .{str});
    std.debug.print("{any}\n", .{slice});
}
