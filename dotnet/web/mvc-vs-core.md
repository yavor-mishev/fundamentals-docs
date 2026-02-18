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

### 1. Project Structure

**ASP.NET MVC**:
```
MyWebApp/
├── App_Start/              # Configuration scattered here
│   ├── RouteConfig.cs      # Routing setup
│   ├── FilterConfig.cs     # Global filters
│   ├── BundleConfig.cs     # CSS/JS bundling
│   └── WebApiConfig.cs     # If using Web API
├── Controllers/
├── Models/
├── Views/
│   └── Web.config          # View engine config
├── Content/                # CSS, images
├── Scripts/                # JavaScript libraries
├── App_Data/               # Local database files
├── Global.asax             # Application startup events
├── Web.config              # Main configuration (XML)
└── packages.config         # NuGet packages list
```

**ASP.NET Core**:
```
MyWebApp/
├── Controllers/
├── Models/
├── Views/
├── wwwroot/                # All static files (public)
│   ├── css/
│   ├── js/
│   ├── lib/
│   └── images/
├── appsettings.json        # Configuration (JSON)
├── appsettings.Development.json  # Environment-specific
├── Program.cs              # Application entry point & setup
└── MyWebApp.csproj         # Project file (SDK-style)
```

**Benefits of Core's Structure**:
- ✅ Simpler, flatter structure
- ✅ All static files in one place (`wwwroot/`)
- ✅ All configuration in `Program.cs` (single source of truth)
- ✅ Environment-specific configs are obvious
- ✅ No special folders with magic behavior

---

### 2. Configuration

#### ASP.NET MVC

**Web.config** (XML-based):
```xml
<configuration>
  <appSettings>
    <add key="ApiKey" value="12345" />
    <add key="MaxItems" value="100" />
  </appSettings>
  <connectionStrings>
    <add name="DefaultConnection" 
         connectionString="Server=.;Database=MyDb;..." />
  </connectionStrings>
  <system.web>
    <compilation debug="true" targetFramework="4.8" />
    <authentication mode="Forms">
      <forms loginUrl="~/Account/Login" timeout="2880" />
    </authentication>
  </system.web>
</configuration>
```

**Global.asax.cs** (Application events):
```csharp
public class MvcApplication : System.Web.HttpApplication
{
    protected void Application_Start()
    {
        AreaRegistration.RegisterAllAreas();
        RouteConfig.RegisterRoutes(RouteTable.Routes);
        BundleConfig.RegisterBundles(BundleTable.Bundles);
        FilterConfig.RegisterGlobalFilters(GlobalFilters.Filters);
    }
}
```

**App_Start/RouteConfig.cs**:
```csharp
public class RouteConfig
{
    public static void RegisterRoutes(RouteCollection routes)
    {
        routes.IgnoreRoute("{resource}.axd/{*pathInfo}");
        
        routes.MapRoute(
            name: "Default",
            url: "{controller}/{action}/{id}",
            defaults: new { controller = "Home", action = "Index", 
                          id = UrlParameter.Optional }
        );
    }
}
```

**Problems**:
- ❌ Configuration scattered across 5+ files
- ❌ XML is verbose and hard to read
- ❌ No built-in environment-specific configuration
- ❌ Magic behavior in `Global.asax` is non-obvious

#### ASP.NET Core

**appsettings.json**:
```json
{
  "ConnectionStrings": {
    "DefaultConnection": "Server=.;Database=MyDb;..."
  },
  "ApiKey": "12345",
  "MaxItems": 100,
  "Logging": {
    "LogLevel": {
      "Default": "Information"
    }
  }
}
```

**Program.cs** (Everything in one place):
```csharp
var builder = WebApplication.CreateBuilder(args);

// Add services (Dependency Injection)
builder.Services.AddControllersWithViews();
builder.Services.AddDbContext<ApplicationDbContext>(options =>
    options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection")));

var app = builder.Build();

// Configure middleware pipeline
if (app.Environment.IsDevelopment())
{
    app.UseDeveloperExceptionPage();
}
else
{
    app.UseExceptionHandler("/Home/Error");
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();
app.UseRouting();
app.UseAuthentication();
app.UseAuthorization();

// Configure routing
app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
```

