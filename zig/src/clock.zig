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
pub fn main() !void {
    var buffer: [1024]u8 = undefined;
    var file: std.fs.File = .stdout();
    var stdout: std.fs.File.Writer = file.writer(&buffer);
    const writer: *std.Io.Writer = &stdout.interface;

    for (std.enums.values(std.c.clockid_t)) |clock| {
        var res: std.c.timespec = undefined;
        var time: std.c.timespec = undefined;

        _ = std.c.clock_getres(clock, &res);
        _ = std.c.clock_gettime(clock, &time);

        std.debug.print(
            ".{{ .name = {s}, .res = {f}, .time = {} }}\n",
            .{ @tagName(clock), Resolution.init(res), time },
        );
    }

    try writer.flush();
}

const std = @import("std");
