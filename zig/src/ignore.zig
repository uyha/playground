fn random() error{WTF}!u8 {
    const static = struct {
        var engine: ?std.Random.DefaultPrng = null;
        var rand: ?std.Random = null;
    };

    if (static.rand == null) {
        static.engine = std.Random.DefaultPrng.init(@bitCast(std.time.milliTimestamp()));
        static.rand = static.engine.?.random();
    }

    return if (static.rand.?.boolean()) ' ' else error.WTF;
}

fn call() u8 {
    if (random() catch null) |val| return val;

    return 0;
}
pub fn main() !void {
    _ = call();
}

const std = @import("std");
