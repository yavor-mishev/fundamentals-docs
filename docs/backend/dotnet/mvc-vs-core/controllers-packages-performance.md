# Controllers, Packages & Performance

## 6. Controller Differences

### ASP.NET MVC

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

### ASP.NET Core

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

## 7. Package Management

### ASP.NET MVC

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

### ASP.NET Core

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

## 8. Performance

### ASP.NET MVC
- Built on .NET Framework (25+ years of backwards compatibility)
- `System.Web` is monolithic and Windows-specific
- Lots of legacy overhead
- Synchronous-first design

**Typical performance**:
- ~10,000 requests/second (simple scenarios)
- Higher memory usage
- Slower startup time

### ASP.NET Core
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
