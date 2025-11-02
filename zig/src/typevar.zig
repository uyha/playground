const Some = struct {
    Type: type,
};

fn print(some: Some) void {
    std.debug.print("{s}\n", .{@typeName(some.Type)});
}
pub fn main() !void {
    // var rng = std.Random.DefaultPrng.init(@intCast(std.time.milliTimestamp()));
    //
    // if (rng.random().boolean()) print(Some{ .Type = i3 }) else print(Some{ .Type = i2 });
    // print(if (rng.random().boolean()) Some{ .Type = i3 } else Some{ .Type = i2 });
}

const std = @import("std");
