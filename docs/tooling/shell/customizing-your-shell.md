# Customizing Your Shell

Once you know the basics ([Shell Basics](shell-basics.md)) and which shell you're using ([Shells Compared](shells-compared.md)), you can make the shell faster and more pleasant to use. Customization happens in **startup files** — scripts your shell runs automatically when it opens. This page focuses on **zsh** (the macOS default) with notes for bash.

## Startup files and load order

When zsh starts, it sources several files in a fixed order. Knowing the order tells you *where to put what*:

| File | When it runs | Use it for |
|---|---|---|
| `~/.zshenv` | **Always**, every zsh (scripts too) | Universal environment variables |
| `~/.zprofile` | **Login** shells (once per session) | One-time setup: `PATH`, `eval` of tools like Homebrew |
| `~/.zshrc` | **Interactive** shells (each new window/tab) | Aliases, prompt, completions, key bindings |
| `~/.zlogin` | After `.zshrc`, login shells | Things that should run last at login |

> **Rule of thumb:** put things you *type with* (aliases, prompt, completion) in `~/.zshrc`. Put one-time environment setup (like `eval "$(brew shellenv)"`) in `~/.zprofile` so it isn't re-run in every subshell.

The **bash** equivalents are `~/.bash_profile` (login) and `~/.bashrc` (interactive). A classic gotcha: macOS terminals open *login* shells, so bash users often `source ~/.bashrc` from `~/.bash_profile` to get both.

To apply changes without opening a new terminal, **re-source** the file:

```bash
source ~/.zshrc      # or the shorthand:  . ~/.zshrc
```

## Aliases and functions

An **alias** is a short name for a longer command. Add these to `~/.zshrc`:

```bash
alias ll="ls -lah"
alias gs="git status"
alias ..="cd .."
```

When an alias isn't enough — because you need arguments or logic — use a **function**:

```bash
# make a directory and cd into it
mkcd() {
  mkdir -p "$1" && cd "$1"
}
```

> **Alias vs function:** use an alias for a fixed substitution; use a function when you need to handle arguments (`"$1"`, `"$2"`, …) or run multiple steps.

**Organizing many aliases:** a long list clutters `~/.zshrc`. A common pattern is to move them into their own file and source it:

```bash
# at the bottom of ~/.zshrc
[ -f ~/.config/zsh/aliases.zsh ] && source ~/.config/zsh/aliases.zsh
```

## Environment variables and PATH

Set environment variables your tools read, and extend `$PATH` to make new commands findable (see [`$PATH` in Shell Basics](shell-basics.md)):

```bash
export EDITOR="code"                 # default editor for git, etc.
export PATH="$HOME/.local/bin:$PATH" # add a directory, kept first so it wins
```

PATH-style `export` lines belong in `~/.zprofile` (login setup), while interactive niceties belong in `~/.zshrc`.

## The prompt

The prompt is just a variable (`PROMPT`/`PS1`) you can customize:

```bash
PROMPT='%n@%m %1~ %# '   # user@host shortdir %
```

Hand-tuning this gets fiddly fast. Most people use a prompt tool instead:

