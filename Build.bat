@echo off
setlocal

set BUILD_SFML_ARG=

:parse_args
if "%~1"=="" goto after_args
if "%~1"=="--sfml-src" (
    set BUILD_SFML_ARG=-DBUILD_SFML_FROM_SOURCE=ON
)
shift
goto parse_args

:after_args
cmake -B build . %BUILD_SFML_ARG%
cmake --build build