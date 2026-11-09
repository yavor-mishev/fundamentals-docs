# Your Prompt with Oh My Posh

This page explains what the prompt is, how **Oh My Posh** draws it, how your theme is put together, and how we added a **Node.js version** segment that only shows up inside Node projects. The second half is a reference for the settings you can change and the values each one accepts.

## Recap: terminal, shell, prompt

Three different things are working together every time you type a command:

| Piece | What it is | Your example |
|---|---|---|
| **Terminal** | The window app that draws text and sends your keystrokes | Terminal.app, iTerm2, VS Code's terminal |
| **Shell** | The program running *inside* the terminal that reads your command, runs it, and prints the result | `zsh` |
| **Prompt** | The text the shell prints *before* each command to say "ready, type here" | `  ~  ❯` |

The shell is the part you configure. The common ones are:

| Shell | Notes |
|---|---|
| **sh** | The original Unix shell (POSIX). Minimal, and the most portable choice for scripts. |
| **bash** | "Bourne Again SHell". Default on most Linux systems for years, and still the most common in scripts and servers. |
| **zsh** | Mostly bash-compatible, with better completion, globbing and themes. The **macOS default** since Catalina. Your Mac and your Pi both use it. |
| **fish** | Friendly out of the box (autosuggestions, colours), but **not** bash-compatible. |

More detail is in [Terminal vs Shell](index.md) and [Shells Compared](shells-compared.md).

## What a prompt actually is

The prompt is just a **shell variable** that holds a string. Before each command, the shell expands the string and prints it.

- In **zsh** the variable is `PROMPT` (or `PS1`). The right-hand side is `RPROMPT`.
- In **bash** it's `PS1`.

The string can contain escape codes that the shell fills in:

```bash
# zsh
PROMPT='%n@%m %1~ %# '      # → yavor@ungabunga projects %
# bash
PS1='\u@\h \W \$ '           # → yavor@ungabunga projects $
```

| zsh | bash | Expands to |
|---|---|---|
| `%n` | `\u` | Username |
| `%m` | `\h` | Hostname |
| `%~` | `\w` | Current directory, with `$HOME` shown as `~` |
| `%1~` | `\W` | Only the last folder |
| `%#` | `\$` | `#` for root, otherwise `%` (zsh) or `$` (bash) |
| `%F{red}…%f` | `\[\e[31m\]…\[\e[0m\]` | Coloured text |

Writing this by hand works fine for simple prompts. It gets painful once you want git status, icons, coloured "powerline" arrows, or a segment that only appears in some folders. A **prompt engine** takes care of all that for you.

## How Oh My Posh plugs into the shell