- **[Oh My Posh](https://ohmyposh.dev/)** — *what you use.* A cross-shell prompt engine driven by one JSON theme file, shared between your Mac and your Pi. See **[Prompt with Oh My Posh](oh-my-posh-prompt.md)** for how your theme works and every setting you can change.
- **[Starship](https://starship.rs/)** — a popular alternative. A single fast, cross-shell prompt (works in zsh, bash, fish). Shows git status, language versions, and more. Install and enable with one line:
  ```bash
  brew install starship
  echo 'eval "$(starship init zsh)"' >> ~/.zshrc
  ```
- **[Powerlevel10k](https://github.com/romkatv/powerlevel10k)** — a very fast, highly configurable zsh theme with a guided setup wizard.
- **[oh-my-zsh](https://ohmyz.sh/)** — a framework that bundles themes and plugins. Convenient, but heavier; many people now prefer plain zsh + Starship.

> **Fonts:** fancy prompts use icons that need a **[Nerd Font](https://www.nerdfonts.com/)** (e.g. "MesloLGS NF" or "FiraCode Nerd Font"). Install one, then select it in your terminal's settings, or the icons show as boxes.

## Completions and history tuning

Zsh's completion system makes Tab much smarter. Enable it in `~/.zshrc`:

```bash
autoload -Uz compinit && compinit
```

A few popular history settings so your shell remembers more and shares history across tabs:

```bash
HISTSIZE=10000
SAVEHIST=10000
setopt SHARE_HISTORY        # share history across sessions
setopt HIST_IGNORE_DUPS     # don't store consecutive duplicates
```

## Modern CLI replacements

These are friendlier, faster drop-ins for classic commands — all installable via Homebrew:

| Modern tool | Replaces | Why |
|---|---|---|
| **eza** | `ls` | Colours, icons, git status, tree view |
| **bat** | `cat` | Syntax highlighting + line numbers |
| **fd** | `find` | Simpler syntax, fast, sensible defaults |
| **ripgrep** (`rg`) | `grep` | Much faster recursive search |
| **zoxide** | `cd` | Jump to frequent dirs: `z proj` |
| **fzf** | — | Fuzzy finder; supercharges Ctrl-R history search |
| **git-delta** | `git diff` | Beautiful, readable diffs |
| **atuin** | history | Searchable, synced shell history |

```bash
brew install eza bat fd ripgrep zoxide fzf git-delta atuin
```

You can alias the classics to the new tools so muscle memory still works:

```bash
alias ls="eza"
alias cat="bat"
```

---

## Your macOS setup right now

Here's where *your* machine stands and the highest-value tweaks, based on your current configuration.

**What you have (a solid baseline):**

- **zsh 5.9** as your default shell, running inside **VS Code's integrated terminal**.
- **Homebrew** installed on Apple Silicon (`/opt/homebrew`), correctly initialised via `eval "$(brew shellenv)"`.
- A working `~/.zshrc` with a lot of `bun` game aliases, an **Oh My Posh** prompt (see [Prompt with Oh My Posh](oh-my-posh-prompt.md)), and the zsh-autosuggestions + zsh-syntax-highlighting plugins. There's still no completion or history tuning, and none of the modern CLI tools are installed yet.

**Quick wins (biggest impact first):**

1. **Add fuzzy history + smart cd:**
   ```bash
   brew install fzf zoxide
   # then add to ~/.zshrc:
   #   eval "$(zoxide init zsh)"
   #   source <(fzf --zsh)
   ```
2. **Tune completions & history** — add the `compinit` and `HISTSIZE`/`setopt` snippets from the sections above to `~/.zshrc`.
3. **Try the modern tools** — `brew install eza bat`, then optionally alias `ls`/`cat`.

**Tidy-ups specific to your config:**

- **Organize the aliases.** Your `~/.zshrc` has ~40 near-identical `bun gen-manifest … && bun start …` game aliases. Either group them under comment headers, or move them to `~/.config/zsh/aliases.zsh` and source it. Because they follow one pattern (only the package name changes), they're a good candidate for a single helper function or a generated file:
  ```bash
  # one function instead of 40 aliases
  game() {
    bun gen-manifest --filter="$1" && bun start --filter="$1"
  }
  # usage: game @backseatgaming/pyrofox
  ```
- **Remove a redundant line.** `eval "$(/opt/homebrew/bin/brew shellenv)"` runs in **both** `~/.zprofile` and `~/.zshrc`. It only needs to be in `~/.zprofile` (login setup) — you can delete it from `~/.zshrc`.
- **Orphan fish config.** You have a `~/.config/fish` directory but **fish isn't installed**. It's harmless; remove it if you want a tidy `~/.config`.
- **Leave the Kiro CLI blocks alone.** The `Kiro CLI pre`/`post` blocks must stay at the very top and bottom of `~/.zshrc`/`~/.zprofile` — add your customizations *between* them, not outside.

> **Note:** the snippets above are examples to apply yourself when you're ready — this guide doesn't change your dotfiles for you. Re-source (`source ~/.zshrc`) or open a new terminal after editing.

## Resources

- [Oh My Posh](https://ohmyposh.dev/) · [Starship](https://starship.rs/)
- [Nerd Fonts](https://www.nerdfonts.com/)
- [oh-my-zsh](https://ohmyz.sh/) · [Powerlevel10k](https://github.com/romkatv/powerlevel10k)
- [Awesome zsh plugins](https://github.com/unixorn/awesome-zsh-plugins)
