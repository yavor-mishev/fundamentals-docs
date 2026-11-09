# ASP.NET Core Interview Prep

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
