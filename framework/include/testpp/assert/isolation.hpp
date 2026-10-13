#pragma once

#ifndef A_ISO_H
#define A_ISO_H

#include "../internal/pch/impl_pch.hpp"

#include "../internal/core/core.hpp"
#include "../internal/core/isolated.hpp"
#include "../internal/fail.hpp"
#include "../internal/helpers.hpp"
#include "../internal/implementation/isolation.hpp"

#include <algorithm>

// Fatal / completion
#define ASSERT_DEATH(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::death(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_SEGFAULT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::segfault(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_ABORT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::abort(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_FATAL(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::fatal(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_NONFATAL(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::nonFatal(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_COMPLETES(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::completes(r, #result, __FILE__, __LINE__); }, true)

// Exit codes
#define ASSERT_SUCCESS(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::success(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::failure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_NONZERO_EXIT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::nonzeroExit(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_EXITCODE(result, code) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::exitCode(r, #result, (code), __FILE__, __LINE__); }, true)

// Output
#define ASSERT_STDOUT_CONTAINS(result, content) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::stdoutContains(r, #result, (content), __FILE__, __LINE__); }, true)

#define ASSERT_STDERR_CONTAINS(result, content) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::stderrContains(r, #result, (content), __FILE__, __LINE__); }, true)

#define ASSERT_NO_STDOUT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noStdout(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_NO_STDERR(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noStderr(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_STDOUT_MATCHES(result, content) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::stdoutMatches(r, #result, (content), __FILE__, __LINE__); }, true)

#define ASSERT_STDERR_MATCHES(result, content) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::stderrMatches(r, #result, (content), __FILE__, __LINE__); }, true)

// Sanitizers
#define ASSERT_ASAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::asanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_NASAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noAsanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_UBSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::ubsanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_NUBSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noUbsanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_TSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::tsanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_NTSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noTsanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_LSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::lsanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_NLSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noLsanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_SAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::sanFailure(r, #result, __FILE__, __LINE__); }, true)

#define ASSERT_NSAN_FAILURE(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::noSanFailure(r, #result, __FILE__, __LINE__); }, true)

// Timing: the timeout itself is configured in RUN_ISO.
// The assertion checks the returned result.
#define ASSERT_TIMEOUT(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::timeout(r, #result, 0, __FILE__, __LINE__); }, true)

#define ASSERT_COMPLETES_WITHIN(result, timeLimit) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::completesWithin(r, #result, (timeLimit), __FILE__, __LINE__); }, true)

// General result metadata
#define ASSERT_STATUS(result, expected) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::executionStatus(r, #result, (expected), __FILE__, __LINE__); }, true)

#define ASSERT_CRASH_TYPE(result, expected) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::crashType(r, #result, (expected), __FILE__, __LINE__); }, true)

#define ASSERT_SIGNAL(result, signal) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::terminationSignal(r, #result, (signal), __FILE__, __LINE__); }, true)

#define ASSERT_KILLED(result) \
    testpp::internal::Assert::evaluate((result), [&](const auto& r) { return testpp::internal::impl_iso::killed(r, #result, __FILE__, __LINE__); }, true)


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