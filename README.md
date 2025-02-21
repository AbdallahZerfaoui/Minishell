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

---

### **Builtins**

Here’s the classification from **easiest to hardest** for implementing shell builtins, based on complexity, argument parsing, and system interaction:

---

### 1. **`pwd`**  
   → **Why easiest?** Simply calls `getcwd()` and prints the current directory. No argument parsing or logic.  
   → Example code:  
     ```c
     printf("%s\n", getcwd(buf, sizeof(buf)));
     ```

---

### 2. **`env`**  
   → **Why easy?** Iterates through the `environ` global variable and prints all environment variables. No parsing or logic.  
   → Example code:  
     ```c
     for (char **env = environ; *env; env++) printf("%s\n", *env);
     ```

---

### 3. **`exit`**  
   → **Why moderate?** Terminates the shell. Handles an optional exit status (e.g., `exit 3`). Basic integer parsing.  
   → Example logic:  
     ```c
     int status = 0;
     if (argc > 1) status = atoi(argv[1]);
     exit(status);
     ```

---

### 4. **`echo`**  
   → **Why moderate?** Prints arguments and handles `-n` (suppress newline). Requires iterating through arguments.  
   → Example logic:  
     ```c
     bool newline = true;
     if (strcmp(argv[1], "-n") == 0) { newline = false; argv++; }
     for (args...) printf("%s ", arg);
     if (newline) printf("\n");
     ```

---

### 5. **`cd`**  
   → **Why tricky?** Uses `chdir()` to change directories. Must handle errors (e.g., invalid path). May update `PWD`/`OLDPWD`.  
   → Example code:  
     ```c
     if (chdir(path) != 0) perror("cd error");
     else update_pwds_environment();
     ```

---

### 6. **`unset`**  
   → **Why harder?** Removes an environment variable. Requires validating variable names and edge cases.  
   → Example code:  
     ```c
     if (is_valid_var_name(var)) unsetenv(var);
     else error("invalid variable name");
     ```

---

### 7. **`export`**  
   → **Why hardest?** Parses `VAR=value` syntax, validates names, and updates the environment. Handles edge cases (e.g., `export VAR` with no value).  
   → Example logic:  
     ```c
     char *eq = strchr(arg, '=');
     if (eq) {
       *eq = '\0';
       setenv(arg, eq+1, 1);
     } else {
       setenv(arg, "", 1); // Export without a value
     }
     ```

---

### Suggested Implementation Order:
1. Start with **`pwd`** and **`env`** to get comfortable with basic system calls.  
2. Move to **`exit`** and **`echo`** to handle simple argument parsing.  
3. Tackle **`cd`** for filesystem interaction.  
4. Finish with **`unset`** and **`export`** for environment manipulation.

--- 

### Tests i should pass
**ls | cat << lim | >out** -> it should ask for the heredoc, create an empty out

