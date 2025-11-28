const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const zimq = b.dependency(
        "zimq",
        .{ .target = target, .optimize = optimize },
    );

    const mod = b.createModule(.{
        .root_source_file = b.path("here.zig"),
        .target = target,
        .optimize = optimize,
    });
    const exe = b.addExecutable(.{
        .name = "some",
        .root_module = mod,
    });
    exe.root_module.addImport("zimq", zimq.module("zimq"));
    b.installArtifact(exe);

    const run_exe = b.addRunArtifact(exe);
    run_exe.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "");
    run_step.dependOn(&run_exe.step);

    const pp = b.addSystemCommand(&.{ b.graph.zig_exe, "cc", "-xc", "-P", "-E" });
    pp.addFileArg(b.path("pre.zig"));
    pp.addArg("-o");
    const out = pp.addOutputFileArg("out.zig");


    const pp_mod = b.createModule(.{
        .root_source_file = out,
        .target = target,
        .optimize = optimize,
    });
    const pp_exe = b.addExecutable(.{ .name = "gen", .root_module = pp_mod });
    const pp_run = b.addRunArtifact(pp_exe);

    const pre = b.step("pre", "");
    pre.dependOn(&pp_run.step);
}
