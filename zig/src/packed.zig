pub fn main() !void {
    const a: Packed = @bitCast(@as(u32, 1));
    _ = &a;
}

const Child = packed struct(u32) {
    value: i32,
};
const Packed = packed struct {
    child: Child,
};
