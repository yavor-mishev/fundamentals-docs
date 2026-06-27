# Markdown Cheatsheet

A quick reference for commonly used Markdown syntax in documentation.

## Headings

# Heading 1

## Heading 2

### Heading 3

## Bold & Italic

**Bold text**
_Italic text_
**_Bold and italic_**

## Lists

**Checklist with description:**

- [x] Install Node.js (done)
- [ ] Configure VS Code (pending)
- Item 2
  - Subitem

**Inline code in a sentence:**
To run the app, use `npm start` in your terminal.
**Numbered list:**

1. First item
2. Second item

**Task list:**

- [x] Task 1

**Shell command block:**

```bash
git status
git pull origin main
```

- [ ] Task 2

## Code Blocks

[Internal link to another section](#headings)
**Inline code:**
Inline code: `your code here`

**Multiline code block:**

![Kendo UI Logo](https://docs.telerik.com/kendo-ui/images/kendo-ui-logo.svg)

```
function hello() {
  console.log('Hello!');
}
```

**Language-specific code block:**

**Table with alignment:**
| Left Align | Center Align | Right Align |
|:-----------|:------------:|------------:|
| left | center | right |
| more left | more center | more right |

```js
const x = 5;
console.log(x);
```

## Links

[Link text](https://example.com)

## Images

> **Note:** Blockquotes can be nested.
>
> > Nested blockquote example.

![Alt text](https://via.placeholder.com/150)

## Tables

**Info:**

> ℹ️ **Info:** This is an informational message.
> | Column 1 | Column 2 |
> |----------|----------|
> | Row 1 | Data |
> | Row 2 | More |

**Collapsible Section (details):**

<details>
  <summary>Click to expand for more info</summary>
  This is hidden content that can be revealed.
</details>
**Advanced Table:**
| Name    | Role      | Status   |
|---------|-----------|----------|
| Alice   | Developer | Active   |
| Bob     | QA        | Inactive |

## Blockquotes

> This is an important message or tip.

## Horizontal Rule

```markdown

```

---

## Important Messages

**Tip:**

> **Tip:** You can use blockquotes for tips and important notes.

**Warning:**

> **Warning:** Be careful with this action!

**Note:**

> **Note:** This is a general note.

## Miscellaneous

**Strikethrough:**
~~This text is crossed out.~~

**Emoji (if supported):**
:smile: :rocket: :warning:

**Footnote:**
Here is a footnote reference.[^1]

[^1]: This is the footnote content.

**HTML in Markdown:**
<span style="color: red; font-weight: bold;">This is red bold text using HTML.</span>

**Task list with links:**

- [x] [Install Node.js](https://nodejs.org/)
- [ ] [Read Kendo Docs](https://docs.telerik.com/kendo-ui)

**Math formulas (if supported):**
$$E = mc^2$$

**Code block with line highlighting (if supported):**

```js {1,3}
const a = 1;
const b = 2;
console.log(a + b);
```

**Blockquote with custom styling (HTML):**

<blockquote style="background: #f9f9f9; border-left: 5px solid #2196F3; padding: 10px;">
  <strong>Info:</strong> This is a custom styled blockquote.
</blockquote>

**Custom badge (HTML):**
<span style="background: #2196F3; color: white; padding: 2px 8px; border-radius: 4px; font-size: 0.9em;">NEW</span>

**Footnote**

This is a simple footnote,[^1] demonstrating how to add additional information.