# Project Structure & Configuration

## 1. Project Structure

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

## 2. Configuration

### ASP.NET MVC

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

### ASP.NET Core

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
