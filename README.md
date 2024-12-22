# Minishell

### **Big Picture of the Minishell Project**

The **Minishell project** is about creating a simple UNIX shell in C, simulating the behavior of Bash. The goal is to deepen your understanding of processes, file descriptors, and core shell functionalities while adhering strictly to specified requirements and constraints. The shell will serve as a basic command-line interpreter, implementing essential features and interacting with the operating system's underlying mechanisms.

---

### **Main Challenges**
1. **Process and File Descriptor Management**
   - Handling multiple processes and ensuring proper use of system calls like `fork`, `execve`, and `pipe`.
   - Correctly closing file descriptors to avoid leaks.

2. **Signal Handling**
   - Responding to signals like `CTRL+C`, `CTRL+D`, and `CTRL+\` with precise behavior (e.g., exiting, ignoring, or restarting a prompt).

3. **Input Parsing**
   - Parsing commands while respecting quotes (single and double) and handling special characters such as `$` for environment variables.

4. **Builtins Implementation**
   - Implementing Bash-like commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) with strict compliance to required behaviors.

5. **Redirections and Pipes**
   - Supporting redirection operators (`<`, `>`, `<<`, `>>`) and pipelines (`|`), managing input and output streams between processes.

6. **Memory Management**
   - Ensuring there are no memory leaks, apart from those caused by the `readline` function.

---

### **Key Constraints**
1. **Norm Compliance**
   - The code must adhere to strict formatting rules and avoid runtime errors such as segmentation faults or double frees.

2. **Limited Global Variables**
   - The only global variable allowed is for signal handling. It cannot store any additional information.

3. **Mandatory Functions and Libraries**
   - Restricted to specific external functions like `readline`, `malloc`, `fork`, `execve`, etc. You must also use `libft` if provided.

4. **Interactive Mode Requirements**
   - Behavior during interaction should mimic Bash, including correct responses to key combinations.

5. **Performance**
   - Efficiently handle redirections, pipes, and builtins without unnecessary resource usage.

6. **No Undefined Behaviors**
   - Inputs like unclosed quotes or unsupported special characters should not crash the shell.

7. **Bonus Dependencies**
   - Bonus features like logical operators (`&&`, `||`) and wildcards (`*`) are assessed only if the mandatory part is flawless.

---

### **Deliverables**
1. **Codebase**
   - Comprising a Makefile, `.c`, and `.h` files adhering to naming conventions.
2. **Git Repository**
   - The project must be submitted through the assigned repository for grading.
3. **Memory Management**
   - All heap-allocated memory must be freed unless exceptions are specified.

---

### **Potential Pitfalls**
- Mismanagement of file descriptors leading to resource leaks.
- Misinterpreting parsing rules, especially for quotes and special characters.
- Incorrect signal handling behavior.
- Failing to free memory or handling errors from `readline`.
- Non-compliance with the Norm leading to disqualification. 

This project requires a meticulous approach to C programming, deep understanding of the shell's architecture, and precise adherence to the provided requirements.
