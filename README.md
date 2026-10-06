# minishell

A Unix shell written from scratch in C: lexer and parser, quoting, variable expansion, pipes,
redirections, heredocs, builtins and signal handling. No external parsing library — only
`readline` for line editing.

**42 Roma Luiss — curriculum project (2025), team of three.** Archived as delivered: this is a
study project, not a maintained tool.

## Build

Requirements: a C compiler, GNU `make`, and the readline development headers
(`libreadline-dev` on Debian/Ubuntu, `readline` on Arch).

```bash
make            # produces ./minishell
make clean      # objects
make fclean     # objects + binary
```

## Run

```bash
./minishell
matt@:/cwd$ echo "hello" | cat
```

The prompt shows `user@:<current directory>$`.

## What it implements

- **Line editing and history** via GNU readline; history is cleared on exit.
- **Pipes**: `cmd1 | cmd2 | cmd3`, arbitrary length.
- **Redirections**: `<`, `>`, `>>`, and heredoc `<<` (with delimiter).
- **Quoting**: single quotes are literal (`'$HOME'` prints `$HOME`); double quotes group
  spaces into one argument, keep `|` and `<`/`>` literal, and still expand variables.
- **Expansion**: `$VAR` from the environment and `$?` (exit status of the last command).
- **Builtins**: `echo` (with `-n`), `cd` (`~`, relative and absolute paths; keeps `PWD` and
  `OLDPWD` updated), `pwd`, `env`, `export`, `unset`, `exit`.
- **External commands**: resolved through `PATH`, executed with `fork` + `execve`, exit status
  propagated back to `$?`.
- **Signals**: `SIGINT` (Ctrl-C) aborts the line and returns a fresh prompt, in a child process
  it terminates the command; `SIGQUIT` (Ctrl-\\) is ignored at the prompt; `SIGCHLD` reaps
  children and reports `Quit (core dumped)` when a child dies of SIGQUIT.
- **SHLVL** incremented on start, like bash.

Verified by running the binary:

```
matt@:/minishell$ echo "hello | world"
hello | world
matt@:/minishell$ ls /nonexistent | wc -l
ls: cannot access '/nonexistent': No such file or directory
0
matt@:/minishell$ export TESTVAR=42
matt@:/minishell$ echo $TESTVAR
42
matt@:/minishell$ echo [$TESTVAR]
[]
matt@:/minishell$ pwd
/home/matt/repos/matteo-genovese/minishell
```

## What it does not implement

Scope is the 42 subject, so these are deliberate gaps rather than bugs:

- wildcards / globbing
- `&&`, `||` and `;` (one command line per prompt)
- subshells `(...)`, command substitution `` `…` ``/`$(…)`, arithmetic `$((…))`
- job control (`jobs`, `fg`, `bg`, `&`), aliases, history file persistence

## Layout

```
src/parser/       tokenising, quotes, expansion, syntax errors
src/command/      pipeline setup, heredoc, fd handling, fork/execve, PATH lookup
src/builtins/     echo, cd, pwd, env, export, unset, exit
src/env/          environment array, SHLVL
src/signals/      SIGINT / SIGQUIT / SIGCHLD handling
libs/libft/       the libft used across 42 projects
```

## Credits

Team project: Matteo Genovese, Federico De Sisti, Andrea Starrantino.

Subject and assignment belong to [42](https://42.fr); this repository is a student
implementation of it. If you are a 42 student, reading this code to pass the project is on you:
the school's rules apply to you, not to this repository.
