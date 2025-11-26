pub fn main() !void {
    var ptr: **u8 = undefined;
    // const any: **anyopaque = &ptr;
    const any: **anyopaque = @ptrCast(&ptr);
    _ = &any;
}

const std = @import("std");
