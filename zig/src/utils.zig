pub fn fieldtup(fields: []const std.builtin.Type.StructField) struct {
    [fields.len][]const u8,
    [fields.len]type,
    [fields.len]std.builtin.Type.StructField.Attributes,
} {
    var names: [fields.len][]const u8 = undefined;
    var types: [fields.len]type = undefined;
    var attrs: [fields.len]std.builtin.Type.StructField.Attributes = undefined;

    for (fields, 0..) |field, i| {
        names[i] = field.name;
        types[i] = field.type;
        attrs[i] = .{
            .@"comptime" = field.is_comptime,
            .@"align" = field.alignment,
            .default_value_ptr = field.default_value_ptr,
        };
    }

    return .{ names, types, attrs };
}

const std = @import("std");
