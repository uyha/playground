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

    const scripts = .{
        "2d",
        "align",
        "arena_usage",
        "bitcast",
        "distinct",
        "fanotify",
        "function",
        "ignore",
        "lambda",
        "nullnull",
        "packed",
        "plus",
        "sentinel",
        "sizeof",
        "slice",
        "static",
        "struct",
        "swap",
        "tagged_union",
        "typemap",
        "typevar",
        "union",
        "use_shared_var",
        "vector",
    };

    inline for (scripts) |s| {
        _ = addPlayground(b, s, options);
    }

    const zeromq = addPlayground(b, "zeromq", options);
    const zimq = b.dependency("zimq", .{
        .target = target,
        .optimize = optimize,
    });
    const mzg = b.dependency("mzg", .{
        .target = target,
        .optimize = optimize,
    });

    zeromq.root_module.addImport("zimq", zimq.module("zimq"));
    zeromq.root_module.addImport("mzg", mzg.module("mzg"));

    const publish = addPlayground(b, "publish", options);
    publish.root_module.addImport("zimq", zimq.module("zimq"));

    const subscribe = addPlayground(b, "subscribe", options);
    subscribe.root_module.addImport("zimq", zimq.module("zimq"));

    const message_pack = addPlayground(b, "message_pack", options);
    message_pack.root_module.addImport("mzg", mzg.module("mzg"));

    const test_mod = b.addTest(.{
        .name = "test",
        .root_source_file = b.path("src/test.zig"),
        .target = target,
        .optimize = optimize,
    });
    test_mod.root_module.addImport("zimq", zimq.module("zimq"));
    const run_tests = b.addRunArtifact(test_mod);
    const test_step = b.step("test", "test");
    test_step.dependOn(&run_tests.step);
}
