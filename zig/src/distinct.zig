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
    var info = @typeInfo(A);
    const fields = info.@"struct".fields;
    const names, const types, const attrs = fieldtup(fields);

    break :blk @Struct(.auto, null, &names, &types, &attrs);
};

pub fn main() void {
    std.debug.print("{}\n", .{A == C});
}

const std = @import("std");
const fieldtup = @import("utils.zig").fieldtup;
