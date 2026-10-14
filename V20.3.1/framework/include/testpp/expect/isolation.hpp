// #pragma once

#ifndef E_ISO_H
#define E_ISO_H

#include "../internal/pch/impl_pch.hpp"

#include "../internal/core/core.hpp"
#include "../internal/core/isolated.hpp"
#include "../internal/fail.hpp"
#include "../internal/helpers.hpp"
#include "../internal/implementation/isolation.hpp"

#include <algorithm>

// Fatal / completion
#define EXPECT_DEATH(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::death(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_SEGFAULT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::segfault(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_ABORT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::abort(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_FATAL(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::fatal(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_NONFATAL(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::nonFatal(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_COMPLETES(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::completes(r, #result, __FILE__, __LINE__); }, false)

// Exit codes
#define EXPECT_SUCCESS(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::success(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::failure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_NONZERO_EXIT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::nonzeroExit(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_EXITCODE(result, code) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::exitCode(r, #result, (code), __FILE__, __LINE__); }, false)

// Output
#define EXPECT_STDOUT_CONTAINS(result, content) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::stdoutContains(r, #result, (content), __FILE__, __LINE__); }, false)

#define EXPECT_STDERR_CONTAINS(result, content) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::stderrContains(r, #result, (content), __FILE__, __LINE__); }, false)

#define EXPECT_NO_STDOUT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noStdout(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_NO_STDERR(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noStderr(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_STDOUT_MATCHES(result, content) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::stdoutMatches(r, #result, (content), __FILE__, __LINE__); }, false)

#define EXPECT_STDERR_MATCHES(result, content) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::stderrMatches(r, #result, (content), __FILE__, __LINE__); }, false)

// Sanitizers
#define EXPECT_ASAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::asanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_NASAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noAsanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_UBSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::ubsanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_NUBSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noUbsanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_TSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::tsanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_NTSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noTsanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_LSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::lsanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_NLSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noLsanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_SAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::sanFailure(r, #result, __FILE__, __LINE__); }, false)

#define EXPECT_NSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noSanFailure(r, #result, __FILE__, __LINE__); }, false)

// Timing: the timeout itself is configured in RUN_ISO.
// The assertion checks the returned result.
#define EXPECT_TIMEOUT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::timeout(r, #result, 0, __FILE__, __LINE__); }, false)

#define EXPECT_COMPLETES_WITHIN(result, timeLimit) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::completesWithin(r, #result, (timeLimit), __FILE__, __LINE__); }, false)

// General result metadata
#define EXPECT_STATUS(result, expected) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::executionStatus(r, #result, (expected), __FILE__, __LINE__); }, false)

#define EXPECT_CRASH_TYPE(result, expected) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::crashType(r, #result, (expected), __FILE__, __LINE__); }, false)

#define EXPECT_SIGNAL(result, signal) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::terminationSignal(r, #result, (signal), __FILE__, __LINE__); }, false)

#define EXPECT_KILLED(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::killed(r, #result, __FILE__, __LINE__); }, false)


namespace testpp::internal {
    namespace Assert {
        template<typename Checker>
        inline void evaluate(const Core::ExecutionResult& result, Checker&& checker, const bool fatal)
        {
            auto failure = checker(result);

            if (failure) {
                if (fatal) {
                    Fail::a_fail(*failure);
                } else {
                    Fail::e_fail(*failure);
                }
            }
        }
    }
}

#endif