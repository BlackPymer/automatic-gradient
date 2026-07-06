# automatic-gradient

A minimal C++ autograd library implementing automatic differentiation for scalar-valued computation graphs.

## Supported operations

- Addition (`+`)
- Multiplication (`*`)

## Building

Compile with any C++17 compiler:

```bash
g++ -std=c++17 src/main.cpp src/float64.cpp -I include -o autograd_test
./autograd_test
```

## How it works

`Float64` wraps a `shared_ptr<float64>` that stores the value, gradient, and computation graph (parent nodes + operation). Each arithmetic operation builds a new node in the graph. Calling `backward()` traverses the graph and accumulates gradients via the chain rule.

## Known limitation

The current backward pass does **not** track visited nodes. When the same intermediate expression node is used multiple times in the computation graph (e.g., `t = x + y; z = t * t`), the gradient is **double-counted** because the node is visited twice by the stack-based traversal and its gradient is distributed to its parents twice.

For example, with `t = x + y; z = t * t` where `x=2, y=3`:
- Expected `dz/dx = 10`, `dz/dy = 10`
- Actual `dz/dx = 20`, `dz/dy = 20`

Note: direct reuse of a leaf variable (`z = x * x`) happens to work correctly because it has no parents, so processing it twice is harmless.

A topological sort with visited-set tracking would fix this.
