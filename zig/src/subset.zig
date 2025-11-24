pub fn Subset(comptime Root: type, comptime elements: anytype) type {
    const root = @typeInfo(Root).@"enum";

    var names: [elements.len][]const u8 = undefined;
    var values: [elements.len]root.tag_type = undefined;

    var fields: usize = 0;
    blk: inline for (elements) |element| {
        if (@typeInfo(@TypeOf(element)) != .enum_literal) {
            @compileError("Enum literal expected");
        }

        inline for (std.meta.tags(Root)) |tag| {
            if (std.mem.eql(u8, @tagName(tag), @tagName(element))) {
                names[fields] = @tagName(tag);
                values[fields] = @intFromEnum(tag);
                fields += 1;
                continue :blk;
            }
        }
        unreachable;
    }

    return @Enum(
        root.tag_type,
        .exhaustive,
        names[0..fields],
        values[0..fields],
    );
}
pub fn main() !void {
    const E = enum { a, b, c };
    const s: Subset(E, .{ .a, .c }) = .c;

    const c: E = @enumFromInt(@intFromEnum(s));
    std.debug.print("{}\n", .{c});
}

const std = @import("std");
