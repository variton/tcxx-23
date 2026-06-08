This example demonstrates how to use:

- `tl::expected`
- typed error propagation
- structured error handling
- policy-based validation
- compile-time composition
- concepts
- no virtual functions

The main goal of this example is to show how a modern C++ API can return
rich error information without using exceptions.

The interval domain is intentionally simple so the focus stays on:

- validation
- error propagation
- error inspection
- reusable policies

---

# The problem

Intervals are simple mathematical structures:

```cpp
[1, 10]
(1, 10)
[1, 10)
(1, 10]
```

but validation can fail in several meaningful ways:

- value below lower bound
- value above upper bound
- value exactly on an excluded bound

Returning only `true` or `false` loses useful information.

Instead, this example uses:

```cpp
tl::expected<void, ErrorInfo<IntervalError>>
```

This allows APIs to explain *why* validation failed.

---

# Error handling

The example uses the following generic error wrapper:

```cpp
template <typename ErrorType>
struct ErrorInfo {
  ErrorType type;
  std::string message;
};
```

and a helper for constructing errors:

```cpp
template <typename ErrorType>
auto unexpected(ErrorType error, std::string msg) {
  return tl::unexpected(ErrorInfo<ErrorType>{error, msg});
}
```

This makes error propagation concise:

```cpp
return err::unexpected(
    IntervalError::OutOfScopeOnLowerBound,
    "value is below the lower bound"
);
```

---

# Why use `tl::expected`?

`tl::expected` provides explicit error handling without exceptions.

Instead of:

```cpp
throw std::runtime_error(...);
```

functions return either:

- success
- structured error information

Example:

```cpp
auto result = interval.has(42);

if (!result.has_value()) {
    auto error = result.error();

    std::cout << error.message << '\n';
}
```

This makes failures:

- explicit
- typed
- easy to inspect
- easy to compose

---

# Why intervals?

Intervals are a good small example because they naturally produce validation errors.

For example:

```cpp
[1, 10]
```

can fail because:

- value < 1
- value > 10

while:

```cpp
(1, 10)
```

can additionally fail because:

- value == 1
- value == 10

This allows the example to demonstrate meaningful typed errors.

---

# Why policies?

All interval types share the same structure:

```cpp
lower_bound
upper_bound
```

but differ in their validation logic.

Policies isolate the validation behavior from the interval storage.

For example:

| Policy | Interval |
|---|---|
| `ClosedIntervalPolicy` | `[lower, upper]` |
| `OpenIntervalPolicy` | `(lower, upper)` |
| `HalfClosedLowerBoundPolicy` | `[lower, upper)` |
| `HalfClosedUpperBoundPolicy` | `(lower, upper]` |

This allows new interval semantics to be added without modifying the root interval implementation.

---

# Compile-time composition

The interval type is assembled statically:

```cpp
BasicInterval<int, ClosedIntervalPolicy<int>>
```

This provides:

- zero virtual dispatch
- no vtables
- no runtime polymorphism
- fully inlineable behavior

The compiler knows the exact validation policy at compile time.

---

# Concepts

Concepts are used to validate:

- valid bound types
- policy interfaces

This improves compiler diagnostics and prevents invalid policies from compiling.

Example:

```cpp
template <typename Policy, typename BoundType>
concept IntervalPolicy = ...;
```

---

# Example

```cpp
using ClosedInterval =
    math::BasicInterval<
        int,
        math::ClosedIntervalPolicy<int>
    >;

ClosedInterval interval{1, 10};

auto result = interval.has(42);

if (!result.has_value()) {
    auto error = result.error();

    std::cout << error.message << '\n';
}
```

---

# Summary

This example demonstrates how to combine:

- `tl::expected`
- typed errors
- structured error information
- policy-based validation
- compile-time composition
- concepts
- zero-cost abstractions

to build expressive APIs without exceptions or virtual interfaces.
