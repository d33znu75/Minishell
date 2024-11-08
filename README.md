# Minishell

Minishell is a simple Unix-like shell implementation written in C. The project aims to replicate basic shell functionality, such as command execution, piping, input/output redirection, and environment variable handling. 

In this project, a significant focus was placed on building an Abstract Syntax Tree (AST) to represent and parse the shell commands, ensuring a more structured and modular approach to command execution.

## Features

- **Command Parsing**: Parse user input into executable commands using an Abstract Syntax Tree (AST).
- **Redirection**: Support for input and output redirection (`<`, `>`, `>>`).
- **Pipes**: Handle piped commands (`|`), enabling the chaining of multiple commands.
- **Environment Variables**: Implement basic environment variable expansion (`$VAR`).
- **Signal Handling**: Gracefully handle signals such as SIGINT (Ctrl+C).
- **Built-in Commands**: Implement a set of built-in commands, including `cd`, `echo`, `exit`, etc.
- **Process Management**: Manage child processes for command execution using `fork()` and `exec`.

## Built-in Commands

Minishell supports several built-in commands, including:

- `cd [dir]`: Change the current working directory.
- `echo [text]`: Print the text to the standard output.
- `exit`: Exit the shell.
- `env`: Display environment variables.
- `pwd` : Print the current working directory.
- `export [VAR=value]`: Set or export an environment variable.
- `unset [VAR]`: Remove an environment variable.
