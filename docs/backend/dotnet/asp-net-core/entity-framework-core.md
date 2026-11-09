# Entity Framework Core

## What it is:
Entity Framework Core (EF Core) is a modern Object-Relational Mapper (ORM) that enables .NET developers to work with databases using .NET objects. It eliminates the need for most data-access code.

**Key Features:**
- Database-agnostic (SQL Server, PostgreSQL, MySQL, SQLite, etc.)
- LINQ support for queries
- Change tracking
- Migrations for schema management
- Conventions and configuration options
- Performance optimizations (compiled queries, batching)

## Why we need it:
1. **Productivity:** Write less boilerplate code
2. **Type Safety:** Compile-time checking of queries
3. **Maintainability:** Schema changes managed through migrations
4. **Database Independence:** Switch databases with minimal code changes
5. **Object-Oriented:** Work with objects, not SQL strings
6. **Testability:** Can be mocked for unit testing

## Core Concepts:

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

## How to use in production:

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
