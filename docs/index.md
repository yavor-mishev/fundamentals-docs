# Technology & Concepts Mind Map

> **Purpose**: A living document to visualize how all fundamental technologies and concepts connect. Use this to maintain mental clarity and trace relationships when deep in complex work.

**Last Updated**: December 20, 2025

---

## 🗺️ The Complete Map

```
┌─────────────────────────────────────────────────────────────────────────┐
│                    LAYER 1: COMPUTER SCIENCE FUNDAMENTALS               │
│                         (Universal, Never Changes)                      │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│   ┌──────────────┐      ┌─────────────┐      ┌──────────────────┐    │
│   │  Algorithms  │      │    Data     │      │  Async/Sync      │    │
│   │  (Sorting,   │      │  Structures │      │  Event Loop      │    │
│   │  Searching)  │      │  (Array/Obj)│      │  Concurrency     │    │
│   └──────┬───────┘      └──────┬──────┘      └────────┬─────────┘    │
│          │                     │                       │               │
│          └─────────────────────┴───────────────────────┘               │
│                                 │                                      │
│                   These apply to ALL programming                       │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
                                  │
                                  ↓
┌─────────────────────────────────────────────────────────────────────────┐
│                    LAYER 2: LANGUAGES & RUNTIMES                        │
│                    (What executes your code)                            │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌─────────────────────────────────┐  ┌────────────────────────────┐  │
│  │      JAVASCRIPT ECOSYSTEM       │  │      .NET ECOSYSTEM        │  │
│  │                                 │  │                            │  │
│  │  JavaScript (Language)          │  │  C# (Language)             │  │
│  │       │                         │  │       │                    │  │
│  │       ├─► Browser Runtime       │  │       ├─► .NET Framework   │  │
│  │       │    • window object      │  │       │    (Legacy)        │  │
│  │       │    • DOM                │  │       │    • Windows only  │  │
│  │       │    • Web APIs           │  │       │                    │  │
│  │       │                         │  │       └─► .NET Core/.NET   │  │
│  │       └─► Node.js Runtime       │  │            (Modern)        │  │
│  │            • global object      │  │            • Cross-platform│  │
│  │            • fs module          │  │            • CoreCLR       │  │
│  │            • http module        │  │                            │  │
│  │            • Built on V8        │  │  Both compile to:          │  │
│  │                                 │  │  IL → Native (via CLR/JIT) │  │
│  │  Executes via:                  │  │                            │  │
│  │  • V8 Engine (Chrome)           │  │                            │  │
│  │  • SpiderMonkey (Firefox)       │  │                            │  │
│  │                                 │  │                            │  │
│  └─────────────────────────────────┘  └────────────────────────────┘  │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
                                  │
                                  ↓
┌─────────────────────────────────────────────────────────────────────────┐
│                    LAYER 3: WEB FUNDAMENTALS                            │
│                    (How the web works)                                  │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌──────────────────────────────────────────────────────────────────┐  │
│  │  HTML (Structure)                                                │  │
│  │    └─► data-* attributes (custom data storage)                   │  │
│  │    └─► DOM (Document Object Model)                               │  │
│  │                                                                   │  │
│  │  CSS/LESS/SASS (Styling)                                         │  │
│  │    └─► Rendered by: WebKit, Blink (layout engines)              │  │
│  │                                                                   │  │
│  │  HTTP/HTTPS Protocol                                             │  │
│  │    └─► Web Servers (listen on ports, serve content)             │  │
│  │         • Port 80 (HTTP)                                         │  │
│  │         • Port 443 (HTTPS)                                       │  │
│  │         • Request → Response cycle                               │  │
│  └──────────────────────────────────────────────────────────────────┘  │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
                                  │
                                  ↓
┌─────────────────────────────────────────────────────────────────────────┐
│                    LAYER 4: ARCHITECTURAL PATTERNS                      │
│                    (Design Concepts - Language Agnostic)                │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌─────────────────────────────┐    ┌─────────────────────────────┐   │
│  │  MVC Pattern                │    │  MVVM Pattern               │   │
│  │  (Request/Response)         │    │  (Reactive/Data-Binding)    │   │
│  │                             │    │                             │   │
│  │  Model ─────────┐           │    │  Model ──────────┐          │   │
│  │  (Data/Logic)   │           │    │  (Raw Data)      │          │   │
│  │                 ↓           │    │                  ↓          │   │
│  │  Controller ────┤           │    │  ViewModel ──────┤          │   │
│  │  (Handles HTTP) │           │    │  (Observable)    │          │   │
│  │                 ↓           │    │  (Auto-sync)     ↓          │   │
│  │  View ──────────┘           │    │  View ───────────┘          │   │
│  │  (UI/HTML)                  │    │  (UI/HTML)                  │   │
│  │                             │    │                             │   │
│  │  Used in:                   │    │  Used in:                   │   │
│  │  • ASP.NET MVC              │    │  • Kendo UI MVVM            │   │
│  │  • Express.js               │    │  • Blazor                   │   │
│  │  • Ruby on Rails            │    │  • WPF                      │   │
│  └─────────────────────────────┘    └─────────────────────────────┘   │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
                                  │
                                  ↓
┌─────────────────────────────────────────────────────────────────────────┐
│                    LAYER 5: FRAMEWORKS & LIBRARIES                      │
│                    (What you build applications with)                   │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌─────────────────────────────┐    ┌─────────────────────────────┐   │
│  │  BACKEND FRAMEWORKS         │    │  FRONTEND LIBRARIES         │   │
│  │                             │    │                             │   │
│  │  ASP.NET MVC/Core           │    │  jQuery                     │   │
│  │    • Language: C#           │    │    • DOM manipulation       │   │
│  │    • Runtime: .NET          │    │    • Event handling         │   │
│  │    • Pattern: MVC           │    │    • AJAX                   │   │
│  │    • Blazor (MVVM variant)  │    │    • Animations             │   │
│  │                             │    │                             │   │
│  │  Express.js                 │    │  Kendo UI                   │   │
│  │    • Language: JavaScript   │    │    • Built on jQuery        │   │
│  │    • Runtime: Node.js       │    │    • MVVM support           │   │
│  │    • Pattern: MVC-like      │    │    • Rich widgets           │   │
│  │    • RESTful APIs           │    │    • Data binding           │   │
│  │                             │    │    • Observable objects     │   │
│  └─────────────────────────────┘    └─────────────────────────────┘   │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
                                  │
                                  ↓
┌─────────────────────────────────────────────────────────────────────────┐
│                    LAYER 6: TOOLS & INFRASTRUCTURE                      │
│                    (Supporting technologies)                            │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌──────────────┐  ┌───────────┐  ┌──────────┐  ┌─────────────────┐  │
│  │    Docker    │  │    Git    │  │   NPM    │  │  Testing        │  │
│  │              │  │           │  │          │  │                 │  │
│  │  • Images    │  │  • Repos  │  │  • JS    │  │  • Jest         │  │
│  │  • Containers│  │  • Commits│  │    Packages│  │  • Selenium   │  │
│  │  • Isolation │  │  • Branches│ │  • Scripts│  │  • Unit Tests  │  │
│  └──────────────┘  └───────────┘  └──────────┘  └─────────────────┘  │
│                                                                         │
│  All work with any language/framework above                            │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 🔗 Critical Connection Points

### Connection 1: Language → Runtime
- **JavaScript** needs a **runtime** (Browser or Node.js) to execute
- **C#** needs a **runtime** (.NET Framework or .NET Core) to execute
- You can't run JavaScript or C# directly on hardware

### Connection 2: Runtime → Engine
- **Node.js** uses **V8 engine** to execute JavaScript
- **.NET** uses **CLR** to compile IL code to native code
- Engines/runtimes handle memory, garbage collection, execution

### Connection 3: Pattern → Framework
- **MVC pattern** is implemented by **ASP.NET MVC** and **Express**
- **MVVM pattern** is implemented by **Kendo UI** and **Blazor**
- Patterns are concepts; frameworks are implementations

### Connection 4: Framework → Language → Runtime
```
ASP.NET MVC  →  uses C#  →  runs on .NET Runtime
Express      →  uses JS   →  runs on Node.js Runtime
Kendo UI     →  uses JS   →  runs in Browser Runtime
```

### Connection 5: Web Stack
```
User Types URL
      ↓
