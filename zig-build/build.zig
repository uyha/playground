const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const zmq = b.dependency(
        "zmq",
        .{ .target = target, .optimize = optimize },
    );
    const zmq_module = zmq.module("libzmq");

    const exe = b.addExecutable(.{
        .name = "some",
        .root_source_file = b.path("here.zig"),
        .target = target,
        .optimize = optimize,
    });
    exe.root_module.addImport("zmq", zmq_module);
    b.installArtifact(exe);

    const run_exe = b.addRunArtifact(exe);
    run_exe.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "");
    run_step.dependOn(&run_exe.step);
}
