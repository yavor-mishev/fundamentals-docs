# Dependency Injection (DI)

## What it is:
Dependency Injection is a design pattern and a core feature of ASP.NET Core that manages class dependencies. Instead of classes creating their own dependencies, they receive them from an external source (the DI container).

## The Four Pillars of DI

### 1. Services (WHAT)
**Definition:** A service is any reusable piece of functionality - a class that does something useful for your application.

**Think of services as tools in a toolbox:**
- `IEmailService` - sends emails
- `IProductRepository` - retrieves/saves products from database
- `ILogger` - logs information
- `IConfiguration` - provides app settings
- `ICacheService` - manages caching

**Key Points:**
- Services are typically defined as **interfaces** (IEmailService) with **concrete implementations** (EmailService)
- Using interfaces makes your code flexible - you can swap implementations without changing consumers
- Services can depend on other services (creating a dependency graph)

**Example - From Tightly Coupled to Service:**
```csharp
// BAD - Tightly coupled, hard to test
public class OrderController : Controller
{
    public IActionResult CreateOrder()
    {
        // Creating dependencies directly
        var smtpClient = new SmtpClient("smtp.gmail.com", 587);
        var emailService = new EmailService(smtpClient);
        var connectionString = "Server=...";
        var context = new ApplicationDbContext(connectionString);
        var orderRepo = new OrderRepository(context);
        
        // Now use them...
        orderRepo.Add(order);
        emailService.Send("Order confirmed!");
    }
}

// GOOD - Using services via DI
public class OrderController : Controller
{
    private readonly IOrderRepository _orderRepo;
    private readonly IEmailService _emailService;
    
    public OrderController(IOrderRepository orderRepo, IEmailService emailService)
    {
        _orderRepo = orderRepo;  // Framework provides these
        _emailService = emailService;
    }
    
    public IActionResult CreateOrder()
    {
        _orderRepo.Add(order);
        _emailService.Send("Order confirmed!");
    }
}
```

### 2. Consumers (WHO)
**Definition:** A consumer is any class that **needs** services to do its job. Consumers **depend on** services.

**Common Consumers:**
- Controllers (need services to handle requests)
- Services (need other services - yes, services can consume services!)
- Middleware (need services to process requests)
- Background tasks (need services to perform work)

**Consumer Patterns:**
```csharp
// Pattern 1: Controller as Consumer
public class ProductController : Controller  // Consumer
{
    private readonly IProductService _service;  // Depends on this service
    private readonly ILogger<ProductController> _logger;  // And this service
    
    public ProductController(IProductService service, ILogger<ProductController> logger)
    {
        _service = service;
        _logger = logger;
    }
}

// Pattern 2: Service as Consumer (services can depend on other services)
public class ProductService : IProductService  // This is BOTH a service AND a consumer
{
    private readonly IProductRepository _repository;  // Consumes repository
    private readonly ICacheService _cache;            // Consumes cache
    private readonly ILogger<ProductService> _logger; // Consumes logger
    
    public ProductService(
        IProductRepository repository,
        ICacheService cache,
        ILogger<ProductService> logger)
    {
        _repository = repository;
        _cache = cache;
        _logger = logger;
    }
    
    public async Task<List<Product>> GetProductsAsync()
    {
        _logger.LogInformation("Getting products");
        
        // Use the services we depend on
        var cached = await _cache.GetAsync<List<Product>>("products");
        if (cached != null) return cached;
        
        var products = await _repository.GetAllAsync();
        await _cache.SetAsync("products", products);
        return products;
    }
}
```

**The Dependency Chain:**
```
Controller (Consumer)
    ↓ depends on
Service (Consumer + Service)
    ↓ depends on
Repository (Consumer + Service)
    ↓ depends on
DbContext (Service)
```

Each level is a consumer of the level below it!

### 3. Container (WHERE/HOW)
**Definition:** The container (also called "service provider" or "IoC container") is the **factory** that creates and manages service instances. It's the "brain" of the DI system.

**What the Container Does:**
1. **Stores registrations** - knows which interface maps to which implementation
2. **Creates instances** - builds objects when requested
3. **Resolves dependencies** - figures out what a class needs and provides it
4. **Manages lifetimes** - knows when to create new instances vs reuse existing ones
5. **Handles disposal** - cleans up resources when services are done

