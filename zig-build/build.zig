const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    var zig_cc_builder = std.ArrayList(u8).init(b.allocator);
    defer zig_cc_builder.deinit();
    std.fmt.format(zig_cc_builder.writer(), "{s} cc", .{b.graph.zig_exe}) catch {};
    const zig_cc = zig_cc_builder.items;

    var zig_cxx_builder = std.ArrayList(u8).init(b.allocator);
    defer zig_cxx_builder.deinit();
    std.fmt.format(zig_cxx_builder.writer(), "{s} c++", .{b.graph.zig_exe}) catch {};
    const zig_cxx = zig_cxx_builder.items;

    const cmake = b.addSystemCommand(&[_][]const u8{ "echo", zig_cc, zig_cxx });
    const cmake_step = b.step("cmake", "Invoke cmake");
    cmake_step.dependOn(&cmake.step);

    if (b.args) |args| {
        cmake.addArgs(args);
    }

    const exe = b.addExecutable(.{
        .name = "some",
        .root_source_file = b.path("here.zig"),
        .target = target,
        .optimize = optimize,
    });
    b.installArtifact(exe);
}
