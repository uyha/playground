const A = struct {
    a: u32,
    pub fn aaa(self: A) u32 {
        return self.a;
    }
};
const B = packed struct {
    a: A,
};

const C = blk: {
    const info = @typeInfo(A).@"struct";

    break :blk @Struct(
        .auto,
        null,
        info.field_names,
        info.field_types[0..],
        info.field_attrs[0..],
    );
};

pub fn main() void {
    std.debug.print("{}\n", .{A == C});
}

const std = @import("std");
