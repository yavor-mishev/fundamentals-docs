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

## Dependency Injection (DI)

### What it is:
Dependency Injection is a design pattern and a core feature of ASP.NET Core that manages class dependencies. Instead of classes creating their own dependencies, they receive them from an external source (the DI container).

### The Four Pillars of DI

#### 1. Services (WHAT)
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

#### 2. Consumers (WHO)
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

#### 3. Container (WHERE/HOW)
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

#### 4. Lifetime (WHEN)
**Definition:** Lifetime determines **when** the container creates instances and **how long** they live. This controls instance sharing and memory usage.

**The Three Lifetimes Explained:**

##### Transient - "Always New"
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

##### Scoped - "One Per Request"
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

##### Singleton - "One Forever"
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

### Lifetime Comparison Table

| Lifetime | Created | Shared | Disposed | Use Cases | Thread Safety |
|----------|---------|--------|----------|-----------|---------------|
| **Transient** | Every request | No | After use | Stateless utilities, helpers, email services | Not required |
| **Scoped** | Per HTTP request | Within request | End of request | DbContext, repositories, business logic | Not required |
| **Singleton** | Once | Entire app | App shutdown | Configuration, caching, logging | **REQUIRED** |

### Lifetime Pitfalls - "Captive Dependencies"

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

### Why we need it:
1. **Loose Coupling:** Classes don't depend on concrete implementations, only interfaces
2. **Testability:** Easy to inject mock implementations for unit testing
3. **Maintainability:** Changes to implementations don't affect consumers
4. **Configuration Flexibility:** Switch implementations without changing code
5. **Lifecycle Management:** The framework handles object creation and disposal

### Service Lifetimes:

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

### How to use in production:

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

---

## LINQ (Language Integrated Query)

### What it is:
LINQ is a powerful query syntax built into C# that provides a consistent way to query and manipulate data from different sources (collections, databases, XML, etc.) using a SQL-like syntax.

**Two Syntax Styles:**
1. **Query Syntax:** SQL-like syntax (more readable for complex queries)
2. **Method Syntax:** Extension methods with lambda expressions (more flexible)

### Why we need it:
1. **Type Safety:** Compile-time checking of queries
2. **IntelliSense Support:** IDE provides auto-completion
3. **Unified Syntax:** Same syntax for different data sources
4. **Readability:** Express complex operations clearly
5. **Deferred Execution:** Queries execute only when enumerated
6. **Composable:** Chain operations together

### Common LINQ Operations:

**Filtering (Where):**
```csharp
// Method syntax
var activeProducts = products
    .Where(p => p.IsActive && p.Price > 0)
    .ToList();

// Query syntax
var activeProducts = (from p in products
                      where p.IsActive && p.Price > 0
                      select p).ToList();
```

**Projection (Select):**
```csharp
// Transform to different type
var productDtos = products
    .Select(p => new ProductDto
    {
        Id = p.Id,
        Name = p.Name,
        Price = p.Price,
        DiscountedPrice = p.Price * 0.9m
    })
    .ToList();

// Select specific properties
var productNames = products.Select(p => p.Name).ToList();
```

**Sorting (OrderBy, ThenBy):**
```csharp
var sortedProducts = products
    .OrderBy(p => p.Category)      // Primary sort
    .ThenByDescending(p => p.Price) // Secondary sort
    .ToList();
```

**Grouping (GroupBy):**
```csharp
var productsByCategory = products
    .GroupBy(p => p.Category)
    .Select(g => new
    {
        Category = g.Key,
        Count = g.Count(),
        AveragePrice = g.Average(p => p.Price),
        Products = g.ToList()
    })
    .ToList();
```

**Joining:**
```csharp
var ordersWithProducts = orders
    .Join(products,
        order => order.ProductId,
        product => product.Id,
        (order, product) => new
        {
            OrderId = order.Id,
            ProductName = product.Name,
            Quantity = order.Quantity,
            Total = order.Quantity * product.Price
        })
    .ToList();
```