**Benefits**:
- ✅ Everything in one file - easy to understand the app setup
- ✅ JSON is cleaner and more modern than XML
- ✅ Built-in environment support (`appsettings.Development.json` automatically loaded)
- ✅ Clear, linear flow from top to bottom
- ✅ Type-safe configuration with options pattern

---

### 3. Dependency Injection

#### ASP.NET MVC

**No built-in DI** - must use third-party container like Autofac:

```csharp
// Install-Package Autofac.Mvc5
public class MvcApplication : HttpApplication
{
    protected void Application_Start()
    {
        var builder = new ContainerBuilder();
        
        // Register dependencies
        builder.RegisterControllers(typeof(MvcApplication).Assembly);
        builder.RegisterType<CustomerRepository>().As<ICustomerRepository>();
        builder.RegisterType<EmailService>().As<IEmailService>();
        
        var container = builder.Build();
        DependencyResolver.SetResolver(new AutofacDependencyResolver(container));
        
        // Other startup code...
    }
}
```

**Controller usage**:
```csharp
public class CustomerController : Controller
{
    private readonly ICustomerRepository _repository;
    
    public CustomerController(ICustomerRepository repository)
    {
        _repository = repository;
    }
}
```

**Problems**:
- ❌ Requires third-party library
- ❌ Extra configuration complexity
- ❌ Different containers have different APIs

#### ASP.NET Core

**Built-in DI container**:

```csharp
// Program.cs
var builder = WebApplication.CreateBuilder(args);

// Register services - built into the framework
builder.Services.AddScoped<ICustomerRepository, CustomerRepository>();
builder.Services.AddScoped<IEmailService, EmailService>();
builder.Services.AddTransient<ILogger, FileLogger>();
builder.Services.AddSingleton<IConfiguration>(builder.Configuration);
```

**Controller usage** (identical):
```csharp
public class CustomerController : Controller
{
    private readonly ICustomerRepository _repository;
    private readonly IEmailService _emailService;
    
    public CustomerController(
        ICustomerRepository repository, 
        IEmailService emailService)
    {
        _repository = repository;
        _emailService = emailService;
    }
}
```

**Benefits**:
- ✅ No external dependencies needed
- ✅ Standard API across all ASP.NET Core apps
- ✅ Encourages best practices (constructor injection)
- ✅ Can still swap in third-party containers if needed
- ✅ Works everywhere (controllers, middleware, Razor Pages, etc.)

**Service Lifetimes**:
- `AddTransient` - New instance every time
- `AddScoped` - One instance per HTTP request
- `AddSingleton` - One instance for app lifetime

---

### 4. Request Pipeline: HTTP Modules vs Middleware

#### ASP.NET MVC (HTTP Modules)

**Web.config**:
```xml
<system.webServer>
  <modules>
    <add name="CustomAuthModule" type="MyApp.CustomAuthModule" />
    <add name="LoggingModule" type="MyApp.LoggingModule" />
  </modules>
</system.webServer>
```

**Custom HTTP Module**:
```csharp
public class LoggingModule : IHttpModule
{
    public void Init(HttpApplication context)
    {
        context.BeginRequest += OnBeginRequest;
        context.EndRequest += OnEndRequest;
    }
    
    private void OnBeginRequest(object sender, EventArgs e)
    {
        var app = (HttpApplication)sender;
        // Log request
    }
    
    private void OnEndRequest(object sender, EventArgs e)
    {
        // Log response
    }
    
    public void Dispose() { }
}
```

**Problems**:
- ❌ Event-based model is complex
- ❌ Configured in XML
- ❌ Tied to IIS
- ❌ Hard to control order of execution
- ❌ Difficult to test

#### ASP.NET Core (Middleware)

**Program.cs**:
```csharp
var app = builder.Build();

// Middleware pipeline - order matters!
app.UseHttpsRedirection();      // 1. Redirect HTTP to HTTPS
app.UseStaticFiles();           // 2. Serve static files
app.UseRouting();               // 3. Route matching
app.UseAuthentication();        // 4. Identify user
app.UseAuthorization();         // 5. Check permissions
app.UseCustomLogging();         // 6. Custom logging
app.MapControllers();           // 7. Execute controller

app.Run();
```

