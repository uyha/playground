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

const FromEpoch = struct {
    timestamp: Timestamp,

    pub fn format(self: FromEpoch, writer: *Io.Writer) Io.Writer.Error!void {
        const nanosecond = 1;
        const microsecond = 1000 * nanosecond;
        const millisecond = 1000 * microsecond;
        const second = 1000 * millisecond;
        const minute = 60 * second;
        const hour = 60 * minute;
        const day = 24 * hour;

        var remain = self.timestamp.toNanoseconds();
        if (remain > day) {
            const days = @divFloor(remain, day);
            try writer.print("{}d", .{days});
            remain -= days * day;
        }
        if (remain > hour) {
            const hours = @divFloor(remain, hour);
            try writer.print(" {}h", .{hours});
            remain -= hours * hour;
        }
        if (remain > minute) {
            const minutes = @divFloor(remain, minute);
            try writer.print(" {}m", .{minutes});
            remain -= minutes * minute;
        }
        if (remain > second) {
            const seconds = @divFloor(remain, second);
            try writer.print(" {}s", .{seconds});
            remain -= seconds * second;
        }
        if (remain > millisecond) {
            const milliseconds = @divFloor(remain, millisecond);
            try writer.print(" {}ms", .{milliseconds});
            remain -= milliseconds * millisecond;
        }
    }
};

fn fromEpoch(timestamp: Timestamp) FromEpoch {
    return .{ .timestamp = timestamp };
}

pub fn main(init: Init) !void {
    var buffer: [1024]u8 = undefined;
    var file: std.Io.File = .stdout();
    var stdout: std.Io.File.Writer = file.writer(init.io, &buffer);
    const writer: *std.Io.Writer = &stdout.interface;

    for (std.enums.values(std.c.clockid_t)) |clock| {
        var res: std.c.timespec = undefined;
        var time: std.c.timespec = undefined;

        _ = std.c.clock_getres(clock, &res);
        _ = std.c.clock_gettime(clock, &time);

        try writer.print(
            ".{{ .name = {s}, .res = {f}, .time = {f} }}\n",
            .{
                @tagName(clock),
                Resolution.init(res),
                fromEpoch(Timestamp.fromNanoseconds(time.sec * 1_000_000_000 + time.nsec)),
            },
        );
    }

    try writer.flush();
}

const std = @import("std");
const Allocator = std.mem.Allocator;
const Io = std.Io;
const Clock = Io.Clock;
const Timestamp = Io.Timestamp;
const Init = std.process.Init;