**Aggregation:**
```csharp
var stats = new
{
    TotalProducts = products.Count(),
    AveragePrice = products.Average(p => p.Price),
    MaxPrice = products.Max(p => p.Price),
    MinPrice = products.Min(p => p.Price),
    TotalValue = products.Sum(p => p.Price * p.Stock)
};
```

**Pagination:**
```csharp
int pageSize = 20;
int pageNumber = 1;

var pagedProducts = products
    .Skip((pageNumber - 1) * pageSize)
    .Take(pageSize)
    .ToList();
```

### How to use in production:

**With Entity Framework (Database Queries):**
```csharp
public class ProductRepository : IProductRepository
{
    private readonly ApplicationDbContext _context;
    
    public ProductRepository(ApplicationDbContext context)
    {
        _context = context;
    }
    
    public async Task<List<Product>> SearchProductsAsync(string searchTerm, decimal? maxPrice)
    {
        // Build query with LINQ
        var query = _context.Products
            .Include(p => p.Category)  // Eager loading
            .AsQueryable();
        
        // Add filters conditionally
        if (!string.IsNullOrEmpty(searchTerm))
        {
            query = query.Where(p => 
                p.Name.Contains(searchTerm) || 
                p.Description.Contains(searchTerm));
        }
        
        if (maxPrice.HasValue)
        {
            query = query.Where(p => p.Price <= maxPrice.Value);
        }
        
        // Execute query and return results
        return await query
            .Where(p => p.IsActive)
            .OrderBy(p => p.Name)
            .ToListAsync();  // Async execution
    }
    
    public async Task<PagedResult<Product>> GetPagedProductsAsync(
        int pageNumber, int pageSize, string sortBy = "Name")
    {
        var query = _context.Products.AsQueryable();
        
        // Dynamic sorting
        query = sortBy switch
        {
            "Name" => query.OrderBy(p => p.Name),
            "Price" => query.OrderBy(p => p.Price),
            "Date" => query.OrderByDescending(p => p.CreatedDate),
            _ => query.OrderBy(p => p.Id)
        };
        
        var totalCount = await query.CountAsync();
        
        var items = await query
            .Skip((pageNumber - 1) * pageSize)
            .Take(pageSize)
            .ToListAsync();
        
        return new PagedResult<Product>
        {
            Items = items,
            TotalCount = totalCount,
            PageNumber = pageNumber,
            PageSize = pageSize
        };
    }
}
```

**Complex Business Logic:**
```csharp
public async Task<OrderSummaryDto> GetOrderSummaryAsync(int userId)
{
    var summary = await _context.Orders
        .Where(o => o.UserId == userId)
        .GroupBy(o => 1) // Group all into one
        .Select(g => new OrderSummaryDto
        {
            TotalOrders = g.Count(),
            TotalSpent = g.Sum(o => o.TotalAmount),
            AverageOrderValue = g.Average(o => o.TotalAmount),
            LastOrderDate = g.Max(o => o.OrderDate),
            MostOrderedProduct = g
                .SelectMany(o => o.OrderItems)
                .GroupBy(oi => oi.ProductId)
                .OrderByDescending(pg => pg.Sum(oi => oi.Quantity))
                .Select(pg => pg.First().Product.Name)
                .FirstOrDefault()
        })
        .FirstOrDefaultAsync();
    
    return summary ?? new OrderSummaryDto();
}
```

**Production Best Practices:**
1. **Use AsNoTracking() for read-only queries:**
```csharp
var products = await _context.Products
    .AsNoTracking()  // Faster for read-only
    .ToListAsync();
```

2. **Avoid multiple enumerations:**
```csharp
// BAD - queries database twice
var products = _context.Products.Where(p => p.IsActive);
var count = products.Count();  // Query 1
var list = products.ToList();  // Query 2

// GOOD - materialize once
var products = await _context.Products
    .Where(p => p.IsActive)
    .ToListAsync();  // Single query
var count = products.Count();  // In-memory
```

