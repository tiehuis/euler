const std = @import("std");
const Mode = @import("builtin").Mode;
const Builder = std.build.Builder;
const TestStep = std.build.TestStep;

const TestCase = struct {
    filename: []const u8,
    problem_type: ProblemType,
};

const ProblemType = enum {
    Free,
    LinkLibC,
};

fn Free(comptime filename: []const u8) -> TestCase {
    TestCase {
        .filename = filename,
        .problem_type = ProblemType.Free,
    }
}

fn LibC(comptime filename: []const u8) -> TestCase {
    TestCase {
        .filename = filename,
        .problem_type = ProblemType.LinkLibC,
    }
}

pub fn build(b: &Builder) {
    const tests = comptime []TestCase {
        Free("001"),
        Free("002"),
        LibC("078"),
        Free("116"),
        Free("117"),
        LibC("214"),
    };

    for ([]Mode { Mode.Debug, Mode.ReleaseSafe, Mode.ReleaseFast }) |mode| {
        inline for (tests) |test_case| {
            const all_tests = b.addTest(test_case.filename ++ ".zig");
            all_tests.setNamePrefix(b.fmt("{} ", @enumTagName(mode)));
            all_tests.setBuildMode(mode);
            if (test_case.problem_type == ProblemType.LinkLibC) {
                all_tests.linkSystemLibrary("c");
            }
            b.default_step.dependOn(&all_tests.step);
        }
    }
}
