const std = @import("std");
const Mode = @import("builtin").Mode;
const Builder = std.build.Builder;
const TestStep = std.build.TestStep;

const TestCase = struct {
    filename: []const u8,
    problem_type: ProblemType,
    run: bool,
};

const ProblemType = enum {
    Free,
    LinkLibC,
};

fn Free(comptime filename: []const u8) TestCase {
    return TestCase {
        .filename = filename,
        .problem_type = ProblemType.Free,
        .run = true,
    };
}

fn LibC(comptime filename: []const u8) TestCase {
    return TestCase {
        .filename = filename,
        .problem_type = ProblemType.LinkLibC,
        .run = true,
    };
}

pub fn build(b: &Builder) void {
    const tests = comptime []TestCase {
        Free("001"),
        Free("002"),
        LibC("078"),
        Free("112"),
        Free("116"),
        Free("117"),
        TestCase { .filename = "145", .problem_type = ProblemType.Free, .run = false },
        LibC("214"),
    };

    for ([]Mode { Mode.Debug, Mode.ReleaseSafe, Mode.ReleaseFast }) |mode| {
        inline for (tests) |test_case| {
            const all_tests = b.addTest(test_case.filename ++ ".zig");
            all_tests.setNamePrefix(b.fmt("{} ", @tagName(mode)));
            all_tests.setBuildMode(mode);
            if (test_case.problem_type == ProblemType.LinkLibC) {
                all_tests.linkSystemLibrary("c");
            }
            if (test_case.run) {
                b.default_step.dependOn(&all_tests.step);
            }
        }
    }
}
