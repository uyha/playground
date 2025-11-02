fn random() error{ WTF, Unexpected, UnsupportedClock }!u8 {
    const static = struct {
        var engine: ?std.Random.DefaultPrng = null;
        var rand: ?std.Random = null;
    };

    var this_thread: Io.Threaded = .init_single_threaded;
    const io: Io = this_thread.io();

    if (static.rand == null) {
        const now = try Clock.real.now(io);
        static.engine = std.Random.DefaultPrng.init(@bitCast(now.toSeconds()));
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
const Io = std.Io;
const Clock = Io.Clock;
