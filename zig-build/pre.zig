#include "header.zig"
#define yeet orelse return null

fn yeetnull() ?usize {
  const a: ?usize = null;
  return a yeet;
}

pub fn main() !void {
    std.debug.print("{?} {}\n", .{yeetnull(), global});
}

const std = @import("std");
