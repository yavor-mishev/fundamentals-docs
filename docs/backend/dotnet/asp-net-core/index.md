# ASP.NET Core

## Overview
- Modern framework for building fast and secure web applications
- Web apps using this framework can be developed on Windows, macOS, and Linux
- Built on top of .NET Core (or .NET 5/6/7/8+), which is a cross-platform, high-performance framework for building applications
- Unified platform for web UI, web APIs, and real-time communication (SignalR)
- High performance - one of the fastest web frameworks available
- Built-in dependency injection
- Cloud-ready, environment-based configuration system
- Lightweight, modular HTTP request pipeline

## Key Architecture Concepts

### Request Pipeline & Middleware
**What it is:**
The ASP.NET Core request pipeline is a series of middleware components that process HTTP requests and responses. Each middleware component can:
- Process an incoming request
- Pass the request to the next middleware
- Process the response on the way back

**Why we need it:**
- Provides modular, reusable components for handling cross-cutting concerns (logging, authentication, error handling)
- Allows fine-grained control over request processing
- Enables performance optimization by only including necessary middleware

**How to use in production:**
```csharp
public class Startup
{
    public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
    {
        if (env.IsDevelopment())
        {
            app.UseDeveloperExceptionPage();
        }
        else
        {
            app.UseExceptionHandler("/Error");
            app.UseHsts(); // HTTP Strict Transport Security
        }

        app.UseHttpsRedirection();
        app.UseStaticFiles();
        app.UseRouting();
        
        // Authentication must come before Authorization
        app.UseAuthentication();
        app.UseAuthorization();
        
        app.UseEndpoints(endpoints =>
        {
            endpoints.MapControllers();
            endpoints.MapRazorPages();
        });
    }
}
```

**Best Practices:**
- Order matters! Authentication before Authorization, Routing before Endpoints
- Use HTTPS redirection in production
- Implement proper exception handling middleware
- Enable response compression for better performance
- Use response caching where appropriate

---

## Additional Key Concepts

### Configuration & Options Pattern

**What it is:**
Strongly-typed configuration management using the Options pattern.

```csharp
// appsettings.json
{
  "AppSettings": {
    "ApplicationName": "Sitefinity CMS",
    "MaxUploadSize": 10485760,
    "EnableCaching": true,
    "CacheExpirationMinutes": 30
  },
  "EmailSettings": {
    "SmtpServer": "smtp.example.com",
    "Port": 587,
    "FromEmail": "noreply@example.com"
  }
}

// Configuration classes
public class AppSettings
{
    public string ApplicationName { get; set; }
    public long MaxUploadSize { get; set; }
    public bool EnableCaching { get; set; }
    public int CacheExpirationMinutes { get; set; }
}

public class EmailSettings
{
    public string SmtpServer { get; set; }
    public int Port { get; set; }
    public string FromEmail { get; set; }
    public string Username { get; set; }
    public string Password { get; set; }
}

// Registration
services.Configure<AppSettings>(Configuration.GetSection("AppSettings"));
services.Configure<EmailSettings>(Configuration.GetSection("EmailSettings"));

// Usage via IOptions
public class ContentService
{
    private readonly AppSettings _appSettings;
    
    public ContentService(IOptions<AppSettings> appSettings)
    {
        _appSettings = appSettings.Value;
    }
    
    public bool CanUploadFile(long fileSize)
    {
        return fileSize <= _appSettings.MaxUploadSize;
    }
}
```

### Logging

**What it is:**
Built-in logging framework with support for various providers.

```csharp
public class ProductController : Controller
{
    private readonly ILogger<ProductController> _logger;
    
    public ProductController(ILogger<ProductController> logger)
    {
        _logger = logger;
    }
    
    public async Task<IActionResult> GetProduct(int id)
    {
        _logger.LogInformation("Fetching product with ID: {ProductId}", id);
        
        try
        {
            var product = await _productService.GetByIdAsync(id);
            
            if (product == null)
            {
                _logger.LogWarning("Product not found: {ProductId}", id);
                return NotFound();
            }
            
            return Ok(product);
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error fetching product {ProductId}", id);
            return StatusCode(500, "Internal server error");
        }
    }
}

// Configure in Program.cs
builder.Logging.ClearProviders();
builder.Logging.AddConsole();
builder.Logging.AddDebug();
builder.Logging.AddEventLog();

// In production, use structured logging (Serilog, NLog)
builder.Host.UseSerilog((context, configuration) =>
    configuration.ReadFrom.Configuration(context.Configuration));
```

### Caching

**What it is:**
In-memory or distributed caching to improve performance.

```csharp
// Memory Cache
public class CacheService : ICacheService
{
    private readonly IMemoryCache _cache;
    
    public CacheService(IMemoryCache cache)
    {
        _cache = cache;
    }
    
    public async Task<T> GetOrCreateAsync<T>(
        string key,
        Func<Task<T>> factory,
        TimeSpan? expiration = null)
    {
        if (_cache.TryGetValue(key, out T cachedValue))
        {
            return cachedValue;
        }
        
        var value = await factory();
        
        var cacheOptions = new MemoryCacheEntryOptions
        {
            AbsoluteExpirationRelativeToNow = expiration ?? TimeSpan.FromMinutes(30),
            SlidingExpiration = TimeSpan.FromMinutes(10)
        };
        
        _cache.Set(key, value, cacheOptions);
        return value;
    }
}

// Distributed Cache (Redis)
services.AddStackExchangeRedisCache(options =>
{
    options.Configuration = Configuration.GetConnectionString("Redis");
    options.InstanceName = "SitefinityInstance";
});
```

### Authentication & Authorization

**What it is:**
Security features for user identity and access control.

```csharp
// Setup
services.AddAuthentication(JwtBearerDefaults.AuthenticationScheme)
    .AddJwtBearer(options =>
    {
        options.TokenValidationParameters = new TokenValidationParameters
        {
            ValidateIssuer = true,
            ValidateAudience = true,
            ValidateLifetime = true,
            ValidateIssuerSigningKey = true,
            ValidIssuer = Configuration["Jwt:Issuer"],
            ValidAudience = Configuration["Jwt:Audience"],
            IssuerSigningKey = new SymmetricSecurityKey(
                Encoding.UTF8.GetBytes(Configuration["Jwt:Key"]))
        };
    });

services.AddAuthorization(options =>
{
    options.AddPolicy("AdminOnly", policy =>
        policy.RequireRole("Administrator"));
    
    options.AddPolicy("ContentEditor", policy =>
        policy.RequireClaim("Permission", "EditContent"));
});

// Usage
[Authorize(Roles = "Administrator")]
public class AdminController : Controller
{
    [Authorize(Policy = "ContentEditor")]
    public IActionResult EditContent()
    {
        return View();
    }
}
```

### Async/Await

**Best practices for asynchronous programming:**
```csharp
// DO: Use async/await for I/O operations
public async Task<List<Product>> GetProductsAsync()
{
    return await _context.Products.ToListAsync();
}

// DON'T: Use .Result or .Wait() - causes deadlocks
public List<Product> GetProducts()
{
    return _context.Products.ToListAsync().Result; // BAD!
}

// DO: Use ConfigureAwait(false) in library code
public async Task<string> GetDataAsync()
{
    var response = await httpClient.GetAsync(url).ConfigureAwait(false);
    return await response.Content.ReadAsStringAsync().ConfigureAwait(false);
}

// DO: Propagate async all the way
public async Task<IActionResult> Index()
{
    var products = await _productService.GetProductsAsync();
    return View(products);
}
```