3. **Use projection to select only needed fields:**
```csharp
// BAD - loads entire entity
var products = await _context.Products.ToListAsync();

// GOOD - only loads needed fields
var products = await _context.Products
    .Select(p => new { p.Id, p.Name, p.Price })
    .ToListAsync();
```

4. **Use Any() instead of Count() for existence checks:**
```csharp
// BAD - counts all records
if (_context.Products.Count(p => p.Name == name) > 0) { }

// GOOD - stops at first match
if (await _context.Products.AnyAsync(p => p.Name == name)) { }
```

---

## Entity Framework Core

### What it is:
Entity Framework Core (EF Core) is a modern Object-Relational Mapper (ORM) that enables .NET developers to work with databases using .NET objects. It eliminates the need for most data-access code.

**Key Features:**
- Database-agnostic (SQL Server, PostgreSQL, MySQL, SQLite, etc.)
- LINQ support for queries
- Change tracking
- Migrations for schema management
- Conventions and configuration options
- Performance optimizations (compiled queries, batching)

### Why we need it:
1. **Productivity:** Write less boilerplate code
2. **Type Safety:** Compile-time checking of queries
3. **Maintainability:** Schema changes managed through migrations
4. **Database Independence:** Switch databases with minimal code changes
5. **Object-Oriented:** Work with objects, not SQL strings
6. **Testability:** Can be mocked for unit testing

### Core Concepts:

**DbContext:**
The main class that coordinates EF functionality for a data model. Represents a session with the database.

```csharp
public class ApplicationDbContext : DbContext
{
    public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
        : base(options)
    {
    }
    
    // DbSet properties represent tables
    public DbSet<Product> Products { get; set; }
    public DbSet<Category> Categories { get; set; }
    public DbSet<Order> Orders { get; set; }
    public DbSet<OrderItem> OrderItems { get; set; }
    
    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);
        
        // Configure entities using Fluent API
        modelBuilder.Entity<Product>(entity =>
        {
            entity.HasKey(e => e.Id);
            
            entity.Property(e => e.Name)
                .IsRequired()
                .HasMaxLength(200);
            
            entity.Property(e => e.Price)
                .HasColumnType("decimal(18,2)");
            
            entity.HasOne(e => e.Category)
                .WithMany(c => c.Products)
                .HasForeignKey(e => e.CategoryId)
                .OnDelete(DeleteBehavior.Restrict);
            
            // Index for performance
            entity.HasIndex(e => e.Name);
            entity.HasIndex(e => new { e.CategoryId, e.IsActive });
        });
        
        modelBuilder.Entity<Order>(entity =>
        {
            entity.HasMany(o => o.OrderItems)
                .WithOne(oi => oi.Order)
                .HasForeignKey(oi => oi.OrderId)
                .OnDelete(DeleteBehavior.Cascade);
        });
        
        // Seed data
        modelBuilder.Entity<Category>().HasData(
            new Category { Id = 1, Name = "Electronics" },
            new Category { Id = 2, Name = "Books" }
        );
    }
}
```

**Entity Models:**
```csharp
public class Product
{
    public int Id { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public decimal Price { get; set; }
    public int Stock { get; set; }
    public bool IsActive { get; set; }
    public DateTime CreatedDate { get; set; }
    public DateTime? ModifiedDate { get; set; }
    
    // Navigation properties
    public int CategoryId { get; set; }
    public Category Category { get; set; }
    public ICollection<OrderItem> OrderItems { get; set; }
}

public class Category
{
    public int Id { get; set; }
    public string Name { get; set; }
    public ICollection<Product> Products { get; set; }
}
```

### How to use in production:

**Setup and Configuration:**
```csharp
// Program.cs or Startup.cs
public void ConfigureServices(IServiceCollection services)
{
    // SQL Server
    services.AddDbContext<ApplicationDbContext>(options =>
        options.UseSqlServer(
            Configuration.GetConnectionString("DefaultConnection"),
            sqlOptions =>
            {
                sqlOptions.EnableRetryOnFailure(
                    maxRetryCount: 3,
                    maxRetryDelay: TimeSpan.FromSeconds(30),
                    errorNumbersToAdd: null);
                sqlOptions.CommandTimeout(30);
            }));
    
    // Configure for production
    if (!env.IsDevelopment())
    {
        services.AddDbContext<ApplicationDbContext>(options =>
            options.UseSqlServer(connectionString)
                .EnableSensitiveDataLogging(false) // Security
                .EnableDetailedErrors(false));      // Performance
    }
}
```