**Custom Middleware**:
```csharp
public class LoggingMiddleware
{
    private readonly RequestDelegate _next;
    
    public LoggingMiddleware(RequestDelegate next)
    {
        _next = next;
    }
    
    public async Task InvokeAsync(HttpContext context)
    {
        // Before request
        var startTime = DateTime.UtcNow;
        
        await _next(context);  // Call next middleware
        
        // After response
        var duration = DateTime.UtcNow - startTime;
        Console.WriteLine($"Request took {duration.TotalMilliseconds}ms");
    }
}

// Extension method for easy registration
public static class LoggingMiddlewareExtensions
{
    public static IApplicationBuilder UseCustomLogging(
        this IApplicationBuilder builder)
    {
        return builder.UseMiddleware<LoggingMiddleware>();
    }
}
```

**Benefits**:
- ✅ Simple, linear pipeline - easy to understand
- ✅ Order is explicit and visible
- ✅ Each middleware does one thing
- ✅ Easy to test (just async methods)
- ✅ Cross-platform (not tied to IIS)
- ✅ Supports async/await natively
- ✅ Can short-circuit the pipeline

**Pipeline Flow Example**:
```
Request → Middleware 1 → Middleware 2 → Middleware 3 → Controller
                ↓            ↓            ↓            ↓
Response ← Middleware 1 ← Middleware 2 ← Middleware 3 ← Controller
```

---

### 5. Hosting Model

#### ASP.NET MVC

**Tightly coupled to IIS**:
- Must run on Windows Server with IIS installed
- Application pool manages the app lifecycle
- `System.Web` library is massive and Windows-specific
- Cannot self-host (without significant effort)

**Web.config hosting settings**:
```xml
<system.webServer>
  <handlers>
    <add name="aspNetCore" path="*" verb="*" 
         modules="AspNetCoreModule" />
  </handlers>
</system.webServer>
```

**Problems**:
- ❌ Platform lock-in to Windows
- ❌ IIS is heavyweight
- ❌ Difficult to containerize
- ❌ Can't easily test locally without IIS Express

#### ASP.NET Core

**Flexible hosting with Kestrel**:

**Program.cs** (Self-hosting):
```csharp
var builder = WebApplication.CreateBuilder(args);
builder.Services.AddControllers();

var app = builder.Build();
app.MapControllers();

// Self-hosted web server!
app.Run();  // Runs on Kestrel by default
```

**Run as console app**:
```bash
dotnet run
# Listening on http://localhost:5000
# Listening on https://localhost:5001
```

**Production scenarios**:

1. **Kestrel alone** (development, microservices):
```csharp
app.Run("http://0.0.0.0:5000");
```

2. **Kestrel behind reverse proxy** (production):
```
Internet → Nginx/Apache → Kestrel → ASP.NET Core App
```

3. **IIS with Kestrel** (Windows production):
```
Internet → IIS → Kestrel → ASP.NET Core App
```

4. **Docker container**:
```dockerfile
FROM mcr.microsoft.com/dotnet/aspnet:8.0
COPY . /app
WORKDIR /app
ENTRYPOINT ["dotnet", "MyApp.dll"]
```

**Benefits**:
- ✅ Cross-platform (Linux, Windows, macOS)
- ✅ Self-hosting (great for microservices)
- ✅ Container-friendly (Docker, Kubernetes)
- ✅ Kestrel is extremely fast
- ✅ Can run without a full web server
- ✅ Flexible deployment options

---

### 6. Controller Differences

#### ASP.NET MVC

```csharp
using System.Web.Mvc;

namespace MyApp.Controllers
{
    public class ProductsController : Controller
    {
        // Returns a view
        public ActionResult Index()
        {
            var products = GetProducts();
            return View(products);
        }
        
        // Returns JSON (for AJAX)
        public ActionResult GetProductsJson()
        {
            var products = GetProducts();
            return Json(products, JsonRequestBehavior.AllowGet);
        }
        
        // POST action
        [HttpPost]
        public ActionResult Create(Product product)
        {
            if (ModelState.IsValid)
            {
                SaveProduct(product);
                return RedirectToAction("Index");
            }
            return View(product);
        }
    }
}
```

**Namespace**: `System.Web.Mvc`  
**Return Type**: `ActionResult`

#### ASP.NET Core

