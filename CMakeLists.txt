cmake_minimum_required(VERSION 3.12)
project(minishell C)

set(CMAKE_C_STANDARD 99)

include_directories(headers)

file(GLOB minishell_srcs
        "srcs/minishell/*.c"
        "srcs/minishell/builtins/*.c"
        "srcs/libft/*.c"

)

add_executable(minishell ${minishell_srcs})

