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
