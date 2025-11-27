#define yeet orelse return null

fn yeetnull() ?usize {
  const a : ?usize = 1;
  return a yeet;
}

pub fn main() !void {
    std.debug.print("{?}\n", .{yeetnull()});
}

const std = @import("std");
