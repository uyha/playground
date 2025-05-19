fn fun(a: anytype) void {
    std.debug.print("{any}\n", .{a});
}

pub fn main() !void {
    const map = .{
        .{ i8, &fun },
    };
    const v: i8 = 1;

    blk: {
        inline for (map) |entry| {
            const T, const function = entry;
            if (T == @TypeOf(v)) {
                function(v);
                break :blk;
            }
        }

        @compileError("No map found");
    }
}

const std = @import("std");
