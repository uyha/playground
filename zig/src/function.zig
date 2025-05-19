const A = struct {
    pub fn a(self: anytype) void {
        _ = self;
    }
};
pub fn main() !void {
    const a: A = .{};
    a.a();
}
