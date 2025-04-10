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
) *std.Build.Step.Compile {
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

    return exe;
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const options: ExecutableOptions = .{ .target = target, .optimize = optimize };

    _ = addPlayground(b, "arena_usage", options);
    _ = addPlayground(b, "distinct", options);
    _ = addPlayground(b, "fanotify", options);
    _ = addPlayground(b, "lambda", options);
    _ = addPlayground(b, "packed", options);
    _ = addPlayground(b, "plus", options);
    _ = addPlayground(b, "sentinel", options);
    _ = addPlayground(b, "slice", options);
    _ = addPlayground(b, "struct", options);
    _ = addPlayground(b, "swap", options);
    _ = addPlayground(b, "tagged_union", options);
    _ = addPlayground(b, "use_shared_var", options);

    const zeromq = addPlayground(b, "zeromq", options);
    const zimq = b.dependency("zimq", .{
        .target = target,
        .optimize = optimize,
    });
    zeromq.root_module.addImport("zimq", zimq.module("zimq"));

    const message_pack = addPlayground(b, "message_pack", options);
    const mzg = b.dependency("mzg", .{
        .target = target,
        .optimize = optimize,
    });
    message_pack.root_module.addImport("mzg", mzg.module("mzg"));
}