**Container in Action:**
```csharp
// Step 1: REGISTRATION - Teaching the container
public void ConfigureServices(IServiceCollection services)
{
    // Tell container: "When someone asks for IEmailService, give them EmailService"
    services.AddScoped<IEmailService, EmailService>();
    
    // "When someone asks for IProductRepository, give them ProductRepository"
    services.AddScoped<IProductRepository, ProductRepository>();
    
    // "When someone asks for ILogger<T>, give them Logger<T>"
    services.AddLogging();
}

// Step 2: RESOLUTION - Container at work (happens automatically)
// When ASP.NET Core needs to create ProductController...

// Container thinks:
// "ProductController needs IProductRepository and ILogger<ProductController>"
// "Let me check my registrations..."
// "IProductRepository → ProductRepository... but wait, ProductRepository needs IDbContext!"
// "IDbContext → ApplicationDbContext... that needs a connection string!"
// "ILogger<ProductController> → Logger<ProductController>... that needs ILoggerFactory!"
// 
// Container builds the entire dependency tree:
var connectionString = configuration.GetConnectionString("Default");
var dbContext = new ApplicationDbContext(connectionString);
var repository = new ProductRepository(dbContext);
var loggerFactory = GetLoggerFactory();
var logger = new Logger<ProductController>(loggerFactory);
var controller = new ProductController(repository, logger);

// You just write:
public ProductController(IProductRepository repository, ILogger<ProductController> logger)
{
    // Container does all the work above automatically!
}
```

**Manual Container Usage (rarely needed):**
```csharp
public class Startup
{
    public void Configure(IApplicationBuilder app, IServiceProvider serviceProvider)
    {
        // Manually resolve from container (avoid this, prefer constructor injection)
        var emailService = serviceProvider.GetRequiredService<IEmailService>();
        var optionalService = serviceProvider.GetService<IOptionalService>(); // Returns null if not registered
    }
}
```

**Container Validation:**
```csharp
// In production, validate all dependencies at startup
var host = Host.CreateDefaultBuilder(args)
    .UseDefaultServiceProvider(options =>
    {
        options.ValidateScopes = true;      // Catch scope violations
        options.ValidateOnBuild = true;     // Validate at startup, not runtime
    })
    .ConfigureWebHostDefaults(webBuilder =>
    {
        webBuilder.UseStartup<Startup>();
    })
    .Build();
```

### 4. Lifetime (WHEN)
**Definition:** Lifetime determines **when** the container creates instances and **how long** they live. This controls instance sharing and memory usage.

**The Three Lifetimes Explained:**

#### Transient - "Always New"
```csharp
services.AddTransient<IEmailService, EmailService>();
```

**Behavior:** A brand new instance is created **every single time** it's requested.

**Mental Model:** Like disposable coffee cups - use once and throw away.

**When to use:**
- Lightweight, stateless services
- Services that maintain NO state between calls
- Services where instance state would cause problems

**Example Scenario:**
```csharp
public class EmailService : IEmailService
{
    private int _emailsSent = 0;  // This state would be isolated per instance
    
    public void SendEmail(string to, string subject, string body)
    {
        _emailsSent++;  // Each instance tracks its own count
        // Send email...
    }
}

// With Transient:
// Call 1: New instance created, _emailsSent = 0, then 1
// Call 2: New instance created, _emailsSent = 0, then 1
// Call 3: New instance created, _emailsSent = 0, then 1
// Each call gets a fresh instance!
```

**Real-world analogy:**
```csharp
public class OrderController : Controller
{
    private readonly IEmailService _email1;
    private readonly IEmailService _email2;
    
    // If EmailService is Transient, these are TWO DIFFERENT instances
    public OrderController(IEmailService email1, IEmailService email2)
    {
        _email1 = email1;
        _email2 = email2;
        
        // email1 != email2 (different objects)
    }
}
```

#### Scoped - "One Per Request"
```csharp
services.AddScoped<IProductRepository, ProductRepository>();
```

**Behavior:** One instance created **per HTTP request** (or per scope). Same instance shared within that request.

**Mental Model:** Like a shopping cart - follows you through your entire shopping session (request), then gets cleared.

**When to use:**
- Database contexts (DbContext) - MOST COMMON
- Repositories
- Business logic services
- Unit of Work pattern
- Anything that should maintain state during a request but not across requests

