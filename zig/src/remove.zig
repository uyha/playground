fn remove(
    source: anytype,
    predicate: *const fn (Elem(@TypeOf(source))) bool,
) []Elem(@TypeOf(source)) {
    var begin: usize = for (source, 0..) |item, index| {
        if (predicate(item)) {
            break index;
        }
    } else return source;

    var current = begin;
    begin += 1;
    while (begin < source.len) : (begin += 1) {
        if (!predicate(source[begin])) {
            source[current] = source[begin];
            current += 1;
        }
    }

    return source[0..current];
}

fn even(n: usize) bool {
    return n % 2 == 0;
}

pub fn main() !void {
    var a: [1_000_000]usize = undefined;
    for (a, 0..) |_, i| {
        a[i] = i;
    }
    var slice: []usize = &a;
    slice = remove(&a, even);

    std.debug.print("{any}\n", .{slice});
}

const std = @import("std");
const Elem = std.meta.Elem;
