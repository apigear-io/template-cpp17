# C++ 17 Blueprint

[![Build & Test](https://github.com/apigear-io/template-cpp17/actions/workflows/ci_build_test.yml/badge.svg)](https://github.com/apigear-io/template-cpp17/actions/workflows/ci_build_test.yml)
[![Feature Configurations](https://github.com/apigear-io/template-cpp17/actions/workflows/ci_build_features.yml/badge.svg)](https://github.com/apigear-io/template-cpp17/actions/workflows/ci_build_features.yml)
[![Sanitizers](https://github.com/apigear-io/template-cpp17/actions/workflows/ci_build_sanitizers.yml/badge.svg)](https://github.com/apigear-io/template-cpp17/actions/workflows/ci_build_sanitizers.yml)
[![Goldenmaster](https://github.com/apigear-io/template-cpp17/actions/workflows/ci_generate.yml/badge.svg)](https://github.com/apigear-io/template-cpp17/actions/workflows/ci_generate.yml)

A C++17 blueprint template for [ApiGear](https://apigear.io/) that generates complete projects from API definitions (YAML). Uses [CMake](https://cmake.org/) as build system and [Poco](https://pocoproject.org/) for network connections.

## Features

Features are individually enabled in the solution file for code generation.

| Feature | Description | Dependencies |
|---------|-------------|--------------|
| **api** | Abstract interfaces and data structures | - |
| **core** | JSON serialization, publishers, thread-safe decorators | api |
| **scaffold** | Project structure with implementations and tests | - |
| **monitor** | API traffic tracing decorators | api, core, apigear |
| **olink** | [ObjectLink](https://objectlinkprotocol.net/) IPC client/server adapters | api, core, apigear |
| **mqtt** | [MQTT v5](https://mqtt.org/) IPC client/server adapters | api, core, apigear |
| **nats** | [NATS](https://nats.io/) IPC client/server adapters | api, core, apigear |
| **apigear** | Support library for monitoring and IPC features | - |
| **examples** | Usage examples for generated code | - |
| **conan** | [Conan](https://conan.io/) package manager files | - |

## Building

### With CMake

```bash
cd goldenmaster
cmake -Bbuild -DCMAKE_INSTALL_PREFIX=tmp -DTEST_FETCH_DEPS=ON
cmake --build build/
cmake --build build/ --target install
```

With tests enabled:

```bash
cmake -Bbuild -DBUILD_TESTING=ON -DTEST_FETCH_DEPS=ON
cmake --build build/
ctest --test-dir build/ --output-on-failure
```

### With Conan

```bash
# Linux / macOS
bash goldenmaster/scripts/test_conan.sh

# Windows
goldenmaster\scripts\test_conan.bat
```

## CI

| Workflow | What it checks | Platforms |
|----------|---------------|-----------|
| **Build & Test** | Full build with CMake and Conan | Ubuntu, Windows, macOS |
| **Feature Configurations** | Each feature builds in isolation | Ubuntu |
| **Sanitizers** | ASan+UBSan and TSan for memory safety and thread safety | Ubuntu |
| **Goldenmaster** | Generated code matches templates | Ubuntu |

## Template Development

This repository is a template project: `templates/` contains Go template files (`.tpl`), and `goldenmaster/` is the reference output that must always match what the generator produces.

```bash
go run main.go install     # Install the apigear CLI
go run main.go gentest     # Generate code into test/
go run main.go diff        # Generate + diff test/ vs goldenmaster/
go run main.go formatstyle # Run clang-format on goldenmaster
go run main.go teststyle   # Verify clang-format compliance
```

Workflow for template changes:

1. Edit templates in `templates/`
2. Run `go run main.go gentest` to generate into `test/`
3. Run `go run main.go diff` to verify against `goldenmaster/`
4. Update `goldenmaster/` to match the intended output
5. CI validates the goldenmaster is up-to-date on every PR
