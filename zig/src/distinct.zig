const std = @import("std");
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
    var a_info = @typeInfo(A);
    a_info.@"struct".decls.len = 0;
    break :blk @Type(a_info);
};

pub fn main() void {
    std.debug.print("{}\n", .{A == C});
}