**Repository Pattern:**
```csharp
public interface IRepository<T> where T : class
{
    Task<T> GetByIdAsync(int id);
    Task<IEnumerable<T>> GetAllAsync();
    Task<T> AddAsync(T entity);
    Task UpdateAsync(T entity);
    Task DeleteAsync(int id);
}

public class Repository<T> : IRepository<T> where T : class
{
    protected readonly ApplicationDbContext _context;
    protected readonly DbSet<T> _dbSet;
    
    public Repository(ApplicationDbContext context)
    {
        _context = context;
        _dbSet = context.Set<T>();
    }
    
    public virtual async Task<T> GetByIdAsync(int id)
    {
        return await _dbSet.FindAsync(id);
    }
    
    public virtual async Task<IEnumerable<T>> GetAllAsync()
    {
        return await _dbSet.AsNoTracking().ToListAsync();
    }
    
    public virtual async Task<T> AddAsync(T entity)
    {
        await _dbSet.AddAsync(entity);
        await _context.SaveChangesAsync();
        return entity;
    }
    
    public virtual async Task UpdateAsync(T entity)
    {
        _dbSet.Update(entity);
        await _context.SaveChangesAsync();
    }
    
    public virtual async Task DeleteAsync(int id)
    {
        var entity = await GetByIdAsync(id);
        if (entity != null)
        {
            _dbSet.Remove(entity);
            await _context.SaveChangesAsync();
        }
    }
}

// Specific repository with custom methods
public interface IProductRepository : IRepository<Product>
{
    Task<List<Product>> GetActiveProductsAsync();
    Task<List<Product>> GetByCategoryAsync(int categoryId);
    Task<Product> GetWithCategoryAsync(int id);
}

public class ProductRepository : Repository<Product>, IProductRepository
{
    public ProductRepository(ApplicationDbContext context) : base(context)
    {
    }
    
    public async Task<List<Product>> GetActiveProductsAsync()
    {
        return await _dbSet
            .AsNoTracking()
            .Where(p => p.IsActive)
            .OrderBy(p => p.Name)
            .ToListAsync();
    }
    
    public async Task<List<Product>> GetByCategoryAsync(int categoryId)
    {
        return await _dbSet
            .AsNoTracking()
            .Include(p => p.Category)
            .Where(p => p.CategoryId == categoryId && p.IsActive)
            .ToListAsync();
    }
    
    public async Task<Product> GetWithCategoryAsync(int id)
    {
        return await _dbSet
            .Include(p => p.Category)
            .FirstOrDefaultAsync(p => p.Id == id);
    }
}
```

**Unit of Work Pattern:**
```csharp
public interface IUnitOfWork : IDisposable
{
    IProductRepository Products { get; }
    IOrderRepository Orders { get; }
    ICategoryRepository Categories { get; }
    Task<int> SaveChangesAsync();
    Task BeginTransactionAsync();
    Task CommitTransactionAsync();
    Task RollbackTransactionAsync();
}

public class UnitOfWork : IUnitOfWork
{
    private readonly ApplicationDbContext _context;
    private IDbContextTransaction _transaction;
    
    public UnitOfWork(
        ApplicationDbContext context,
        IProductRepository products,
        IOrderRepository orders,
        ICategoryRepository categories)
    {
        _context = context;
        Products = products;
        Orders = orders;
        Categories = categories;
    }
    
    public IProductRepository Products { get; }
    public IOrderRepository Orders { get; }
    public ICategoryRepository Categories { get; }
    
    public async Task<int> SaveChangesAsync()
    {
        return await _context.SaveChangesAsync();
    }
    
    public async Task BeginTransactionAsync()
    {
        _transaction = await _context.Database.BeginTransactionAsync();
    }
    
    public async Task CommitTransactionAsync()
    {
        try
        {
            await _context.SaveChangesAsync();
            await _transaction?.CommitAsync();
        }
        catch
        {
            await RollbackTransactionAsync();
            throw;
        }
        finally
        {
            _transaction?.Dispose();
            _transaction = null;
        }
    }
    
    public async Task RollbackTransactionAsync()
    {
        await _transaction?.RollbackAsync();
        _transaction?.Dispose();
        _transaction = null;
    }
    
    public void Dispose()
    {
        _transaction?.Dispose();
        _context?.Dispose();
    }
}
```