```csharp
using Microsoft.AspNetCore.Mvc;

namespace MyApp.Controllers
{
    public class ProductsController : Controller
    {
        // Returns a view
        public IActionResult Index()
        {
            var products = GetProducts();
            return View(products);
        }
        
        // Returns JSON (for AJAX/API)
        public IActionResult GetProductsJson()
        {
            var products = GetProducts();
            return Json(products);  // No JsonRequestBehavior needed
        }
        
        // POST action
        [HttpPost]
        public IActionResult Create(Product product)
        {
            if (ModelState.IsValid)
            {
                SaveProduct(product);
                return RedirectToAction("Index");
            }
            return View(product);
        }
        
        // API endpoint (same controller!)
        [HttpGet("api/products")]
        public IActionResult GetProducts()
        {
            return Ok(GetProducts());  // Returns 200 OK with JSON
        }
    }
}
```

**Namespace**: `Microsoft.AspNetCore.Mvc`  
**Return Type**: `IActionResult` (interface)

**Benefits of Core**:
- ✅ Can mix MVC (views) and API (JSON) in same controller
- ✅ No `JsonRequestBehavior.AllowGet` needed
- ✅ Better async support
- ✅ More return types (`Ok()`, `NotFound()`, `BadRequest()`, etc.)

---

### 7. Package Management

#### ASP.NET MVC

**packages.config**:
```xml
<?xml version="1.0" encoding="utf-8"?>
<packages>
  <package id="Microsoft.AspNet.Mvc" version="5.2.7" targetFramework="net48" />
  <package id="Microsoft.AspNet.Razor" version="3.2.7" targetFramework="net48" />
  <package id="Microsoft.AspNet.WebPages" version="3.2.7" targetFramework="net48" />
  <package id="Newtonsoft.Json" version="13.0.1" targetFramework="net48" />
  <package id="EntityFramework" version="6.4.4" targetFramework="net48" />
</packages>
```

**Packages folder**:
```
Solution/
├── packages/               # All NuGet packages stored here
│   ├── Microsoft.AspNet.Mvc.5.2.7/
│   ├── Newtonsoft.Json.13.0.1/
│   └── ...
├── MyWebApp/
└── MyWebApp.sln
```

**Problems**:
- ❌ XML format
- ❌ Solution-level packages folder (can get huge)
- ❌ Packages checked into source control (sometimes)
- ❌ Separate file from project file

#### ASP.NET Core

**MyApp.csproj** (SDK-style):
```xml
<Project Sdk="Microsoft.NET.Sdk.Web">
  <PropertyGroup>
    <TargetFramework>net8.0</TargetFramework>
  </PropertyGroup>
  
  <ItemGroup>
    <PackageReference Include="Microsoft.AspNetCore.Mvc" Version="8.0.0" />
    <PackageReference Include="Newtonsoft.Json" Version="13.0.3" />
    <PackageReference Include="Microsoft.EntityFrameworkCore" Version="8.0.0" />
  </ItemGroup>
</Project>
```

**Global package cache**:
- Packages stored in `~/.nuget/packages/` (user profile)
- Shared across all projects
- No solution-level packages folder

**Benefits**:
- ✅ Packages in project file (single source of truth)
- ✅ Cleaner, more compact syntax
- ✅ Global cache saves disk space
- ✅ Automatic package restore
- ✅ Easier to see dependencies at a glance

---

### 8. Performance

#### ASP.NET MVC
- Built on .NET Framework (25+ years of backwards compatibility)
- `System.Web` is monolithic and Windows-specific
- Lots of legacy overhead
- Synchronous-first design

**Typical performance**:
- ~10,000 requests/second (simple scenarios)
- Higher memory usage
- Slower startup time

#### ASP.NET Core
- Built from scratch for performance
- Async/await first-class support
- Minimal, modular design
- Optimized for modern hardware

**Typical performance**:
- ~100,000+ requests/second (same scenarios)
- Lower memory footprint
- Faster startup time
- Much better JSON serialization

**Benchmark example** (TechEmpower):
- ASP.NET Core consistently ranks in top 10 fastest frameworks
- ASP.NET MVC doesn't even appear on modern benchmarks

**Benefits**:
- ✅ 10x+ better throughput
- ✅ Lower cloud costs (can serve more with less)
- ✅ Better scalability
- ✅ Faster response times

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