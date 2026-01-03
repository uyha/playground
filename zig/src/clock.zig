const Resolution = struct {
    raw: u96,
    fn init(spec: std.c.timespec) Resolution {
        const raw_sec: u96 = @intCast(spec.sec);
        const raw_nsec: u96 = @intCast(spec.nsec);
        return .{ .raw = raw_sec * 1_000_000_000 + raw_nsec };
    }

    pub fn format(
        self: Resolution,
        writer: *std.Io.Writer,
    ) std.Io.Writer.Error!void {
        if (self.raw < 1_000) {
            try writer.print("{} ns", .{self.raw});
        } else if (self.raw < 1_000_000) {
            try writer.print("{} us", .{self.raw / 1_000});
        } else if (self.raw < 1_000_000_000) {
            try writer.print("{} ms", .{self.raw / 1_000_000});
        } else {
            try writer.print("{} s", .{self.raw / 1_000_000_000});
        }
    }
};

fn juicyMain(gpa: Allocator, io: Io) !void {
    _ = &gpa;

    var buffer: [1024]u8 = undefined;
    var file: std.Io.File = .stdout();
    var stdout: std.Io.File.Writer = file.writer(io, &buffer);
    const writer: *std.Io.Writer = &stdout.interface;

    for (std.enums.values(std.c.clockid_t)) |clock| {
        var res: std.c.timespec = undefined;
        var time: std.c.timespec = undefined;

        _ = std.c.clock_getres(clock, &res);
        _ = std.c.clock_gettime(clock, &time);

        try writer.print(
            ".{{ .name = {s}, .res = {f}, .time = {} }}\n",
            .{ @tagName(clock), Resolution.init(res), time },
        );
    }

    try writer.flush();
}
pub fn main() !void {
    var allocator: std.heap.DebugAllocator(.{}) = .init;
    defer _ = allocator.deinit();
    const gpa = allocator.allocator();

    var runtime: std.Io.Threaded = .init(gpa, .{});
    defer runtime.deinit();

    try juicyMain(gpa, runtime.io());
}

const std = @import("std");
const Allocator = std.mem.Allocator;
const Io = std.Io;
const Clock = Io.Clock;
