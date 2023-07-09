cmake_minimum_required(VERSION 3.21)
project(policy)

cmake_policy(PUSH)
cmake_language(DEFER CALL cmake_policy POP)
