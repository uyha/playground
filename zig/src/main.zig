const ComptimeField = struct {
    comptime value: u8 = 1,
};

fn slice(_: []const i32) void {}

fn throw(err: type, e: ?err) err!void {
    return e orelse {};
}

pub fn main() !void {
    ({
        errdefer |e| {
            std.debug.print("{s}:{} ({s}) {}\n", .{ @src().file, @src().line, @src().fn_name, e });
        }

        return error.WTF;
    }) catch |e| {
        std.debug.print("{}\n", .{e});
    };
}

const std = @import("std");
