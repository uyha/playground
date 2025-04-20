const std = @import("std");
const A = blk: {
    const First = @typeInfo(
        struct { a: u8 },
    ).@"struct";

    const Second = @typeInfo(
        struct { b: u8 },
    ).@"struct";

    _ = &First;
    _ = &Second;

    break :blk @Type(std.builtin.Type{
        .@"struct" = .{
            .layout = .auto,
            .fields = First.fields ++ Second.fields,
            .decls = First.decls ++ Second.decls,
            .is_tuple = false,
        },
    });
};
pub fn main() void {
    const a: A = .{ .a = 1, .b = 1 };
    _ = &a;
    std.debug.print("{any}\n", .{a});
}
