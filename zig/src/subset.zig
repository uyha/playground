pub fn Subset(comptime Root: type, comptime elements: anytype) type {
    var fields: [elements.len]std.builtin.Type.EnumField = undefined;

    blk: inline for (elements, 0..) |element, i| {
        if (@typeInfo(@TypeOf(element)) != .enum_literal) {
            @compileError("Enum literal expected");
        }

        inline for (std.meta.tags(Root)) |tag| {
            if (std.mem.eql(u8, @tagName(tag), @tagName(element))) {
                fields[i] = .{
                    .name = @tagName(tag),
                    .value = @intFromEnum(tag),
                };
                continue :blk;
            }
        }
        unreachable;
    }

    const root = @typeInfo(Root).@"enum";
    return @Type(std.builtin.Type{ .@"enum" = .{
        .tag_type = root.tag_type,
        .fields = &fields,
        .decls = &.{},
        .is_exhaustive = root.is_exhaustive,
    } });
}
pub fn main() !void {
    const E = enum { a, b, c };
    const s: Subset(E, .{ .a, .c }) = .c;

    const c: E = @enumFromInt(@intFromEnum(s));
    std.debug.print("{}\n", .{c});
}

const std = @import("std");
