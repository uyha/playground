const A = blk: {
    const First = @typeInfo(
        struct { a: u8 },
    ).@"struct";

    const Second = @typeInfo(
        struct { b: u8 },
    ).@"struct";

    const names, const types, const attrs = fieldtup(First.fields ++ Second.fields);

    break :blk @Struct(.auto, null, &names, &types, &attrs);
};
pub fn main() void {
    const a: A = .{ .a = 1, .b = 1 };
    _ = &a;
    std.debug.print("{any}\n", .{a});
}

const std = @import("std");
const fieldtup = @import("utils.zig").fieldtup;
