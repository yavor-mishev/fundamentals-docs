# Shell

The **shell** is a program on your computer that allows you to interact with the OS via a text interface. Just like we have a GUI (Graphical User Interface) to interact with our computer using windows, icons, and menus, we have a CLI (Command Line Interface) to interact with our computer using text commands. The shell is the program that processes those commands and gives you the output.

There are many different shells in the wild and some are best for some specific use cases. For instance, Bash is a popular shell for Linux and macOS users, while PowerShell is commonly used in Windows environments. Each shell has its own syntax and features, but they all serve the same basic purpose: to allow you to interact with your computer through text commands.

### The prompt

The **prompt** is the text that appears in the terminal to indicate that the shell is ready to accept commands. It usually includes information about the current user, the hostname, and the current working directory. For example, a typical Bash prompt might look like this:

```bash
user@hostname:~/current/directory$
```

The $ symbol just shows that you are a regular user, while a # symbol would indicate that you are logged in as the root. We'll cover root and users later on.

### Basic commands

Here are some basic shell commands in Bash:

- `echo`: prints text to the terminal. we can pass parameters to the `echo` command to indicate what we want printed in the terminal. For example, `echo Hello, World!` will print "Hello, World!" to the terminal.
- `cd`: changes the current working directory. For example, `cd /home/user/Documents` will change the current directory to `/home/user/Documents`. The root of you filesystem is denoted by a single slash `/` and the home directory of the current user is denoted by `~`.
- `man`: shows the manual for a command. For example, `man ls` will show the manual for the `ls` command, which lists the contents of a directory. you can also use the short version of the manual command by using `--help` flag. For example, `ls --help` will show a brief help message for the `ls` command.
- `which`: shows where the command is located in the filesystem. For example, `which ls` will show the path to the `ls` command, which is usually `/bin/ls` or `/usr/bin/ls`. Essentially every command in the shell is a precompiled executable file that is stored somewhere in the filesystem and the `which` command helps you find where it is located. This is useful for troubleshooting and understanding how commands work.
- `which -a`: shows all the locations of the command in the filesystem. For example, `which -a ls` will show all the paths to the `ls` command, which can be useful if you have multiple versions of a command installed on your system.
- `cat`: prints the contents of a file to the terminal. For example, `cat file.txt` will print the contents of `file.txt` to the terminal.
- `head`: prints by default the first 10 lines of a file to the terminal. For example, `head file.txt` will print the first 10 lines of `file.txt` to the terminal. You can also specify the number of lines you want to print by using the `-n` flag. For example, `head -n 5 file.txt` will print the first 5 lines of `file.txt` to the terminal.

### The $PATH variable

The `$PATH` variable is an environment variable that contains a list of directories that the shell searches for executable files when you enter a command. When you type a command in the terminal, the shell looks for an executable file with that name in the directories listed in the `$PATH` variable. If it finds a match, it executes the command; if not, it returns an error message saying that the command was not found.

To see the directores included in your `$PATH` variable, you can use the `echo` command like this:

```bash
echo $PATH
```

If you have more than one command with the same name in different directories, the shell will execute the first one it finds in the order of the directories listed in `$PATH`. You can modify the `$PATH` variable to include additional directories or change the order of existing ones, which can be useful for customizing your shell environment and ensuring that you are using the correct version of a command.