Web Server (listens on port)
      ↓
HTTP Request sent
      ↓
Backend Framework (ASP.NET/Express)
      ↓
Controller handles request (MVC)
      ↓
Model fetches/processes data
      ↓
View renders HTML
      ↓
HTTP Response sent back
      ↓
Browser renders (HTML + CSS + JS)
      ↓
Frontend Framework (Kendo UI) adds interactivity (MVVM)
```

---

## 🧠 Mental Model Questions

Use these to test your understanding:

### "Where Am I?" Framework
When working on something, ask:

1. **What layer am I in?**
   - Fundamentals? Language? Pattern? Framework? Tool?

2. **What depends on what?**
   - Does Express depend on JavaScript? ✅ Yes
   - Does JavaScript depend on Express? ❌ No
   - Does MVC depend on C#? ❌ No (it's just a pattern)
   - Does ASP.NET MVC depend on C#? ✅ Yes

3. **Can I replace this?**
   - Can I replace Node.js with Deno? ✅ Yes (both JS runtimes)
   - Can I replace JavaScript with C# in Node.js? ❌ No
   - Can I use MVC with JavaScript? ✅ Yes (Express does this)

### Common Confusions - RESOLVED

| ❌ Confusion | ✅ Clarity |
|------------|-----------|
| "Is Node.js a language?" | No. JavaScript is the language. Node.js is a runtime. |
| "Is .NET a language?" | No. C# is the language. .NET is a framework/runtime. |
| "Is MVC only for .NET?" | No. MVC is a pattern used by many frameworks. |
| "Can I use jQuery without HTML?" | No. jQuery manipulates the DOM (HTML). |
| "Is Docker like a VM?" | Similar but lighter. Containers vs. Virtual Machines. |
| "Do I need .NET Framework for .NET Core?" | No. They're separate. .NET Core is the modern version. |

---

## 📊 Dependency Tree

### To Build an ASP.NET MVC App:
```
Your App
  └─ ASP.NET MVC Framework
       └─ C# Language
            └─ .NET Runtime
                 └─ Operating System (Windows/Linux/Mac)
