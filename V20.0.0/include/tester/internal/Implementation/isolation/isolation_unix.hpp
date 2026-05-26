#pragma once

#ifndef ISO_UNIX_H
#define ISO_UNIX_H

#include <functional>
#include <unistd.h>

namespace internal {
    namespace impl_iso {
        template <typename R, typename Args>
        inline void isolateRun(std::function<R(Args...)> func) {
            pid_t child_pid = fork();

            if (child_pid == -1) {
                //fork failed
            } else if (child_pid > 0) {
                //parent
                int child_status;
                pid_t result = waitpid(child_pid, &child_status, WNOHANG);
            } else {
                _exit();
            }
        }
    }
}

#endif