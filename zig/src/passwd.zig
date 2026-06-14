const Entry = struct {
    name: []const u8,
    password: []const u8,
    uid: []const u8,
    gid: []const u8,
    gecos: []const u8,
    directory: []const u8,
    shell: []const u8,

    pub fn format(self: *const Entry, writer: *Io.Writer) Io.Writer.Error!void {
        return try writer.print(
            \\.{{.name = "{s}", .password = "{s}", .uid = "{s}", .gid = "{s}", .gecos = "{s}", .directory = "{s}", .shell = "{s}"}}"
        ,
            .{ self.name, self.password, self.uid, self.gid, self.gecos, self.directory, self.shell },
        );
    }
};

const PsswdParser = struct {
    content: std.ArrayList(u8) = .empty,
    reader: *Io.Reader,

    pub fn init(reader: *Io.Reader) PsswdParser {
        return .{ .reader = reader };
    }
    pub fn deinit(self: *PsswdParser, gpa: Allocator) void {
        self.content.deinit(gpa);
    }

    pub fn next(
        self: *PsswdParser,
        gpa: Allocator,
    ) error{ ReadFailed, OutOfMemory, Malformed }!?Entry {
        self.content.clearRetainingCapacity();

        const fields = @typeInfo(Entry).@"struct".fields;
        var ranges: [fields.len]struct { start: usize, end: usize } = undefined;
        var count: u8 = 0;
        var start: usize = 0;

        while (self.reader.takeByte()) |c| {
            if (c == '\n') {
                ranges[count] = .{ .start = start, .end = self.content.items.len };
                count += 1;
                break;
            }

            try self.content.append(gpa, c);

            if (c == ':') {
                ranges[count] = .{ .start = start, .end = self.content.items.len - 1 };
                count += 1;
                start = self.content.items.len;
            }
        } else |e| {
            switch (e) {
                error.EndOfStream => {
                    if (self.content.items.len == 0) return null;
                    ranges[count] = .{ .start = start, .end = self.content.items.len - 1 };
                    count += 1;
                },
                else => |v| return v,
            }
        }

        if (count != fields.len) {
            return error.Malformed;
        }

        return .{
            .name = self.content.items[ranges[0].start..ranges[0].end],
            .password = self.content.items[ranges[1].start..ranges[1].end],
            .uid = self.content.items[ranges[2].start..ranges[2].end],
            .gid = self.content.items[ranges[3].start..ranges[3].end],
            .gecos = self.content.items[ranges[4].start..ranges[4].end],
            .directory = self.content.items[ranges[5].start..ranges[5].end],
            .shell = self.content.items[ranges[6].start..ranges[6].end],
        };
    }
};

pub fn main(init: Init) !void {
    // const f = try Io.Dir.openFileAbsolute(init.io, "/etc/passwd", .{});
    //
    // var buffer: [2048]u8 = undefined;
    // var streaming_reader = f.readerStreaming(init.io, &buffer);
    // const reader: *Io.Reader = &streaming_reader.interface;

    var reader: Io.Reader = Io.Reader.fixed(
        \\uy:x:100:100::test:asdf
    );
    var parser: PsswdParser = .init(&reader);
    defer parser.deinit(init.gpa);

    // const uid = std.os.linux.getuid();
    //
    while (try parser.next(init.gpa)) |entry| {
        // if (uid != try std.fmt.parseInt(std.os.linux.uid_t, entry.uid, 10)) {
        //     continue;
        // }
        std.debug.print("{f}\n", .{entry});
    }
}

const std = @import("std");
const Allocator = std.mem.Allocator;
const Io = std.Io;
const Clock = Io.Clock;
const Init = std.process.Init;