```

### To Build an Express App:
```
Your App
  └─ Express Framework
       └─ JavaScript Language
            └─ Node.js Runtime
                 └─ V8 Engine
                      └─ Operating System
```

### To Use Kendo UI Widgets:
```
Your Web Page
  └─ Kendo UI Library
       └─ jQuery Library
            └─ JavaScript Language
                 └─ Browser Runtime
                      └─ Rendering Engine (Blink/WebKit)
```

---

## 🎯 Quick Reference Cheat Sheet

### "I Forgot the Basics" - Reset Points

| Topic | One-Liner | File to Review |
|-------|-----------|----------------|
| **Algorithms** | Step-by-step instructions to solve problems | [algorithms.md](algorithms/algorithms.md) |
| **Event Loop** | How JS handles async without blocking | [event-loop.md](javascript/event-loop.md) |
| **HTTP** | Request/response protocol, ports 80/443 | [web-server.md](web-servers/web-server.md) |
| **MVC** | Model-View-Controller separation pattern | [mvc.md](asp-net-mvc/mvc.md) |
| **MVVM** | Observable data binding between VM and View | [mvvm.md](mvvm/mvvm.md) |
| **DOM** | HTML structure that JS can manipulate | [html.md](html/html.md) |
| **CLR** | .NET's runtime that compiles IL to native | [c-sharp.md](cs/c-sharp.md) |
| **V8** | Engine that executes JavaScript | [v8.md](web-engines/js-engines/v8.md) |

### "What's the Difference?" - Common Pairs

| vs | Key Difference |
|----|----------------|
| **JavaScript vs Node.js** | Language vs Runtime |
| **C# vs .NET** | Language vs Framework |
| **.NET Framework vs .NET Core** | Legacy/Windows vs Modern/Cross-platform |
| **MVC vs MVVM** | Request/Response vs Reactive/Binding |
| **jQuery vs Kendo UI** | Low-level DOM vs High-level Widgets |
| **Browser vs Node.js** | Frontend runtime vs Backend runtime |
| **Docker vs VM** | Containers (light) vs Virtual Machines (heavy) |
| **NPM vs Packages** | Package manager vs Packages themselves |
| **Git vs GitHub** | Version control tool vs Hosting service |

---

## 🔄 Skill Retention Strategy

### Daily Work → Foundation Mapping

When you work on complex features, trace back to fundamentals:

**Example 1**: "Debugging Kendo MVVM data binding issue"
```
Kendo MVVM
  ↓ uses
Observable pattern
  ↓ which is
Property change detection
  ↓ which relies on
JavaScript objects (fundamental data structure)
  ↓ executed by
Browser's JavaScript engine
```

**Example 2**: "Building ASP.NET Core API endpoint"
```
ASP.NET Core API
  ↓ uses
MVC pattern (Controller)
  ↓ handles
HTTP requests
  ↓ which uses
Web server listening on ports
  ↓ written in
C# language
  ↓ compiled by
.NET runtime (CLR)
```

### Weekly Refresh Checklist

- [ ] Read one "Layer 1" file (algorithms, data structures, event loop)
- [ ] Trace one complex work task back to fundamentals
- [ ] Update this MIND-MAP.md with new connections discovered
- [ ] Review "Common Confusions" section - test yourself

---

## 📝 Notes Section

Use this space to add your own insights, connections, or "aha!" moments:

### My Key Insights
- [Add your discoveries here]
- 
- 

### Patterns I've Noticed
- [Add recurring patterns you see]
- 
- 

### Still Confusing
- [Add things you're still working on understanding]
- 
- 

---

**Remember**: Complexity is just layers of simplicity stacked together. When lost, trace down to a layer you're comfortable with, then work back up.