**Migrations:**
```bash
# Create a new migration
dotnet ef migrations add InitialCreate

# Update database
dotnet ef database update

# Remove last migration
dotnet ef migrations remove

# Generate SQL script
dotnet ef migrations script
```

**Production Best Practices:**

1. **Connection Resiliency:**
```csharp
services.AddDbContext<ApplicationDbContext>(options =>
    options.UseSqlServer(connectionString,
        sqlOptions => sqlOptions.EnableRetryOnFailure(
            maxRetryCount: 3,
            maxRetryDelay: TimeSpan.FromSeconds(30),
            errorNumbersToAdd: null)));
```

2. **Asynchronous Operations:**
```csharp
// Always use async methods in production
var products = await _context.Products.ToListAsync();
await _context.SaveChangesAsync();
```

3. **Explicit Loading:**
```csharp
// Load related data explicitly when needed
var product = await _context.Products.FindAsync(id);
await _context.Entry(product)
    .Reference(p => p.Category)
    .LoadAsync();
```

4. **Tracking vs No-Tracking:**
```csharp
// No-tracking for read-only (faster)
var products = await _context.Products
    .AsNoTracking()
    .ToListAsync();

// Tracking for updates (default)
var product = await _context.Products.FindAsync(id);
product.Price = 99.99m;
await _context.SaveChangesAsync();
```

5. **Batch Operations:**
```csharp
// Update multiple records efficiently
await _context.Products
    .Where(p => p.CategoryId == categoryId)
    .ExecuteUpdateAsync(s => s
        .SetProperty(p => p.IsActive, false)
        .SetProperty(p => p.ModifiedDate, DateTime.UtcNow));

// Delete multiple records
await _context.Products
    .Where(p => p.Stock == 0)
    .ExecuteDeleteAsync();
```

6. **Connection Pooling:**
```csharp
// Connection string configuration
"DefaultConnection": "Server=.;Database=MyDb;Trusted_Connection=True;MultipleActiveResultSets=true;Min Pool Size=5;Max Pool Size=100;"
```

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

---

## Sitefinity-Specific Considerations

### CMS Architecture Patterns
When working with Sitefinity:
1. **Content APIs:** Use Sitefinity's content APIs with async operations
2. **Custom Modules:** Leverage DI for custom module development
3. **Data Providers:** Understand EF Core for custom data storage
4. **Widgets:** Use dependency injection in widget constructors
5. **Background Tasks:** Implement using IHostedService with proper async patterns

### Performance Optimization
1. **Query Optimization:** Use .AsNoTracking() for read-only content
2. **Caching Strategies:** Implement output caching for public content
3. **Lazy Loading:** Be cautious with navigation properties
4. **Pagination:** Always paginate large content lists
5. **Compilation:** Use compiled queries for repeated operations

### Security Best Practices
1. **Input Validation:** Always validate user input
2. **SQL Injection Prevention:** Use parameterized queries (EF Core does this)
3. **XSS Protection:** Encode output
4. **Authentication:** Understand ASP.NET Core Identity integration
5. **Authorization:** Implement role-based and claims-based authorization

---

## Interview Preparation Tips