**Example Scenario:**
```csharp
services.AddScoped<IProductRepository, ProductRepository>();

// Request 1 comes in:
public class ProductController : Controller
{
    private readonly IProductRepository _repo;
    
    public ProductController(IProductRepository repo)  // Container creates instance A
    {
        _repo = repo;  // Gets instance A
    }
    
    public async Task<IActionResult> GetProduct(int id)
    {
        var product = await _repo.GetByIdAsync(id);  // Uses instance A
        
        // If we resolve IProductRepository again in this request...
        var service = HttpContext.RequestServices.GetService<IProductRepository>();
        // ...we get the SAME instance A
        
        return View(product);
    }
}
// Request 1 ends - Container disposes instance A

// Request 2 comes in:
// Container creates NEW instance B
// Request 2 uses instance B throughout
// Request 2 ends - Container disposes instance B
```

**Why Scoped is perfect for DbContext:**
```csharp
public class ProductService
{
    private readonly ApplicationDbContext _context;
    
    public ProductService(ApplicationDbContext context)
    {
        _context = context;  // Same context used throughout the request
    }
    
    public async Task ProcessOrderAsync(Order order)
    {
        // All these operations use the SAME DbContext
        var product = await _context.Products.FindAsync(order.ProductId);
        product.Stock -= order.Quantity;
        _context.Orders.Add(order);
        await _context.SaveChangesAsync();  // Single transaction!
    }
}

// If Repository and Service both inject ApplicationDbContext,
// they get the SAME instance within a request - perfect for transactions!
```

#### Singleton - "One Forever"
```csharp
services.AddSingleton<ICacheService, MemoryCacheService>();
```

**Behavior:** One instance created **when first requested**, then **reused forever** until application shuts down.

**Mental Model:** Like a shared company refrigerator - everyone uses the same one, never replaced.

**When to use:**
- Configuration settings
- Caching services
- Thread-safe utilities
- Expensive-to-create objects that are stateless or thread-safe

**CRITICAL:** Must be thread-safe! Multiple requests use the same instance simultaneously.

**Example Scenario:**
```csharp
public class CacheService : ICacheService
{
    private readonly ConcurrentDictionary<string, object> _cache = new();
    
    public void Set(string key, object value)
    {
        _cache[key] = value;  // Thread-safe dictionary
    }
    
    public object Get(string key)
    {
        _cache.TryGetValue(key, out var value);
        return value;
    }
}

services.AddSingleton<ICacheService, CacheService>();

// Application starts
// Request 1: Container creates CacheService instance - stores in memory
// Request 2: Container returns the SAME instance
// Request 3: Container returns the SAME instance
// ...
// Request 1000: Container returns the SAME instance
// Application stops: Instance disposed
```

**Singleton Sharing Visualization:**
```csharp
// Time: 9:00 AM - User 1's request
public class Controller1 : Controller
{
    public Controller1(ICacheService cache)  // Gets instance X
    {
        cache.Set("key1", "value1");  // Modifies instance X
    }
}

// Time: 9:00 AM - User 2's request (same time!)
public class Controller2 : Controller
{
    public Controller2(ICacheService cache)  // Gets instance X (SAME instance!)
    {
        var value = cache.Get("key1");  // Can see "value1" from User 1!
    }
}
```

## Lifetime Comparison Table

| Lifetime | Created | Shared | Disposed | Use Cases | Thread Safety |
|----------|---------|--------|----------|-----------|---------------|
| **Transient** | Every request | No | After use | Stateless utilities, helpers, email services | Not required |
| **Scoped** | Per HTTP request | Within request | End of request | DbContext, repositories, business logic | Not required |
| **Singleton** | Once | Entire app | App shutdown | Configuration, caching, logging | **REQUIRED** |

## Lifetime Pitfalls - "Captive Dependencies"

**DANGER: Don't inject shorter-lived services into longer-lived ones!**

```csharp
// BAD - Scoped service injected into Singleton
services.AddSingleton<IReportService, ReportService>();  // Lives forever
services.AddScoped<ApplicationDbContext>();  // Lives per request

public class ReportService : IReportService  // Singleton
{
    private readonly ApplicationDbContext _context;  // Scoped - WRONG!
    
    // This is a "captive dependency" problem
    public ReportService(ApplicationDbContext context)
    {
        _context = context;  
        // This DbContext instance gets captured by the singleton
        // and is reused across ALL requests forever!
        // DbContext is NOT thread-safe - this will cause errors!
    }
}

// GOOD - Factory pattern or IServiceProvider
public class ReportService : IReportService  // Singleton
{
    private readonly IServiceProvider _serviceProvider;
    
    public ReportService(IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider;
    }
    
    public async Task GenerateReportAsync()
    {
        // Create a scope and get a fresh DbContext
        using (var scope = _serviceProvider.CreateScope())
        {
            var context = scope.ServiceProvider.GetRequiredService<ApplicationDbContext>();
            // Use context safely within this scope
        }
    }
}
```

