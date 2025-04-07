pub fn main() !void {
    _ = Packed{ .child = .{ .value = 32 } };
}

const Child = packed struct {
    value: i32,
};
const Packed = packed struct {
    child: Child,
};
