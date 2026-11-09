# Dependency Injection, Request Pipeline & Hosting

## 3. Dependency Injection

### ASP.NET MVC

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

### ASP.NET Core

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

## 4. Request Pipeline: HTTP Modules vs Middleware

### ASP.NET MVC (HTTP Modules)

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

### ASP.NET Core (Middleware)

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

## 5. Hosting Model

### ASP.NET MVC

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

### ASP.NET Core

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
