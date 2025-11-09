pub fn Signal(Event: type) type {
    const Subscriber = struct {
        id: usize,
        f: *const fn (userdata: ?*anyopaque, event: Event) void,
        userdata: ?*anyopaque,
    };
    return struct {
        const Self = @This();

        current_id: usize = 0,
        subscribers: std.ArrayList(Subscriber) = .empty,

        pub const init: Self = .{};

        pub fn add(self: *Self, gpa: std.mem.Allocator, f: *const fn (userdata: ?*anyopaque, event: Event) void, userdata: ?*anyopaque) std.mem.Allocator.Error!usize {
            const subscriber: *Subscriber = try self.subscribers.addOne(gpa);
            defer self.current_id +%= 1;
            subscriber.id = self.current_id;
            subscriber.f = f;
            subscriber.userdata = userdata;

            return self.current_id;
        }
        pub fn remove(self: *Self, id: usize) void {
            for (self.subscribers.items, 0..) |subscriber, i| {
                if (subscriber.id == id) {
                    _ = self.subscribers.swapRemove(i);
                    return;
                }
            }
        }

        pub fn emit(self: *const Self, event: Event) void {
            for (self.subscribers.items) |*subscriber| {
                subscriber.f(subscriber.userdata, event);
            }
        }
    };
}

fn echo(_: ?*anyopaque, event: u8) void {
    std.debug.print(
        "{s}:{} ({s}) {}\n",
        .{ @src().file, @src().line, @src().fn_name, event },
    );
}

pub fn main() !void {
    var allocator: std.heap.DebugAllocator(.{}) = .init;
    const gpa: std.mem.Allocator = allocator.allocator();

    var signal: Signal(u8) = .init;
    var id = try signal.add(gpa, echo, null);

    signal.emit(1);
    signal.remove(id);
    signal.emit(1);

    id = try signal.add(gpa, echo, null);
    signal.emit(1);
}

const std = @import("std");
