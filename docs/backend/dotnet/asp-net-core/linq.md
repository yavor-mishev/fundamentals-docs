# LINQ (Language Integrated Query)

## What it is:
LINQ is a powerful query syntax built into C# that provides a consistent way to query and manipulate data from different sources (collections, databases, XML, etc.) using a SQL-like syntax.

**Two Syntax Styles:**
1. **Query Syntax:** SQL-like syntax (more readable for complex queries)
2. **Method Syntax:** Extension methods with lambda expressions (more flexible)

## Why we need it:
1. **Type Safety:** Compile-time checking of queries
2. **IntelliSense Support:** IDE provides auto-completion
3. **Unified Syntax:** Same syntax for different data sources
4. **Readability:** Express complex operations clearly
5. **Deferred Execution:** Queries execute only when enumerated
6. **Composable:** Chain operations together

## Common LINQ Operations:

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

## How to use in production:

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
