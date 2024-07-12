const std = @import("std");

fn TypeList(current: anytype) type {
    comptime {
        switch (@typeInfo(@TypeOf(current))) {
            .Struct => |t| {
                if (!t.is_tuple) {
                    @compileError("`current` must be a tuple of types");
                }
                for (t.fields) |field| {
                    if (field.type != type) {
                        @compileError(std.fmt.comptimePrint(
                            "Field {s} must be a type, but it is {}\n",
                            .{ field.name, field.type },
                        ));
                    }
                }
            },
            else => @compileError("`current` must be a tuple of types"),
        }
    }
    return struct {
        const types = current;

        pub fn append(next: anytype) @TypeOf(TypeList(@This().types ++ .{next})) {
            return TypeList(@This().types ++ .{next});
        }

        pub fn index(comptime T: type) usize {
            inline for (0.., types) |i, t| {
                if (t == T) return i;
            }
        }
    };
}

fn isEven(ptr: *const u32) bool {
    return @rem(ptr.*, 2) == 0;
}

fn flip(ptr: *u32) void {
    ptr.* ^= 1;
}

fn giveMeRaw(any: anytype) void {
    _ = any;
}

const A = struct {
    pub fn a(_: @This()) void {}
};

fn a(_: A) void {}

pub fn main() !void {
    std.debug.print("{}\n", .{@typeInfo(@TypeOf(giveMeRaw)).Fn.params[0].is_generic});
    const c = A{};
    A.a(c);
}
