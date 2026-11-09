# Shells Compared

There are several shells you'll run into, and the choice matters for both daily comfort and script portability. This page explains what they are, how they differ, and how to pick. For what a shell *is*, start with [Terminal vs Shell](index.md); for everyday commands, see [Shell Basics](shell-basics.md).

## POSIX and `sh`: the common baseline

**POSIX** is a standard that defines a baseline shell language and a set of behaviours every Unix-like system should support. The original Bourne shell, `sh`, is that baseline. Modern shells like bash and zsh are *supersets* — they can run almost all `sh` scripts but add their own extra features on top.

> **Why this matters:** if a script only uses POSIX `sh` features, it runs almost anywhere. If it uses bash- or zsh-only features, it breaks on systems that don't have those shells. This is the key trade-off between portability and convenience.

On most systems `/bin/sh` is not its own shell anymore — it's a link to bash or `dash` running in a stripped-down POSIX-compatible mode.

## The shells at a glance

| Shell | Default on | POSIX / scripting | Interactive UX | Config file | Notes |
|---|---|---|---|---|---|
| **sh** | (baseline) | The POSIX standard | Minimal | `~/.profile` | Maximum portability; few comforts |
| **bash** | Most Linux distros | Near-POSIX, the scripting standard | Decent | `~/.bashrc`, `~/.bash_profile` | Everywhere; macOS ships an ancient 3.2 |
| **zsh** | macOS (since Catalina) | Mostly bash-compatible | Excellent | `~/.zshrc` | Great completion & globbing; big plugin scene |
| **fish** | (opt-in) | **Not POSIX** | Best out of the box | `~/.config/fish/config.fish` | Autosuggestions & highlighting built in; different syntax |
| **PowerShell** | Windows | Its own object-based language | Strong | `$PROFILE` | Passes objects, not text; cross-platform too |

## Bash — the lingua franca

**Bash** (Bourne Again SHell) is the most widely installed shell and the de facto standard for shell *scripts*. If you write a `.sh` file for a server, CI pipeline, or Docker image, it's almost certainly bash or POSIX sh.

- **Strength:** ubiquity. A bash script runs nearly everywhere.
- **Quirk on macOS:** Apple still ships **bash 3.2** from 2007 (later versions are GPLv3-licensed, which Apple avoids). It's missing many modern features. If you script in bash on a Mac, install a current version with `brew install bash`.

## Zsh — the comfortable daily driver

**Zsh** (Z shell) has been the macOS default since Catalina. It's largely compatible with bash for interactive use and scripting, but adds quality-of-life features:

- Smarter, configurable **tab completion** (it completes flags, git branches, etc.).
- Powerful **globbing** (e.g. `ls **/*.md` matches recursively).
- Spelling correction, named directories, and a rich **plugin and theme ecosystem** (oh-my-zsh, Powerlevel10k, and the cross-shell Starship prompt).

For most people, zsh is the sweet spot: familiar enough to reuse bash habits, but much nicer interactively. See [Customizing Your Shell](customizing-your-shell.md) to make it shine.

## Fish — the friendliest, but different

**Fish** (Friendly Interactive SHell) gives you the best experience *with zero configuration*:

- **Autosuggestions** as you type (greyed-out completions from your history).
- **Syntax highlighting** that flags mistakes before you hit Enter.
- Clean, discoverable tab completion and built-in help.

The catch: **fish is not POSIX-compatible**. Its scripting syntax differs (e.g. setting a variable is `set name value`, not `name=value`), so you can't paste most bash snippets from the internet directly, and you wouldn't use fish for portable system scripts.

> **Common setup:** use fish (or zsh + Starship) as your *interactive* shell for comfort, while still writing your *scripts* in bash/POSIX sh for portability. Your login shell and the shell your scripts run in don't have to be the same.

## PowerShell — the Windows native

**PowerShell** is Microsoft's shell, default on Windows and available cross-platform. Its big difference: commands pass **structured objects** between each other instead of plain text, which makes complex automation cleaner. Its syntax is unlike the Unix shells, so it's a separate world rather than a bash variant.

## What should you use?

- **Interactive daily driver:** **zsh** — you very likely already have it as your default on macOS. Add [Starship](customizing-your-shell.md) and you get fish-like polish while keeping bash compatibility. Choose **fish** instead if you value the best out-of-the-box UX and don't mind its different syntax.
- **Writing scripts:** **bash** (or strict POSIX `sh`). Start scripts with `#!/usr/bin/env bash` so they find a modern bash, and avoid zsh/fish-only syntax if the script must run elsewhere.
- **On Windows automation:** **PowerShell**, or use WSL to get a real Linux bash/zsh.

> **Remember:** changing your interactive shell (with `chsh`, see [Terminal vs Shell](index.md)) doesn't change what language your `.sh` scripts use — that's set by each script's shebang line (`#!/usr/bin/env bash`).

## Next step

- [Customizing Your Shell](customizing-your-shell.md) — config files, prompts, aliases, plugins, and modern CLI tools, with concrete recommendations for your Mac.
