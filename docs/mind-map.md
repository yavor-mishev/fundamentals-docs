# Technology & Concepts Mind Map

> **Purpose**: A living document to visualize how all fundamental technologies and concepts connect. Use this to maintain mental clarity and trace relationships when deep in complex work.

## 🗺️ The Complete Map

Six layers, from the most universal at the top to the most specific at the bottom. Each layer builds on the one above it.

```mermaid
flowchart TB
    subgraph L1["1 · Computer Science Fundamentals — universal, never changes"]
        direction LR
        ALG["Algorithms<br/>sorting · searching"]
        DS["Data Structures<br/>arrays · objects"]
        ASY["Async / Sync<br/>event loop · concurrency"]
    end

    subgraph L2["2 · Languages & Runtimes — what executes your code"]
        direction LR
        subgraph JSE["JavaScript ecosystem"]
            JS["JavaScript"] --> BRT["Browser runtime<br/>window · DOM · Web APIs"]
            JS --> NODE["Node.js runtime<br/>global · fs · http"]
            JS -. executed by .-> ENG["V8 (Chrome, Node.js)<br/>SpiderMonkey (Firefox)"]
        end
        subgraph NETE[".NET ecosystem"]
            CS["C#"] --> NETFX[".NET Framework<br/>legacy · Windows only"]
            CS --> NETC[".NET Core / .NET<br/>modern · cross-platform · CoreCLR"]
            NETFX & NETC -. compile .-> IL["IL → native<br/>via CLR / JIT"]
        end
    end

    subgraph L3["3 · Web Fundamentals — how the web works"]
        direction LR
        HTML["HTML<br/>structure · data-* · DOM"]
        CSS["CSS / LESS / SASS<br/>rendered by WebKit, Blink"]
        HTTP["HTTP / HTTPS<br/>web servers · ports 80/443<br/>request → response"]
    end

    subgraph L4["4 · Architectural Patterns — language agnostic"]
        direction LR
        MVC["MVC<br/>request/response<br/>Model → Controller → View<br/><i>ASP.NET MVC · Express · Rails</i>"]
        MVVM["MVVM<br/>reactive data binding<br/>Model → ViewModel ⇄ View<br/><i>Kendo UI · Blazor · WPF</i>"]
    end

    subgraph L5["5 · Frameworks & Libraries — what you build with"]
        direction LR
        ASP["ASP.NET MVC / Core<br/>C# · .NET · MVC<br/>Blazor (MVVM variant)"]
        EXP["Express.js<br/>JavaScript · Node.js<br/>MVC-like · REST APIs"]
        JQ["jQuery<br/>DOM · events · AJAX"]
        KENDO["Kendo UI<br/>built on jQuery<br/>MVVM · widgets · binding"]
    end

    subgraph L6["6 · Tools & Infrastructure — work with everything above"]
        direction LR
        DOCKER["Docker<br/>images · containers"]
        GIT["Git<br/>repos · commits · branches"]
        NPM["npm<br/>packages · scripts"]
        TEST["Testing<br/>Jest · Selenium"]
    end

    L1 --> L2 --> L3 --> L4 --> L5 --> L6
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

```mermaid
flowchart TD
    A[User types URL] --> B[Web server listening on a port]
    B --> C[HTTP request sent]
    C --> D["Backend framework<br/>ASP.NET / Express"]
    D --> E["Controller handles request (MVC)"]
    E --> F[Model fetches / processes data]
    F --> G[View renders HTML]
    G --> H[HTTP response sent back]
    H --> I["Browser renders HTML + CSS + JS"]
    I --> J["Frontend framework (Kendo UI)<br/>adds interactivity (MVVM)"]
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

| Topic | One-Liner | Page to Review |
|-------|-----------|----------------|
| **Algorithms** | Step-by-step instructions to solve problems | [Algorithms](fundamentals/algorithms.md) |
| **Event Loop** | How JS handles async without blocking | [Event Loop](languages/javascript/event-loop.md) |
| **HTTP** | Request/response protocol, ports 80/443 | [Web Servers](backend/web-servers.md) |
| **MVC** | Model-View-Controller separation pattern | [MVC](fundamentals/architecture-patterns/mvc.md) |
| **MVVM** | Observable data binding between VM and View | [MVVM](fundamentals/architecture-patterns/mvvm/index.md) |
| **DOM** | HTML structure that JS can manipulate | [HTML](web/html.md) |
| **CLR** | .NET's runtime that compiles IL to native | [C#](languages/csharp.md) |
| **V8** | Engine that executes JavaScript | *(not written yet)* |

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
- [ ] Update this page with new connections discovered
- [ ] Review "Common Confusions" section - test yourself

---

**Remember**: Complexity is just layers of simplicity stacked together. When lost, trace down to a layer you're comfortable with, then work back up.