## Why we need it:
1. **Loose Coupling:** Classes don't depend on concrete implementations, only interfaces
2. **Testability:** Easy to inject mock implementations for unit testing
3. **Maintainability:** Changes to implementations don't affect consumers
4. **Configuration Flexibility:** Switch implementations without changing code
5. **Lifecycle Management:** The framework handles object creation and disposal

## Service Lifetimes:

**1. Transient (AddTransient):**
- New instance created every time it's requested
- Best for lightweight, stateless services
- Example: Utility services, helpers

```csharp
services.AddTransient<IEmailService, EmailService>();
```

**2. Scoped (AddScoped):**
- One instance per HTTP request
- Same instance shared within a single request
- Most common for business logic and data access
- Example: DbContext, repository pattern

```csharp
services.AddScoped<IOrderRepository, OrderRepository>();
services.AddScoped<IOrderService, OrderService>();
```

**3. Singleton (AddSingleton):**
- Single instance for the application lifetime
- Shared across all requests and users
- Must be thread-safe!
- Example: Configuration, caching, logging

```csharp
services.AddSingleton<IConfiguration>(configuration);
services.AddSingleton<ICacheService, MemoryCacheService>();
```

## How to use in production:

**Registration (Startup.cs or Program.cs):**
```csharp
public void ConfigureServices(IServiceCollection services)
{
    // Register DbContext with scoped lifetime
    services.AddDbContext<ApplicationDbContext>(options =>
        options.UseSqlServer(Configuration.GetConnectionString("DefaultConnection")));
    
    // Register repositories
    services.AddScoped<IProductRepository, ProductRepository>();
    services.AddScoped<IOrderRepository, OrderRepository>();
    
    // Register business services
    services.AddScoped<IProductService, ProductService>();
    services.AddScoped<IOrderService, OrderService>();
    
    // Register utilities as transient
    services.AddTransient<IEmailService, EmailService>();
    services.AddTransient<IPdfGenerator, PdfGenerator>();
    
    // Register singletons for configuration/caching
    services.AddSingleton<IMemoryCache, MemoryCache>();
    services.AddSingleton<IAppSettings>(sp => 
        sp.GetRequiredService<IOptions<AppSettings>>().Value);
}
```

**Constructor Injection (Most Common):**
```csharp
public class ProductController : Controller
{
    private readonly IProductService _productService;
    private readonly ILogger<ProductController> _logger;
    
    // Dependencies injected via constructor
    public ProductController(
        IProductService productService,
        ILogger<ProductController> logger)
    {
        _productService = productService;
        _logger = logger;
    }
    
    public async Task<IActionResult> Index()
    {
        var products = await _productService.GetAllProductsAsync();
        return View(products);
    }
}
```

**Service Layer Example:**
```csharp
public interface IProductService
{
    Task<List<Product>> GetAllProductsAsync();
    Task<Product> GetByIdAsync(int id);
}

public class ProductService : IProductService
{
    private readonly IProductRepository _repository;
    private readonly ILogger<ProductService> _logger;
    private readonly ICacheService _cache;
    
    public ProductService(
        IProductRepository repository,
        ILogger<ProductService> logger,
        ICacheService cache)
    {
        _repository = repository;
        _logger = logger;
        _cache = cache;
    }
    
    public async Task<List<Product>> GetAllProductsAsync()
    {
        var cacheKey = "all_products";
        
        // Try to get from cache first
        var cachedProducts = await _cache.GetAsync<List<Product>>(cacheKey);
        if (cachedProducts != null)
        {
            _logger.LogInformation("Retrieved products from cache");
            return cachedProducts;
        }
        
        // If not in cache, get from database
        var products = await _repository.GetAllAsync();
        
        // Store in cache for next time
        await _cache.SetAsync(cacheKey, products, TimeSpan.FromMinutes(10));
        
        return products;
    }
}
```

**Production Best Practices:**
- Always inject interfaces, not concrete types
- Avoid injecting too many dependencies (max 3-5, otherwise refactor)
- Be careful with Singleton lifetime - must be thread-safe
- Use Scoped for most business logic and data access
- Dispose of resources properly (use IDisposable, implement Dispose pattern)
- Validate services during startup in production:
```csharp
services.AddControllers()
    .AddControllersAsServices(); // Validates DI registrations at startup
```
