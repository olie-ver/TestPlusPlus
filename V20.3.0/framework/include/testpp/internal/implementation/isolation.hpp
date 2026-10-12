#pragma once

#ifndef ISO_H
#define ISO_H

#include "isolation_types.hpp"

#define RUN_ISO(...) testpp::internal::impl_iso::runIsolated(__VA_ARGS__)

#pragma once

#include "../core/core.hpp"
#include "../helpers.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <string>

namespace testpp::internal::impl_iso {

    using Result = Core::ExecutionResult;
    using Failure = Core::FailureInfo;
    using Status = Core::ExecutionStatus;
    using Crash = Core::CrashType;

    inline std::optional<Failure> failUnless(
        bool passed,
        std::string message,
        const char* file,
        uint32_t line)
    {
        if (passed) {
            return std::nullopt;
        }

        return Failure{std::move(message), file, line};
    }

    inline std::string statusName(Status status) {
        return Core::ExecutionStrings[static_cast<int>(status)];
    }

    inline std::string crashName(Crash crash) {
        return Core::CrashStrings[static_cast<int>(crash)];
    }

    inline std::string exitMessage(
        const char* expr,
        int expected,
        int actual)
    {
        return std::string("Expected ") + expr
            + " to exit with code " + Helpers::toString(expected)
            + ", but it exited with code " + Helpers::toString(actual);
    }

    inline std::string excerpt(const std::string& text) {
        constexpr size_t maxSize = 1024;
        return text.substr(0, std::min(maxSize, text.size()));
    }

    // --------------------------------------------------------
    // Termination / completion
    // --------------------------------------------------------

    inline std::optional<Failure> death(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        const bool died =
            r.execution_status != Status::Completed
            || r.crash_type != Crash::None;

        return failUnless(
            died,
            std::string("Expected ") + expr + " to terminate abnormally",
            file, line);
    }

    inline std::optional<Failure> segfault(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        return failUnless(
            r.crash_type == Crash::SegmentationFault,
            std::string("Expected ") + expr + " to seg fault, but crash type was "
                + crashName(r.crash_type),
            file, line);
    }

    inline std::optional<Failure> abort(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        return failUnless(
            r.crash_type == Crash::Abort,
            std::string("Expected ") + expr + " to abort, but crash type was "
                + crashName(r.crash_type),
            file, line);
    }

    inline std::optional<Failure> fatal(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        const bool failed =
            r.execution_status != Status::Completed
            || r.crash_type != Crash::None;

        return failUnless(
            failed,
            std::string("Expected ") + expr + " to fail or crash, but it completed",
            file, line);
    }

    inline std::optional<Failure> nonFatal(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        const bool passed =
            r.execution_status == Status::Completed
            && r.crash_type == Crash::None;

        return failUnless(
            passed,
            std::string("Expected ") + expr
                + " to complete without failure; status: "
                + statusName(r.execution_status)
                + ", crash type: " + crashName(r.crash_type),
            file, line);
    }

    inline std::optional<Failure> completes(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        return failUnless(
            r.execution_status == Status::Completed,
            std::string("Expected ") + expr + " to complete; status: "
                + statusName(r.execution_status),
            file, line);
    }

    // --------------------------------------------------------
    // Exit codes
    // --------------------------------------------------------

    inline std::optional<Failure> success(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        return failUnless(
            r.execution_status == Status::Completed
                && r.process.native_exit_code == EXIT_SUCCESS,
            exitMessage(expr, EXIT_SUCCESS, r.process.native_exit_code),
            file, line);
    }

    inline std::optional<Failure> failure(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        return failUnless(
            r.execution_status == Status::Completed
                && r.process.native_exit_code == EXIT_FAILURE,
            exitMessage(expr, EXIT_FAILURE, r.process.native_exit_code),
            file, line);
    }

    inline std::optional<Failure> nonzeroExit(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        return failUnless(
            r.execution_status == Status::Completed
                && r.process.native_exit_code != 0,
            std::string("Expected ") + expr
                + " to exit with a nonzero code; actual code: "
                + Helpers::toString(r.process.native_exit_code),
            file, line);
    }

