const std = @import("std");
const linux = std.os.linux;
const posix = std.posix;

pub fn main() !void {
    const handle = try std.posix.fanotify_init(
        .{
            .CLOEXEC = true,
            .NONBLOCK = true,
            .REPORT_NAME = true,
            .REPORT_DIR_FID = true,
            .REPORT_FID = true,
            .REPORT_TARGET_FID = true,
        },
        0,
    );

    try std.posix.fanotify_mark(
        handle,
        .{ .ADD = true },
        .{
            .CLOSE_WRITE = true,
            .CREATE = true,
            .EVENT_ON_CHILD = true,
        },
        posix.AT.FDCWD,
        "./",
    );

    const epoll_handle = linux.epoll_create();
    var event: linux.epoll_event = .{
        .events = linux.EPOLL.IN,
        .data = .{ .fd = handle },
    };
    std.debug.print("{s}:{} ({s}): ", .{ @src().file, @src().line, @src().fn_name });
    std.debug.print(
        "{}\n",
        .{
            linux.epoll_ctl(
                @intCast(epoll_handle),
                linux.EPOLL.CTL_ADD,
                handle,
                &event,
            ),
        },
    );
    var buffer: [1]linux.epoll_event = undefined;
    std.debug.print("{s}:{} ({s}): ", .{ @src().file, @src().line, @src().fn_name });
    std.debug.print("{}\n", .{
        linux.epoll_wait(
            @intCast(epoll_handle),
            &buffer,
            buffer.len,
            -1,
        ),
    });
    std.debug.print("{s}:{} ({s}): ", .{ @src().file, @src().line, @src().fn_name });
    std.debug.print("{} {any}\n", .{ buffer[0].events, buffer[0].data.fd });

    var fa_buffer: [88]u8 align(@alignOf(linux.fanotify.event_metadata)) = undefined;
    const result = posix.read(handle, &fa_buffer);
    std.debug.print("{s}:{} ({s}): ", .{ @src().file, @src().line, @src().fn_name });
    std.debug.print("{any}\n", .{result});

    const fa_event: *linux.fanotify.event_metadata = @ptrCast(&fa_buffer);

    std.debug.print("{any}\n", .{fa_event});
}
