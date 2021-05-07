cmake_minimum_required(VERSION 3.19)
project(MCP C)

set(CMAKE_C_STANDARD 99)

add_executable(MCP MCP.c MCP_simulator.c MCP_simulator.h)