    inline std::optional<Failure> exitCode(
        const Result& r, const char* expr, int expected,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.execution_status == Status::Completed
                && r.process.native_exit_code == expected,
            exitMessage(expr, expected, r.process.native_exit_code),
            file, line);
    }

    // --------------------------------------------------------
    // Captured output
    // --------------------------------------------------------

    inline std::optional<Failure> stdoutContains(
        const Result& r, const char* expr, const std::string& content,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.output.stdout_text.find(content) != std::string::npos,
            std::string("Expected stdout from ") + expr + " to contain \""
                + content + "\".\nstdout: " + excerpt(r.output.stdout_text),
            file, line);
    }

    inline std::optional<Failure> stderrContains(
        const Result& r, const char* expr, const std::string& content,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.output.stderr_text.find(content) != std::string::npos,
            std::string("Expected stderr from ") + expr + " to contain \""
                + content + "\".\nstderr: " + excerpt(r.output.stderr_text),
            file, line);
    }

    inline std::optional<Failure> noStdout(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        return failUnless(
            r.output.stdout_text.empty(),
            std::string("Expected no stdout from ") + expr
                + ".\nstdout: " + excerpt(r.output.stdout_text),
            file, line);
    }

    inline std::optional<Failure> noStderr(
        const Result& r, const char* expr, const char* file, uint32_t line)
    {
        return failUnless(
            r.output.stderr_text.empty(),
            std::string("Expected no stderr from ") + expr
                + ".\nstderr: " + excerpt(r.output.stderr_text),
            file, line);
    }

    inline std::optional<Failure> stdoutMatches(
        const Result& r, const char* expr, const std::string& expected,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.output.stdout_text == expected,
            std::string("Expected stdout from ") + expr
                + " to match the expected text.\nstdout: "
                + excerpt(r.output.stdout_text),
            file, line);
    }

    inline std::optional<Failure> stderrMatches(
        const Result& r, const char* expr, const std::string& expected,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.output.stderr_text == expected,
            std::string("Expected stderr from ") + expr
                + " to match the expected text.\nstderr: "
                + excerpt(r.output.stderr_text),
            file, line);
    }

    // --------------------------------------------------------
    // Sanitizers
    // --------------------------------------------------------

    inline std::optional<Failure> asanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            r.sanitizers.asan_detected,
            "Expected AddressSanitizer to report a failure",
            file, line);
    }

    inline std::optional<Failure> noAsanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            !r.sanitizers.asan_detected,
            "Unexpected AddressSanitizer failure: " + r.sanitizers.asan_msg,
            file, line);
    }

    inline std::optional<Failure> ubsanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            r.sanitizers.ubsan_detected,
            "Expected UndefinedBehaviorSanitizer to report a failure",
            file, line);
    }

    inline std::optional<Failure> noUbsanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            !r.sanitizers.ubsan_detected,
            "Unexpected UBSan failure: " + r.sanitizers.ubsan_msg,
            file, line);
    }

    inline std::optional<Failure> tsanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            r.sanitizers.tsan_detected,
            "Expected ThreadSanitizer to report a failure",
            file, line);
    }

    inline std::optional<Failure> noTsanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            !r.sanitizers.tsan_detected,
            "Unexpected TSan failure: " + r.sanitizers.tsan_msg,
            file, line);
    }

    inline std::optional<Failure> lsanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            r.sanitizers.lsan_detected,
            "Expected LeakSanitizer to report a failure",
            file, line);
    }

    inline std::optional<Failure> noLsanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            !r.sanitizers.lsan_detected,
            "Unexpected LSan failure: " + r.sanitizers.lsan_msg,
            file, line);
    }

    inline std::optional<Failure> sanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        const bool detected =
            r.sanitizers.asan_detected
            || r.sanitizers.ubsan_detected
            || r.sanitizers.tsan_detected
            || r.sanitizers.lsan_detected;

        return failUnless(
            detected,
            "Expected a sanitizer to report a failure",
            file, line);
    }

    inline std::optional<Failure> noSanFailure(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        const bool detected =
            r.sanitizers.asan_detected
            || r.sanitizers.ubsan_detected
            || r.sanitizers.tsan_detected
            || r.sanitizers.lsan_detected;

        return failUnless(
            !detected,
            "Unexpected sanitizer failure",
            file, line);
    }

    // --------------------------------------------------------
    // Timing and general metadata
    // --------------------------------------------------------

    inline std::optional<Failure> timeout(
        const Result& r, const char* expr, int,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.execution_status == Status::TimedOut,
            std::string("Expected ") + expr + " to time out; status: "
                + statusName(r.execution_status),
            file, line);
    }

    inline std::optional<Failure> completesWithin(
        const Result& r, const char* expr, int timeLimitMs,
        const char* file, uint32_t line)
    {
        const bool completed =
            r.execution_status == Status::Completed
            && r.execution_ms <= static_cast<uint64_t>(timeLimitMs);

        return failUnless(
            completed,
            std::string("Expected ") + expr + " to complete within "
                + Helpers::toString(timeLimitMs) + "ms; measured "
                + Helpers::toString(r.execution_ms) + "ms, status: "
                + statusName(r.execution_status),
            file, line);
    }

    inline std::optional<Failure> executionStatus(
        const Result& r, const char*, Status expected,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.execution_status == expected,
            std::string("Expected execution status ")
                + statusName(expected) + ", got "
                + statusName(r.execution_status),
            file, line);
    }

    inline std::optional<Failure> crashType(
        const Result& r, const char*, Crash expected,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.crash_type == expected,
            std::string("Expected crash type ")
                + crashName(expected) + ", got " + crashName(r.crash_type),
            file, line);
    }

    inline std::optional<Failure> terminationSignal(
        const Result& r, const char*, int expected,
        const char* file, uint32_t line)
    {
        return failUnless(
            r.process.native_signal == expected,
            std::string("Expected termination signal ")
                + Helpers::toString(expected) + ", got "
                + Helpers::toString(r.process.native_signal),
            file, line);
    }

    inline std::optional<Failure> killed(
        const Result& r, const char*, const char* file, uint32_t line)
    {
        return failUnless(
            r.crash_type == Crash::Killed,
            "Expected the isolated process to be killed",
            file, line);
    }

}

#endif