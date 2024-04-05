const std = @import("std");
const print = std.debug.print;

const Shape = union(enum) {
    rectangle: struct { width: u8, height: u8 },
    triangle: struct { base: u8, height: u8 },
};

pub fn main() !void {
    const info = @typeInfo(Shape);
    const tag_info = @typeInfo(info.Union.tag_type.?);
    print("{?}\n", .{tag_info.Enum.tag_type});
    inline for (@typeInfo(Shape).Union.fields) |field| {
        print("{s}\n", .{field.name});
    }
}
