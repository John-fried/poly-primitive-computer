# Poly Primitive Computer

What is **Poly Primitive Computer**? **Poly Primitive Computer** (or **PPC**) is an esoteric programming language (esolang) and computing tool that shares a slight resemblance to **Assembly**.

# Hello World!

**PPC** has absolutely no support for strings; it operates strictly on **ASCII Values**. Cutting straight to the chase, here is an example of how to print `Hello World!` in **PPC**:

```asm
mov 0, [trans H]
mov 1, [trans e]
mov gpr0, [trans l]  ; Store 'l' in gpr0
mov 2, gpr0          ; Use gpr0 (l)
mov 3, gpr0          ; Use gpr0 (l)
mov gpr1, [trans o]  ; Store 'o' in gpr1
mov 4, gpr1          ; Use gpr1 (o)
mov 5, 32            ; Space ' '
mov 6, [trans W]
mov 7, gpr1          ; Use gpr1 (o)
mov gpr2, [trans r]  ; Store 'r' in gpr2
mov 8, gpr2          ; Use gpr2 (r)
mov 9, gpr0          ; Use gpr0 (l)
mov 10, [trans d]
mov 11, [trans !]
print 0..11          ; Print indices 0-11

```

Save the file as `Hello.ppc` and run it in your terminal:

```bash
$ ppc ./Hello.ppc

```

The message `Hello World!` will appear on the screen.

> A sample file is available at `tests/hello_world.ppc` for you to try.

# Syntax

As introduced above, here are the core syntax features:

**1. Subevaluate**:
By using brackets **"["** and **"]"**, the content inside is executed first, and the result is returned to the instruction. Example process:

```asm
1. mov 0, [trans A]
2. mov 0, 65 <-- Result of 'trans A' instruction (preprocess result)

```

> `trans` is an instruction to translate a single character into its actual **ASCII Value**. Use this if you want to avoid the "hardcore" aspect of pure esoteric coding.

**2. Comments**:
Written by adding a semicolon ";" just like in **Assembly**. The ";" signals the start of a comment, which is useful for keeping track of your own code logic.

# Memory Mechanics

**PPC** stores integer values in memory. For example, `mov 12, 52` will store the integer 52 into memory index 12.

**Important:** The higher the memory index you access, the more memory **PPC** automatically allocates to accommodate it. Therefore, keep your indices low to save memory, or utilize **Registers** like `gpr0, gpr1, gpr2`.
