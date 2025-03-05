const std = @import("std");

const ExecutableOptions = blk: {
    const OptionsStruct = @typeInfo(std.Build.ExecutableOptions).@"struct";

    var fields: [OptionsStruct.fields.len]std.builtin.Type.StructField = undefined;

    var index = 0;
    for (OptionsStruct.fields) |field| {
        if (!std.mem.eql(u8, field.name, "name") and
            !std.mem.eql(u8, field.name, "root_source_file"))
        {
            fields[index] = field;
            index += 1;
        }
    }

    break :blk @Type(.{
        .@"struct" = .{
            .layout = .auto,
            .fields = fields[0..index],
            .decls = &[_]std.builtin.Type.Declaration{},
            .is_tuple = false,
        },
    });
};

fn executableOptions(
    name: []const u8,
    root_source_file: std.Build.LazyPath,
    options: ExecutableOptions,
) std.Build.ExecutableOptions {
    var result: std.Build.ExecutableOptions = undefined;
    result.name = name;
    result.root_source_file = root_source_file;

    for (@typeInfo(ExecutableOptions).Struct.fields) |field| {
        @field(result, field.name) = @field(options, field.name);
    }

    return result;
}

fn addPlayground(
    b: *std.Build,
    name: []const u8,
    options: ExecutableOptions,
) void {
    var buffer = std.ArrayList(u8).init(b.allocator);
    defer buffer.deinit();

    std.fmt.format(buffer.writer(), "src/{s}.zig", .{name}) catch unreachable;

    const exe = b.addExecutable(.{
        .name = name,
        .root_source_file = b.path(buffer.items),
        .target = options.target,
        .optimize = options.optimize,
    });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step(name, "");
    run_step.dependOn(&run_cmd.step);
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const options: ExecutableOptions = .{ .target = target, .optimize = optimize };

    addPlayground(b, "tagged_union", options);
    addPlayground(b, "sentinel", options);
    addPlayground(b, "distinct", options);
    addPlayground(b, "use_shared_var", options);
    addPlayground(b, "arena_usage", options);
    addPlayground(b, "lambda", options);
    addPlayground(b, "slice", options);
}
