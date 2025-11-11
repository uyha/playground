const std = @import("std");

const Options = struct {
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
};

fn addPlayground(
    b: *std.Build,
    name: []const u8,
    options: Options,
) *std.Build.Step.Compile {
    var buffer: std.Io.Writer.Allocating = .init(b.allocator);
    defer buffer.deinit();

    buffer.writer.print("src/{s}.zig", .{name}) catch unreachable;

    const exe = b.addExecutable(.{
        .name = name,
        .root_module = b.createModule(.{
            .root_source_file = b.path(buffer.writer.buffered()),
            .target = options.target,
            .optimize = options.optimize,
        }),
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

    const options: Options = .{ .target = target, .optimize = optimize };

    const scripts = .{
        "2d",
        "align",
        "arena_usage",
        "bitcast",
        "distinct",
        "enum_map",
        "errdefer",
        "fanotify",
        "for-break",
        "function",
        "ignore",
        "io",
        "lambda",
        "nullnull",
        "max",
        "order_of_eval",
        "packed",
        "plus",
        "sentinel",
        "signal",
        "sizeof",
        "slice",
        "static",
        "struct",
        "subset",
        "swap",
        "tagged_union",
        "tuple",
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
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/test.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });
    test_mod.root_module.addImport("zimq", zimq.module("zimq"));
    const run_tests = b.addRunArtifact(test_mod);
    const test_step = b.step("test", "test");
    test_step.dependOn(&run_tests.step);

    const copyRes = b.addSystemCommand(&.{"cp"});
    copyRes.addFileArg(b.path("res/some.txt"));
    const out = copyRes.addOutputFileArg("out/some.txt");

    const resource = addPlayground(b, "resource", options);
    resource.root_module.addAnonymousImport("some", .{ .root_source_file = out });

    const clock = addPlayground(b, "clock", options);
    clock.root_module.link_libc = true;

    const main = addPlayground(b, "main", options);
    main.root_module.addAnonymousImport(
        "res",
        .{ .root_source_file = b.path("src/res.zon") },
    );
}