### Key Topics to Master:
1. **Middleware Pipeline:** Order and purpose of each middleware
2. **DI Lifetimes:** When to use Transient, Scoped, Singleton
3. **EF Core Patterns:** Repository, Unit of Work, query optimization
4. **LINQ Queries:** Complex queries, joins, grouping
5. **Async/Await:** Proper async patterns, avoiding deadlocks
6. **Configuration:** Options pattern, environment-specific settings
7. **Caching:** Memory cache vs distributed cache strategies
8. **Logging:** Structured logging, log levels

### Common Interview Questions with Answers:

#### 1. "Explain the difference between Scoped and Transient lifetime in DI"
**Short Answer:** 
Transient creates a new instance every time it's requested (like a disposable cup), while Scoped creates one instance per HTTP request that's shared within that request (like a shopping cart). Use Transient for lightweight stateless services, and Scoped for DbContext and repositories that should maintain state during a request but not across requests.

**Key Point:** DbContext should always be Scoped because you want the same context instance used throughout a request for proper transaction management, but a fresh context for each new request.

---

#### 2. "How do you optimize EF Core queries for performance?"
**Short Answer:**
- Use `AsNoTracking()` for read-only queries (no change tracking overhead)
- Project only needed fields with `Select()` instead of loading entire entities
- Use `Any()` instead of `Count() > 0` for existence checks
- Eager load related data with `Include()` to avoid N+1 queries
- Use pagination (`Skip`/`Take`) for large datasets
- Avoid multiple enumerations (materialize query once with `ToListAsync()`)

**Example:**
```csharp
// Optimized query
var products = await _context.Products
    .AsNoTracking()
    .Where(p => p.IsActive)
    .Select(p => new { p.Id, p.Name, p.Price })
    .Skip(page * pageSize)
    .Take(pageSize)
    .ToListAsync();
```

---

#### 3. "What's the difference between IEnumerable and IQueryable?"
**Short Answer:**
- **IEnumerable<T>:** In-memory collection, uses LINQ-to-Objects, filtering happens in C# code
- **IQueryable<T>:** Database query, uses LINQ-to-SQL/EF, filtering happens at database level

**Key Difference:** IQueryable translates expressions to SQL and executes on the database (efficient), while IEnumerable loads all data into memory first, then filters in C# (inefficient for databases).

**Example:**
```csharp
// BAD - Loads ALL products into memory, then filters in C#
IEnumerable<Product> products = _context.Products;
var activeProducts = products.Where(p => p.IsActive).ToList(); // Filters in-memory

// GOOD - Filters at database level with WHERE clause
IQueryable<Product> products = _context.Products;
var activeProducts = await products.Where(p => p.IsActive).ToListAsync(); // SQL: WHERE IsActive = 1
```

---

#### 4. "How does the middleware pipeline work in ASP.NET Core?"
**Short Answer:**
The middleware pipeline is a chain of components that process requests in order, then responses in reverse order. Each middleware can:
1. Process the request and pass to next middleware (or short-circuit)
2. Process the response coming back

**Order matters!** Common order: Exception Handling → HTTPS Redirection → Static Files → Routing → Authentication → Authorization → Endpoints.

**Visualization:**
```
Request  →  [Middleware 1]  →  [Middleware 2]  →  [Middleware 3]  →  Endpoint
Response ←  [Middleware 1]  ←  [Middleware 2]  ←  [Middleware 3]  ←  
```

---

#### 5. "Explain async/await and why we shouldn't use .Result"
**Short Answer:**
`async/await` allows non-blocking I/O operations. When you `await`, the thread is freed to handle other requests instead of blocking.

**Never use `.Result` or `.Wait()`** because:
- Causes deadlocks in ASP.NET Core (especially with synchronization contexts)
- Blocks the thread, reducing scalability
- Defeats the purpose of async programming

**Example:**
```csharp
// BAD - Blocks thread, can deadlock
public IActionResult GetProducts()
{
    var products = _repository.GetAllAsync().Result; // DEADLOCK RISK!
    return View(products);
}

// GOOD - Non-blocking
public async Task<IActionResult> GetProducts()
{
    var products = await _repository.GetAllAsync(); // Thread freed while waiting
    return View(products);
}
```

---

