# `tcxx`

> Modern C++20 templated header library.

`tcxx` provides a modern C++ set of utilities for modern C++ projects.

---

## Features

- Modern C++20 codebase
- Docker-based reproducible development environment
- Automated local CI workflow
- Doxygen documentation generation
- Valgrind integration
- Coverage report generation

---

## Requirements

| Dependency | Version |
|---|---|
| GCC | 15+ |
| CMake | 4.2.3+ |
| Ninja | Latest |
| Docker | Latest |

The local tooling also expects common development utilities such as
`ctest`, `valgrind`, `clang-format`, `lcov`, and Python 3.

---

## Quick Start

### Build the Docker Image

```bash
cd ubuntu-resolute-gcc-15

docker build -t tcxx:1.0 .
```

---

### Launch the Development Container

Run the following command from the project root directory:

```bash
docker run \
    --name=ctcxx \
    --hostname=cypher \
    -v $PWD:/home/cxx-core \
    --net=host \
    --restart=no \
    -it tcxx:1.0 /bin/bash
```

---

## Build & Test

Inside the container:

```bash
cd /home/cxx-core

./local-ci.sh
```

The local CI pipeline performs the following tasks:

- Configure and build the project
- Execute unit tests
- Generate an HTML unit test report
- Generate coverage reports
- Generate Doxygen documentation
- Execute Valgrind analysis
- Run `clang-format`

---

## Using `tcxx` as a Dependency

When `tcxx` is pulled into another project as a dependency, run the bootstrap
script from the `tcxx` checkout before configuring the consuming project:

```bash
./bootstrap.sh
```

The bootstrap script updates apt metadata and installs `libexpected-dev`.

---

## Documentation & Reports

Generated artifacts are available under the `reports/` directory.

### Coverage Report

Open in your browser:

```text
reports/coverage_html/index.html
```

---

### Doxygen Documentation

Open in your browser:

```text
reports/html/index.html
```

---

### Valgrind Report

Open in your browser:

```text
reports/valgrind-report.html
```

---

## Project Structure

```text
.
├── include/                  # Public headers
├── test/                     # Unit tests
├── examples/                 # Example code
├── tools/                    # Report generation helpers
├── reports/                  # Generated reports
├── ubuntu-resolute-gcc-15/   # Docker environment
├── docs/                     # Documentation
├── bootstrap.sh              # System dependency bootstrap
├── build.sh                  # Debug/release build helper
├── local-ci.sh               # Local CI workflow
└── CMakeLists.txt
```

---

## Development Workflow

Recommended development workflow:

1. Build the Docker image
2. Launch the development container
3. Execute the local CI pipeline
4. Inspect generated reports and logs

---

## Design Goals

- Clean and maintainable C++20 architecture
- Reproducible builds and tooling
- Automated quality analysis

---

## Roadmap

- [ ] C++23 modules support

---

## License

Licensed under the MIT License.

See `LICENSE` for details.
