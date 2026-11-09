# Shell Basics

The **shell** is a program that lets you interact with the operating system through a text interface. Just as a GUI (Graphical User Interface) lets you use windows, icons, and menus, a CLI (Command Line Interface) lets you use typed commands. The shell reads those commands, runs them, and shows you the output.

There are many shells, each suited to different uses — **Bash** is common on Linux and macOS, **Zsh** is the macOS default, and **PowerShell** is common on Windows. Their syntax differs slightly, but all serve the same purpose. This page covers the everyday commands you'll use in a Bash/Zsh-style shell. For how the shells differ, see [Shells Compared](shells-compared.md).

## The prompt

The **prompt** is the text the shell prints to say it's ready for input. It usually shows the current user, the hostname, and the current directory. A typical Bash prompt looks like:

```bash
user@hostname:~/current/directory$
```

The `$` means you're a regular user; a `#` means you're logged in as **root** (the all-powerful administrator account). You can completely change how the prompt looks — see [Customizing Your Shell](customizing-your-shell.md).

## Anatomy of a command

Most commands follow the same shape:

```bash
command -flags arguments
```

```bash
ls -l ~/Documents
#  │  │   └── argument: what to act on
#  │  └────── flag/option: how to behave (-l = long format)
#  └───────── command: the program to run
```

Flags can usually be combined (`ls -la` = `ls -l -a`). Long-form flags use two dashes (`ls --all`).

## Moving around the filesystem

- `pwd` — **print working directory**: shows where you currently are.
- `cd` — **change directory**. `cd /home/user/Documents` goes there by absolute path. `/` is the filesystem root and `~` is your home directory. Handy shortcuts: `cd ~` (home), `cd ..` (up one level), `cd -` (back to previous directory).
- `ls` — **list** directory contents. Useful flags: `ls -l` (long/details), `ls -a` (include hidden dotfiles), `ls -h` (human-readable sizes), often combined as `ls -lah`.

## Working with files

- `mkdir` — make a directory. `mkdir -p a/b/c` creates nested directories in one go.
- `cp` — copy. `cp file.txt backup.txt`; copy folders with `cp -r src/ dest/`.
- `mv` — move **or** rename. `mv old.txt new.txt` renames; `mv file.txt ~/Documents/` moves.
- `rm` — remove. `rm file.txt` deletes a file; `rm -r folder/` deletes a folder.
- `touch` — create an empty file (or update its timestamp).

> **⚠️ `rm` is permanent — there is no Trash/Recycle Bin on the command line.** `rm -rf` deletes a folder and everything inside it without asking. Double-check the path before running it, and never run `rm -rf` on a path you don't fully understand.

## Reading and searching files

- `cat` — print a whole file. `cat file.txt`.
- `head` — first lines (default 10). `head -n 5 file.txt` shows the first 5.
- `tail` — last lines (default 10). `tail -n 20 log.txt`; `tail -f log.txt` *follows* a file live as it grows (great for logs).
- `grep` — search for text. `grep "error" log.txt` prints matching lines; `grep -r "TODO" .` searches recursively from the current folder.
- `find` — find files by name/type. `find . -name "*.md"` lists every Markdown file beneath the current directory.

## Getting help

- `man` — the **manual** for a command. `man ls` opens the full manual (press `q` to quit).
- `--help` — most commands print a quick summary with `ls --help`.
- `which` — show where a command lives on disk. `which ls` → `/bin/ls`. Every command is an executable file somewhere on your system, and `which` finds it. `which -a ls` shows **all** matches if several versions are installed — useful when troubleshooting which one actually runs.
- `echo` — print text. `echo Hello, World!` prints `Hello, World!`. Also used to inspect variables: `echo $PATH`.

## Pipes and redirection

These let you connect commands together and control where their input and output go — one of the most powerful ideas in the shell.

| Symbol | Name | What it does |
|---|---|---|
| `\|` | pipe | Send one command's output into the next command's input |
| `>` | redirect (overwrite) | Write output to a file, replacing its contents |
| `>>` | redirect (append) | Write output to the end of a file |
| `<` | input redirect | Feed a file in as a command's input |
| `2>` | error redirect | Send error messages (stderr) to a file |

Examples:

```bash
ls -l | grep ".md"          # list files, keep only lines containing ".md"
echo "hello" > notes.txt    # write "hello" into notes.txt (overwrites)
echo "world" >> notes.txt   # append "world" to notes.txt
cat notes.txt | wc -l       # count the lines in notes.txt
command 2> errors.log       # save error output to a file
```

> **Mental model:** every command has three streams — **stdin** (input), **stdout** (normal output), and **stderr** (errors). Pipes and redirects just rewire where those streams go.

## History and keyboard shortcuts

The shell remembers what you've typed, and editing the command line is much faster with shortcuts.

- `history` — list your recent commands.
- `!!` — re-run the last command (e.g. `sudo !!` re-runs it with `sudo`).
- **Ctrl-R** — reverse-search your history; start typing and it finds matching past commands.
- **Tab** — autocomplete a command, file, or path. Press twice to see all options.
- **Up / Down arrows** — step through previous commands.

Line-editing shortcuts (these work in most shells):

| Shortcut | Action |
|---|---|
| **Ctrl-A** | Jump to the start of the line |
| **Ctrl-E** | Jump to the end of the line |
| **Ctrl-U** | Delete from cursor to start of line |
| **Ctrl-K** | Delete from cursor to end of line |
| **Ctrl-W** | Delete the word before the cursor |
| **Ctrl-C** | Cancel the current command |
| **Ctrl-D** | Send end-of-input / exit the shell |
| **Ctrl-L** | Clear the screen (same as `clear`) |

## Variables and the environment

The shell can store values in **variables**. There are two kinds:

```bash
name="Yavor"        # a shell variable — only this shell sees it
echo "$name"        # use it with a $ prefix

export EDITOR="code"   # an environment variable — passed down to programs you run
```

A **shell variable** lives only in your current shell. An **environment variable** (created with `export`) is also handed to any program the shell launches. That's why tools read settings like `$EDITOR`, `$LANG`, or `$PATH` from the environment.

### The `$PATH` variable

`$PATH` is an environment variable holding a list of directories the shell searches for executables. When you type a command, the shell looks for a matching program in each `$PATH` directory **in order** and runs the first one it finds; if none match, you get "command not found".

```bash
echo $PATH          # show the directories, separated by colons
```

If two commands share a name in different directories, the one earlier in `$PATH` wins. You can add directories or reorder them to control which version of a tool runs — this is configured in your shell's startup files, covered in [Customizing Your Shell](customizing-your-shell.md).

## Next steps

- [Shells Compared](shells-compared.md) — bash vs zsh vs fish, and what to use.
- [Customizing Your Shell](customizing-your-shell.md) — config files, prompts, aliases, and modern tools.
