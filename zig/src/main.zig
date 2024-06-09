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

pub fn main() !void {
    comptime var list = TypeList(.{});
    comptime {
        list = list.append(u8).append(u16);
    }

    inline for (0.., list.types) |i, t| {
        std.debug.print("{} {}\n", .{ i, t });
    }
}
