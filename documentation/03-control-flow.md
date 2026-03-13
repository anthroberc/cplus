# Control Flow in C+

C+ provides comprehensive control flow structures to manage program execution.

## Conditional Statements

Use `if`, `elif`, and `else` to execute code based on conditions. Note that every control structure must end with a semicolon.

```cplus
if (x > 10) {
    print("Greater than 10");
} elif (x == 10) {
    print("Exactly 10");
} else {
    print("Less than 10");
};
```

## Loops

The `while` loop continues execution as long as a condition is true.

```cplus
let i = 0;
while (i < 5) {
    print(i);
    i = i + 1;
};
```

## Loop Control

- **break**: Exit the current loop immediately.
- **continue**: Skip the rest of the current iteration and move to the next.
- **pass**: A null operation that does nothing.
