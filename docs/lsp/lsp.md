# LSP — Language Server Protocol

The **Language Server Protocol (LSP)** is a standard way for an **editor** and a **language tool** to talk to each other. It's what gives you autocomplete, inline error squiggles, go-to-definition, hover documentation, rename-symbol, and formatting — the features often marketed as "IntelliSense".

The key idea: the editor knows nothing about the language, and the language tool knows nothing about the editor. They only agree on a **protocol**.

## The problem it solved

Before LSP, every language-tooling feature was built per editor. If you had **M** languages and **N** editors, you needed **M × N** separate integrations:

```text
              VS Code   Vim   Emacs   Sublime   Visual Studio
TypeScript      ✔        ✔      ✔        ✔           ✔
Python          ✔        ✔      ✔        ✔           ✔
Rust            ✔        ✔      ✔        ✔           ✔
C#              ✔        ✔      ✔        ✔           ✔
```

Each ✔ was a plugin someone had to write and maintain, in that editor's own extension language, duplicating all the hard parts (parsing, type inference, symbol resolution).

With LSP it becomes **M + N**: each language writes **one** server, each editor writes **one** client.

```text
TypeScript server ┐                    ┌ VS Code
Python server     ├─ LSP (JSON-RPC) ───┤ Neovim
Rust server       │                    │ Emacs
C# server         ┘                    └ Zed
```

> **Key idea:** LSP turned an M × N problem into an M + N problem. That's the whole reason it exists.

LSP was created by **Microsoft** (out of the work on VS Code, around 2016) and then developed openly with Red Hat and Codenvy. It is now an [open specification](https://microsoft.github.io/language-server-protocol/) that any editor or language can implement.

## How it actually works

There are two sides:

- **Client** — the editor (VS Code, Neovim, Emacs, Zed…). It knows about buffers, cursors, and UI.
- **Server** — a separate process for a language (`tsserver`, `pyright`, `rust-analyzer`, `clangd`…). It parses your code and understands its meaning.

They exchange **JSON-RPC 2.0** messages, usually over stdin/stdout of the server process (sometimes over a socket or pipe).

```text
Editor (client)                          Language server (process)
   │  initialize ─────────────────────────────▶
   │  ◀───────────────────────── capabilities  │
   │  textDocument/didOpen ───────────────────▶ (parses the file)
   │  ◀──────── textDocument/publishDiagnostics (the red squiggles)
   │  textDocument/completion ────────────────▶
   │  ◀────────────────────── list of items    │
```

The lifecycle in words:

1. You open a `.ts` file. The editor starts the TypeScript language server as a child process.
2. **`initialize`** — the client and server exchange *capabilities*: "I can show hovers", "I can provide rename". Anything unsupported is simply not used.
3. **`textDocument/didOpen` / `didChange`** — the editor streams the file's contents and every edit to the server, so the server always has the current text (it does **not** read your unsaved file from disk).
4. The server pushes **`textDocument/publishDiagnostics`** whenever it finds problems — this is a *notification*, sent unprompted, which is why errors appear as you type.
5. When you press the completion key, the editor sends **`textDocument/completion`** and waits for a reply — a *request*.
6. **`shutdown`** / **`exit`** when you close the project.

### Requests vs notifications

| Kind | Expects a reply? | Examples |
| --- | --- | --- |
| **Request** | Yes | `initialize`, `textDocument/completion`, `textDocument/definition`, `textDocument/hover`, `textDocument/rename` |
| **Notification** | No | `textDocument/didOpen`, `didChange`, `didSave`, `publishDiagnostics` |

## The features you know, by their protocol name

| What you see in the editor | LSP method |
| --- | --- |
| Autocomplete / IntelliSense | `textDocument/completion` |
| Red/yellow squiggles | `textDocument/publishDiagnostics` |
| Tooltip on hover | `textDocument/hover` |
| Go to definition (F12) | `textDocument/definition` |
| Find all references | `textDocument/references` |
| Parameter hints while typing a call | `textDocument/signatureHelp` |
| Rename symbol (F2) | `textDocument/rename` |
| Format document | `textDocument/formatting` |
| Quick fixes / lightbulb | `textDocument/codeAction` |
| Outline / breadcrumbs | `textDocument/documentSymbol` |
| Search symbol across project | `workspace/symbol` |
| Inline type/parameter labels | `textDocument/inlayHint` |
| Rich syntax colouring | `textDocument/semanticTokens` |

## Common language servers

| Language | Server |
| --- | --- |
| TypeScript / JavaScript | `typescript-language-server` (wraps `tsserver`) |
| Python | Pyright / Pylance, `python-lsp-server`, Ruff |
| Rust | `rust-analyzer` |
| C / C++ | `clangd` |
| C# | Roslyn language server / OmniSharp |
| Go | `gopls` |
| HTML / CSS / JSON | `vscode-langservers-extracted` |
| Lua | `lua-language-server` |

A full list lives at [langserver.org](https://langserver.org/).

## Things worth knowing

- **The server is a separate process.** If IntelliSense goes stale or dies, restarting the language server (VS Code: *TypeScript: Restart TS Server*) usually fixes it without restarting the editor. High CPU from "the editor" is often really the language server re-analysing the project.
- **Positions are line/character, zero-based**, and character offsets are counted in **UTF-16 code units** by default — a quirk inherited from VS Code that trips up implementers with emoji and non-BMP characters.
- **Capability negotiation means graceful degradation.** A server that doesn't implement rename simply doesn't advertise it, and the editor hides the option instead of erroring.
- **LSP is not a compiler or a linter.** It's a *transport*. The intelligence lives in the server, which usually reuses the language's real compiler front-end (that's why `rust-analyzer` and `tsserver` are so accurate).
- **Syntax highlighting is mostly not LSP.** Basic colouring comes from the editor's own grammars (TextMate grammars, Tree-sitter); LSP only adds the semantic layer on top via `semanticTokens`.
- **Sibling protocols.** The same idea was copied for other tooling: **DAP** (Debug Adapter Protocol) for debuggers, **BSP** (Build Server Protocol) for builds, and — same spirit, different domain — **MCP** (Model Context Protocol) for connecting AI models to tools.

## Further reading

- [Official LSP specification](https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/)
- [Why LSP? (Microsoft's own write-up)](https://microsoft.github.io/language-server-protocol/overviews/lsp/overview/)
- [langserver.org — implementations by language and editor](https://langserver.org/)
