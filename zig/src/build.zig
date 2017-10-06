const std = @import("std");
const Mode = @import("builtin").Mode;
const Builder = std.build.Builder;
const TestStep = std.build.TestStep;

pub fn build(b: &Builder) {
    const tests = [][]const u8 {
        "001",
        "002",
        "116",
        "117"
    };

    for ([]Mode { Mode.Debug, Mode.ReleaseSafe, Mode.ReleaseFast }) |mode| {
        inline for (tests) |src_file| {
            const all_tests = b.addTest(src_file ++ ".zig");
            all_tests.setNamePrefix(b.fmt("{} ", @enumTagName(mode)));
            all_tests.setBuildMode(mode);
            b.default_step.dependOn(&all_tests.step);
        }
    }
}