#### 6. "How do you handle transactions in EF Core?"
**Short Answer:**
Three ways:
1. **Implicit:** `SaveChangesAsync()` is automatically a transaction
2. **Explicit:** Use `BeginTransactionAsync()` for multiple `SaveChanges` calls
3. **Transaction Scope:** For distributed transactions

**Example:**
```csharp
// Implicit - single SaveChanges
await _context.Products.AddAsync(product);
await _context.SaveChangesAsync(); // Automatically wrapped in transaction

// Explicit - multiple operations
using var transaction = await _context.Database.BeginTransactionAsync();
try
{
    await _context.Products.AddAsync(product);
    await _context.SaveChangesAsync();
    
    await _context.Orders.AddAsync(order);
    await _context.SaveChangesAsync();
    
    await transaction.CommitAsync();
}
catch
{
    await transaction.RollbackAsync();
    throw;
}
```

---

#### 7. "What are navigation properties and how do Include/ThenInclude work?"
**Short Answer:**
Navigation properties represent relationships between entities (foreign keys become object references). 

- `Include()` - loads related entities (eager loading)
- `ThenInclude()` - loads nested related entities

Without `Include()`, related data is null unless explicitly loaded (lazy loading) or explicitly loaded later.

**Example:**
```csharp
public class Product
{
    public int Id { get; set; }
    public int CategoryId { get; set; }
    public Category Category { get; set; } // Navigation property
}

public class Category
{
    public int Id { get; set; }
    public string Name { get; set; }
    public ICollection<Product> Products { get; set; } // Navigation property
}

// Without Include - Category is NULL
var product = await _context.Products.FirstAsync();
// product.Category == null

// With Include - Category is loaded
var product = await _context.Products
    .Include(p => p.Category) // JOIN with Categories table
    .FirstAsync();
// product.Category.Name is available

// ThenInclude for nested relationships
var orders = await _context.Orders
    .Include(o => o.OrderItems)           // Load OrderItems
        .ThenInclude(oi => oi.Product)    // Then load Product for each OrderItem
            .ThenInclude(p => p.Category) // Then load Category for each Product
    .ToListAsync();
```

---

#### 8. "How would you implement caching in a CMS system?"
**Short Answer:**
Use multi-layer caching:
1. **Memory Cache** (fast, single server) for frequently accessed data
2. **Distributed Cache** (Redis) for multi-server environments
3. **Response Caching** for entire page outputs
4. **Output Caching** for partial views/widgets

**Strategy for CMS:**
- Cache published content (invalidate on publish)
- Cache user permissions/roles (sliding expiration)
- Cache navigation/menus (absolute expiration + manual invalidation)
- Don't cache personalized content
- Use cache keys with versioning for easy invalidation

**Example:**
```csharp
public class ContentService
{
    private readonly IMemoryCache _cache;
    private readonly IContentRepository _repository;
    
    public async Task<Content> GetContentAsync(string slug)
    {
        var cacheKey = $"content:{slug}";
        
        // Try cache first
        if (!_cache.TryGetValue(cacheKey, out Content content))
        {
            // Not in cache, get from database
            content = await _repository.GetBySlugAsync(slug);
            
            // Store in cache with expiration
            var cacheOptions = new MemoryCacheEntryOptions
            {
                AbsoluteExpirationRelativeToNow = TimeSpan.FromMinutes(30),
                SlidingExpiration = TimeSpan.FromMinutes(5)
            };
            
            _cache.Set(cacheKey, content, cacheOptions);
        }
        
        return content;
    }
    
    public void InvalidateContentCache(string slug)
    {
        _cache.Remove($"content:{slug}");
    }
}

// Response caching for entire pages
[ResponseCache(Duration = 300, Location = ResponseCacheLocation.Any)]
public IActionResult PublicPage()
{
    return View();
}
```

### Hands-On Practice:
- Build a simple CMS-like application with products/categories
- Implement Repository pattern with Unit of Work
- Create complex LINQ queries with grouping and joining
- Set up authentication and authorization
- Optimize database queries and implement caching

Good luck with your Sitefinity interview!