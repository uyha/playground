const std = @import("std");
const print = std.debug.print;

pub fn main() !void {
    const Rectangle = struct {
        width: f32,
        height: f32,

        pub fn calculate_area(self: *@This()) f32 {
            return self.width * self.height;
        }
    };
    var r: Rectangle = Rectangle{ .width = 34.5, .height = 23.66 };
    print("area is {}\n", .{r.calculate_area()});
}

test "simple test" {
    var list = std.ArrayList(i32).init(std.testing.allocator);
    defer list.deinit(); // try commenting this out and see if zig detects the memory leak!
    try list.append(42);
    try std.testing.expectEqual(@as(i32, 42), list.pop());
}