[Oh My Posh](https://ohmyposh.dev/) is a prompt engine: one binary plus a JSON **theme** file. It works with zsh, bash, fish, PowerShell and others, so the same theme looks the same on every machine.

You enable it with one line in `~/.zshrc`:

```bash
eval "$(oh-my-posh init zsh --config ~/.mytheme.omp.json)"
```

Here's what that line does:

1. `oh-my-posh init zsh …` **prints** a block of zsh code. It doesn't change anything by itself.
2. `eval "$( … )"` **runs** that printed code in your current shell.
3. The code registers a zsh hook (`precmd`) that runs before every prompt. The hook calls `oh-my-posh print primary`, which reads your theme, collects the data it needs (folder, git, exit code, …) and returns the finished string. The hook then puts that string into `PROMPT`.

So the theme is read again for each new prompt. To see your changes, edit `~/.mytheme.omp.json` and open a new tab (or run `exec zsh`).

> **Order matters in `.zshrc`:** the `oh-my-posh init` line sits *before* the zsh-autosuggestions and zsh-syntax-highlighting plugins, because syntax highlighting must be loaded last. Keep new things between the Kiro CLI pre/post blocks.

## Your setup

| | Mac | Raspberry Pi (`ungabunga`) |
|---|---|---|
| Shell | zsh | zsh |
| Oh My Posh binary | `/opt/homebrew/bin/oh-my-posh` (Homebrew) | `~/.local/bin/oh-my-posh` |
| Theme file | `~/.mytheme.omp.json` | `~/.mytheme.omp.json` (a copy of the Mac one) |
| Loaded from | `~/.zshrc` | `~/.zshrc` |
| Font | Needs a [Nerd Font](https://www.nerdfonts.com/) in the terminal app, or the icons show as boxes | Icons are drawn by the terminal on the *Mac*, so the Mac font is the one that matters over SSH |

### Anatomy of your theme

Your prompt has two lines:

```
 ┌ block 1 (left) ───────────────────────────────────────────────┐        ┌ block 2 (right) ┐
   session ▶  path  ▶   git      ▶  node     ▶ status                         time
     ▶  teratestn ▶ main ≡    ▶  v25.7.0  ▶  ✓                              23:09
 ❯                                          ← block 3 (new line, left)
```

A theme is a list of **blocks**, and each block is a list of **segments**:

| # | Block | Segment | What it shows |
|---|---|---|---|
| 1 | Left | `session` | Apple logo `` on the Mac, Raspberry Pi logo `` when you're in over SSH (`{{ if .SSHSession }}`) |
| | | `path` | The current folder only (`"style": "folder"`) |
| | | `git` | Branch, ahead/behind arrows, changed/staged counts, stash count. The background colour changes with repo state (see [`background_templates`](#colours)) |
| | | `node` | **New.** Node.js version, only inside Node projects |
| | | `status` | Teal with a check mark normally; pink with the exit code when the last command failed |
| 2 | Right | `time` | Clock in `15:04` format |
| 3 | Left, `newline: true` | `text` | The `❯` where you type. It turns pink after a failed command |

## What we changed: the Node.js segment

### Goal

Show the active Node version **only when the current folder is a Node project**, and keep it hidden everywhere else.

### The segment we added

It goes in block 1, right after the `git` segment:

```json
{
  "type": "node",
  "style": "powerline",
  "powerline_symbol": "",
  "background": "#6ca35e",
  "foreground": "#ffffff",
  "template": "  {{ .Full }} ",
  "options": {
    "display_mode": "files",
    "fetch_version": true
  }
}
```

| Key | Value | Why |
|---|---|---|
| `type` | `node` | Built-in segment that runs `node --version` |
| `style` | `powerline` | Same arrow style as the path and git segments next to it |
| `powerline_symbol` | `` | The `` arrow glyph from the Nerd Font |
| `background` | `#6ca35e` | Node.js green |
| `template` | `"  {{ .Full }} "` | Node logo `` + full version, e.g. `25.7.0` |
| `options.display_mode` | `files` | **The key setting.** Only render when the folder contains Node files |
| `options.fetch_version` | `true` | Ask for the version. Newer Oh My Posh releases fetch it automatically and ignore this key. |

With `display_mode: "files"`, the node segment looks in the current folder for any of these:

```
*.js  *.ts  package.json  .nvmrc  pnpm-workspace.yaml  .yarnrc.yml  .pnp.cjs  .pnp.js  .pnp.loader.mjs  node_modules
```

If none are found, the segment returns nothing and disappears completely, arrow included.

### Testing it

```bash
cd ~/Projects/teratestn
oh-my-posh debug --config ~/.mytheme.omp.json
```

`oh-my-posh debug` renders the whole prompt and lists every segment with `true`/`false` (was it shown?) and how long it took. That's the reliable way to test a theme from a script.

> **Gotcha:** `oh-my-posh print primary` run from a script did **not** show the node segment, even though it worked in a real terminal. Slow segments (anything that runs a command, like `node --version`) are filled in by the shell integration, so `print` on its own can skip them. Trust `debug` or a real new tab.

### Copying the theme to the Pi

The Pi's `.zshrc` loads the same filename, so copying the file over is enough:

```bash
# back up first, then copy
ssh yavor@ungabunga 'cp ~/.mytheme.omp.json ~/.mytheme.omp.json.bak'
scp ~/.mytheme.omp.json yavor@ungabunga:~/.mytheme.omp.json
```

Then reload the shell on the Pi with `exec zsh` (or log out and back in).

`scp` copies files over SSH, using the same `user@host` syntax as `ssh`. Paths after the `:` are on the remote machine.

The Pi doesn't have Node installed yet, so the segment stays hidden there until you install it.

### Lesson: `rm` has no undo

While cleaning up, the real theme on the Pi got deleted instead of the `.bak`. `rm` deletes straight away, with no Trash. We fixed it by copying the Mac version over again.

Habits that prevent this:

```bash
ls ~/.mytheme.omp.json*          # look first: what exactly matches?
rm -i ~/.mytheme.omp.json.bak    # -i asks "remove …?" before deleting
```

Type the full name (`….json.bak`) instead of relying on Tab completion. Tab stops at the shared prefix `.mytheme.omp.json`, so pressing Enter there deletes the real file.

---

## Reference: what you can tinker with

The theme is one JSON file with three levels: **top-level settings**, **blocks** and **segments**. The `$schema` line at the top gives you autocomplete and validation in VS Code. Hover any key to see what it does.

```json
{
  "$schema": "https://raw.githubusercontent.com/JanDeDobbeleer/oh-my-posh/main/themes/schema.json",
  "version": 4,
  "final_space": true,
  "blocks": [
    {
      "type": "prompt",
      "alignment": "left",
      "segments": [ { "type": "path", "style": "powerline", "...": "..." } ]
    }
  ]
}
```

### Top-level settings

| Key | Values | What it does |
|---|---|---|
| `version` | `4` | Schema version. Leave it at 4. |
| `final_space` | `true` / `false` | Add a space after the prompt so your cursor doesn't touch the `❯` |
| `console_title_template` | template string | The terminal tab/window title. Yours: `"{{ .Shell }} in {{ .Folder }}"` |
| `blocks` | array | The blocks, in order |
| `palette` | `{ "name": "#hex" }` | Named colours. Use them as `"p:name"` anywhere a colour is accepted |
| `transient_prompt` | object (`template`, `foreground`, `background`, …) | A short prompt (e.g. just `❯`) that *replaces* old prompts in your scrollback, so the history stays clean |
| `secondary_prompt` | object | The prompt shown when a command continues onto another line (after `\` or an open quote) |
| `async` | `true` / `false` | Show the prompt immediately and let slow segments appear when they're ready |
| `var` | `{ "Key": value }` | Your own constants, available in templates as `{{ .Var.Key }}` |
| `extends` | path or URL | Start from another theme and override only what you change |
| `enable_cursor_positioning` | `true` / `false` | Avoid a blank first line at the top of a fresh terminal |
| `shell_integration` | `true` / `false` | Mark command boundaries so terminals like iTerm2 can jump between commands |

### Block properties

| Key | Values | What it does |
|---|---|---|
| `type` | `prompt`, `rprompt` | Normal prompt, or zsh's right-side prompt (`RPROMPT`, which disappears when you type over it) |
| `alignment` | `left`, `right` | Which edge of the terminal the block sticks to. Your clock is a `right` block |
| `newline` | `true` / `false` | Start this block on a new line. This is how your `❯` sits on line 2 |
| `filler` | string, e.g. `"·"` or `"─"` | Character repeated across the gap between a left and a right block |
| `overflow` | `break`, `hide` | What happens when a block doesn't fit: move to a new line, or hide it |
| `leading_diamond` / `trailing_diamond` | glyph | Rounded cap at the very start or end of the block |
| `segments` | array | The segments, drawn left to right |

### Segment properties (shared by every segment type)

| Key | Values | What it does |
|---|---|---|
| `type` | one of ~120 types (see [below](#segment-types-worth-knowing)) | What the segment shows |
| `style` | `powerline`, `diamond`, `plain`, `accordion` | How it's drawn (see [Styles](#styles)) |
| `foreground` / `background` | a colour (see [Colours](#colours)) | Text and fill colour |
| `foreground_templates` / `background_templates` | array of templates | Conditional colours. The **first** template that produces a colour wins, otherwise the plain colour is used |
| `template` | Go template string | The text inside the segment (see [Templates](#templates)) |
| `templates` + `templates_logic` | array + `first_match` / `join` | Several templates: keep the first non-empty one, or join them all |
| `powerline_symbol` | glyph, usually `` `` | The arrow after a `powerline` segment |
| `leading_diamond` / `trailing_diamond` | glyph, e.g. `` `` / `` `` | The rounded caps of a `diamond` segment |
| `invert_powerline` | `true` / `false` | Flip the arrow direction (useful in right-aligned blocks) |
| `min_width` / `max_width` | integer (columns) | Hide the segment when the terminal is narrower / wider than this |
| `include_folders` / `exclude_folders` | array of paths, `~` allowed, regex allowed | Only show in, or never show in, these folders |
| `cache` | `{ "duration": "5m", "strategy": "folder" }` | Reuse the result for a while. `duration`: `none`, `infinite`, or e.g. `30s` / `5m` / `1h30m`. `strategy`: `folder`, `session`, `device` |
| `alias` | name | Lets other segments read this one's data: `{{ .Segments.Name.Field }}` |
| `options` | object | Settings specific to this segment type (called `properties` in older themes) |

### Styles

| Style | Look | Needs |
|---|---|---|
| `powerline` | `▶` arrows joining segments into one bar | `powerline_symbol` |
| `diamond` | Rounded or angled caps on each side | `leading_diamond`, `trailing_diamond` |
| `plain` | Just coloured text, no background shape | — |
| `accordion` | Like powerline, but leaves a thin arrow behind when the segment is empty | `powerline_symbol` |

Your theme mixes them. The bar opens with a rounded `diamond` (session), continues as `powerline` (path, git, node), and ends with a rounded `diamond` (status). The `❯` is `plain`.

### Colours

Anywhere a colour is accepted, you can use:

| Form | Example | Notes |
|---|---|---|
| Hex | `#ff479c`, `#fff` | Most common |
| ANSI name | `red`, `lightBlue`, `darkGray`, `white` | Follows your terminal's colour scheme |
| ANSI 256 index | `"208"` | 0–255 |
| Keywords | `transparent`, `parentBackground`, `parentForeground`, `background`, `foreground`, `accent` | `transparent` = no fill. `parentBackground` = the previous segment's background |
| Palette | `p:pink` | Needs `"palette": { "pink": "#ff479c" }` at the top level |
| Shade | `darken(#ff479c, 20)`, `lighten(p:pink, 10)` | Darker or lighter by a percentage |
| Gradient | `linear-gradient(#c386f1, #ff479c)` | Blends across the segment |

Conditional colours, as used in your git segment:

```json
"background": "#fffb38",
"background_templates": [
  "{{ if or (.Working.Changed) (.Staging.Changed) }}#FF9248{{ end }}",
  "{{ if and (gt .Ahead 0) (gt .Behind 0) }}#ff4500{{ end }}",
  "{{ if gt .Ahead 0 }}#B388FF{{ end }}"
]
```

Yellow = clean, orange = uncommitted changes, red-orange = diverged from the remote, purple = ahead or behind.

### Templates

Templates use [Go's `text/template`](https://pkg.go.dev/text/template) syntax. `{{ … }}` inserts a value or runs logic.

```
{{ .Full }}                                   insert a field
{{ if .SSHSession }}A{{ else }}B{{ end }}     if / else
{{ if gt .Code 0 }}{{ .Code }}{{ end }}       comparisons: eq ne lt le gt ge
{{ if and .Working.Changed .Staging.Changed }} and / or / not
{{ trunc 25 .Branch }}                        functions (Sprig library): trunc, upper, lower, replace, …
{{ .Env.HOME }}                               any environment variable
```

**Available everywhere:** `.Shell`, `.Folder`, `.PWD`, `.UserName`, `.HostName`, `.OS`, `.Root` (true if root), `.Code` (last exit code), `.Env.NAME`, `.Var.NAME`.

**Per segment** (the fields your theme uses, plus useful extras):

| Segment | Fields |
|---|---|
| `session` | `.UserName`, `.HostName`, `.SSHSession` |
| `path` | `.Path`, `.Parent`, `.Folder`, `.Writable` |
| `git` | `.HEAD`, `.Branch`, `.BranchStatus`, `.Ahead`, `.Behind`, `.Working.Changed`, `.Working.String`, `.Staging.Changed`, `.Staging.String`, `.StashCount`, `.UpstreamIcon`, `.RepoName` |
| `node` | `.Full` (`25.7.0`), `.Major`, `.Minor`, `.Patch`, `.PackageManagerIcon`, `.PackageManagerName`, `.Expected` / `.Mismatch` (compared with `.nvmrc`) |
| `status` | `.Code`, `.Error` |
| `time` | `.CurrentDate` (used as `{{ .CurrentDate \| date .Format }}`) |

**Icons** are Nerd Font code points written as `\uXXXX`. Search for icons at the [Nerd Fonts cheat sheet](https://www.nerdfonts.com/cheat-sheet) and copy the hex code.

### Options for the segments you use

**`node`** (and every language segment: python, go, rust, java, …)

| Option | Values | Default | Effect |
|---|---|---|---|
| `display_mode` | `always`, `files`, `environment`, `context` | `context` | `files` = only when matching files are present. `always` = everywhere. `environment` = only in an active virtual environment (Python). `context` = files *or* environment |
| `home_enabled` | `true` / `false` | `false` | Also show it in `~` |
| `extensions` | array of globs | see above | Which files count as "a Node project" |
| `fetch_package_manager` | `true` / `false` | `false` | Fill `.PackageManagerIcon` with the npm/yarn/pnpm/bun icon, based on the lockfile |
| `npm_icon`, `yarn_icon`, `pnpm_icon`, `bun_icon` | glyph | Nerd Font logos | Override those icons |
| `missing_command_text` | string | `""` | Text shown when `node` isn't installed |
| `cache_duration` | `none`, `5m`, `1h`, … | — | How long to remember the version |

**`path`**

| Option | Values | Effect |
|---|---|---|
| `style` | `folder`, `full`, `short`, `agnoster`, `agnoster_full`, `agnoster_short`, `agnoster_left`, `letter`, `unique`, `mixed`, `fish`, `powerlevel` | How much of the path to show. **Yours:** `folder` (just `teratestn`). `full` = `~/Projects/teratestn`. `fish` = `~/P/teratestn`. `letter` = `~/P/t` |
| `home_icon` | string | What to show for `$HOME`. Yours: `~` |
| `folder_separator_icon` | string | Separator between folders. Yours: `` |
| `max_depth` | integer | Folder count before `agnoster_short` starts shortening |
| `mapped_locations` | `{ "~/Projects": "" }` | Replace known paths with an icon or nickname |

**`git`**

| Option | Values | Effect |
|---|---|---|
| `branch_template` | template | How the branch name is shown. Yours: `{{ trunc 25 .Branch }}` cuts long names to 25 characters |
| `branch_icon` | glyph | Icon before the branch (default ``) |
| `branch_identical_icon`, `branch_ahead_icon`, `branch_behind_icon`, `branch_gone_icon` | glyph | `≡`, `↑`, `↓`, `≢` by default |
| `mapped_branches` | `{ "feature/*": "🚀 " }` | Replace branch prefixes with something shorter |
| `status_formats` | `{ "Added": "+%d" }` | How each kind of change is counted in `.Working.String` |
| `ignore_status` | array of paths | Skip the (slow) status check in huge repos |

**`status`**

| Option | Values | Effect |
|---|---|---|
| `always_enabled` | `true` / `false` | Show the segment on success too. Yours: `true`, so it's always there and changes colour |
| `status_template` | template | How the code is formatted |

**`time`**

| Option | Values | Effect |
|---|---|---|
| `time_format` | Go time layout | Go formats time by example, based on the reference date **Mon Jan 2 15:04:05 MST 2006**. Yours is `15:04` → `23:09`. Other examples: `15:04:05`, `3:04 PM`, `Mon 02 Jan` |

### Segment types worth knowing

There are about 120. These are the ones you're most likely to want:

| Category | Types |
|---|---|
| Languages / runtimes | `node`, `bun`, `deno`, `python`, `go`, `rust`, `java`, `dotnet`, `php`, `ruby`, `swift`, `lua` |
| Package managers / tools | `npm`, `pnpm`, `yarn`, `docker`, `kubectl`, `terraform`, `aws`, `az`, `gcp` |
| Shell & system | `executiontime` (how long the last command took), `os`, `shell`, `root`, `battery`, `sysinfo` (CPU/RAM), `upgrade` |
| Version control | `git`, `jujutsu`, `mercurial`, `svn` |
| Misc | `project` (name and version from `package.json`), `spotify`, `text`, `claude` |

Full list with options: [ohmyposh.dev/docs/segments](https://ohmyposh.dev/docs/segments).

## Recipes

Copy these into `segments` arrays to try them.

**Show how long the last command took** (only if it took more than 2 s):

```json
{
  "type": "executiontime",
  "style": "powerline",
  "powerline_symbol": "",
  "background": "#ffd166",
  "foreground": "#193549",
  "template": "  {{ .FormattedMs }} ",
  "options": { "threshold": 2000, "style": "austin" }
}
```

**Add the package manager icon to the node segment:**

```json
"template": "  {{ .Full }} {{ .PackageManagerIcon }} ",
"options": { "display_mode": "files", "fetch_package_manager": true }
```

**Warn when the Node version doesn't match `.nvmrc`:**

```json
"background_templates": ["{{ if .Mismatch }}#e91e63{{ end }}"]
```

**Collapse old prompts in scrollback to just `❯`:**

```json
"transient_prompt": {
  "foreground": "#00897b",
  "foreground_templates": ["{{ if gt .Code 0 }}#e91e63{{ end }}"],
  "template": "❯ "
}
```

**Name your colours once** (then change the whole theme from one place):

```json
"palette": { "teal": "#00897b", "pink": "#e91e63" },
"...": "...",
"background": "p:teal"
```

## Workflow & troubleshooting

| Want to… | Do |
|---|---|
| Try a change | Edit `~/.mytheme.omp.json`, then open a new tab or run `exec zsh` |
| See why a segment is missing | `oh-my-posh debug --config ~/.mytheme.omp.json`. Each segment is listed as `true`/`false` with timings, and errors are printed |
| Catch JSON mistakes | Open the file in VS Code. The `$schema` line underlines invalid keys and values |
| Browse ready-made themes | `ls $(brew --prefix oh-my-posh)/themes`, or the gallery at [ohmyposh.dev/docs/themes](https://ohmyposh.dev/docs/themes) |
| Sync to the Pi | `scp ~/.mytheme.omp.json yavor@ungabunga:~/.mytheme.omp.json`, then `exec zsh` on the Pi |
| Undo | Keep a copy before big edits: `cp ~/.mytheme.omp.json ~/.mytheme.omp.json.bak` |

| Symptom | Cause |
|---|---|
| Boxes or `?` instead of icons | Terminal font isn't a Nerd Font. Change it in the terminal app's settings (VS Code: `terminal.integrated.fontFamily`) |
| Segment never appears | Check `display_mode`, `include_folders`/`exclude_folders`, and whether the tool (e.g. `node`) is installed and on `$PATH` |
| Prompt is slow | Run `debug` to find the slow segment, then add a `cache` or turn on `async` |
| Prompt disappeared completely | Usually a JSON syntax error (a trailing comma, a missing quote). `debug` reports it |

## Resources

- [Oh My Posh docs](https://ohmyposh.dev/docs) · [configuration](https://ohmyposh.dev/docs/configuration/general) · [segments](https://ohmyposh.dev/docs/segments) · [templates](https://ohmyposh.dev/docs/configuration/templates)
- [Nerd Fonts cheat sheet](https://www.nerdfonts.com/cheat-sheet)
- [Go time format reference](https://pkg.go.dev/time#pkg-constants)
- [Sprig template functions](https://masterminds.github.io/sprig/)
