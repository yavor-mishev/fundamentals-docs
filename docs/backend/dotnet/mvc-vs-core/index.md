# ASP.NET MVC vs ASP.NET Core

## Overview

Both frameworks are for **building web applications** using the MVC pattern, but they represent two different generations:

- **ASP.NET MVC** (2009-2019) - Legacy framework built on .NET Framework
- **ASP.NET Core** (2016-present) - Modern, complete rewrite built on .NET Core/.NET

**Key Point**: You use **either** ASP.NET MVC **or** ASP.NET Core for a project, not both simultaneously.

---

## Platform & Development Differences

| Aspect | ASP.NET MVC | ASP.NET Core |
|--------|-------------|--------------|
| **Built On** | .NET Framework | .NET Core / .NET |
| **Development OS** | Windows only | Windows, macOS, Linux |
| **Production OS** | Windows only | Windows, macOS, Linux |
| **Web Server** | IIS only | IIS, Kestrel, Nginx, Apache |
| **IDE Options** | Visual Studio (Windows), Rider (Windows) | VS Code, Visual Studio, Rider (any OS) |
| **Deployment** | Windows Server with IIS | Any OS, containers, cloud |

### What This Means

**ASP.NET MVC**:
- Your **development machine** must be Windows
- Your **production server** must be Windows
- You're locked into the Microsoft/Windows ecosystem

**ASP.NET Core**:
- Develop on **any OS** (Mac, Linux, Windows)
- Deploy to **any OS** (often Linux for cost savings in the cloud)
- True cross-platform flexibility

---

## The Story: Why the Differences Exist

### ASP.NET Core Was a Complete Rewrite

In 2016, Microsoft didn't just port ASP.NET MVC to run cross-platform. They **completely rebuilt the framework from scratch**, asking:

> "If we were building a web framework today, knowing everything we've learned over 15 years, what would it look like?"

### What They Did

✅ **Kept what worked**:
- MVC pattern (Model-View-Controller)
- Razor view engine
- Core routing concepts
- C# as the primary language

✅ **Modernized what was outdated**:
- Configuration system
- Dependency injection
- Hosting model
- Request pipeline

✅ **Removed the bloat**:
- Dependency on `System.Web` (massive, Windows-only library)
- Tight coupling to IIS
- XML-heavy configuration

✅ **Added what was missing**:
- Built-in dependency injection
- Middleware pipeline
- Cross-platform support
- Cloud-first design
- Performance optimizations

### Influences from Other Frameworks

By 2016, frameworks like Node.js/Express, Ruby on Rails, and Django had popularized:
- Middleware pipelines for request processing
- JSON-based configuration
- Convention over configuration
- Lightweight, modular design
- Self-hosting capabilities

Microsoft incorporated these proven patterns into ASP.NET Core.

---

## Structural Differences

The differences are covered in detail on three pages:

- [Project Structure & Configuration](structure-and-configuration.md)
- [Dependency Injection, Request Pipeline & Hosting](di-pipeline-hosting.md)
- [Controllers, Packages & Performance](controllers-packages-performance.md)

---

## Migration: Can You Convert Between Them?

**Short answer**: Yes, but it's not trivial.

### What needs to change:

1. **Project file** - Convert to SDK-style `.csproj`
2. **Configuration** - `Web.config` → `appsettings.json` + `Program.cs`
3. **Startup** - `Global.asax` → `Program.cs`
4. **Namespaces** - `System.Web.Mvc` → `Microsoft.AspNetCore.Mvc`
5. **HTTP Modules** - Rewrite as middleware
6. **Dependency Injection** - Remove third-party DI, use built-in
7. **Package references** - Update all NuGet packages
8. **Static files** - Move to `wwwroot/`
9. **Authentication** - Rewrite using ASP.NET Core Identity
10. **Session state** - Different APIs

### Migration effort:
- **Small app** (5-10 controllers): 1-2 weeks
- **Medium app** (20-50 controllers): 1-2 months
- **Large app** (100+ controllers): 3-6+ months

Microsoft provides [migration guides](https://docs.microsoft.com/aspnet/core/migration), but significant effort is required for large applications.

---

## Summary: Two Generations of Web Development

Think of ASP.NET MVC and ASP.NET Core as **two generations of the same idea**:

### ASP.NET MVC (2009-2019)
- 🕰️ Legacy framework from different era
- 🪟 Windows-only (development and production)
- 🏢 Enterprise-focused, IIS-dependent
- 📦 Monolithic, tightly coupled
- ⚠️ Maintenance mode (security fixes only)

### ASP.NET Core (2016-present)
- 🚀 Modern, performance-focused
- 🌍 Cross-platform (any OS)
- ☁️ Cloud-native, container-ready
- 🧩 Modular, loosely coupled
- ✅ Actively developed, long-term future

### The Bottom Line

To end users, apps built with either framework look the same (same URLs, same HTML). But under the hood:

- **ASP.NET Core** = Complete rewrite incorporating 15+ years of lessons learned
- **Better architecture** = Middleware, built-in DI, modular design
- **Better performance** = 10x+ faster, lower resource usage
- **Better developer experience** = Simpler config, better tooling, cross-platform

If starting a new project in 2025, **always choose ASP.NET Core**. ASP.NET MVC is only relevant for maintaining existing applications.
