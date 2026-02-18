# C#

## What is C#?

It is an object-oriented programming language created by Microsoft that runs on the .NET Framework. It is widely used for building a variety of applications, including web, mobile, desktop, game development and others.

.NET family: C#, F#, VB.NET

`dotnet` is a CLI (Command Line Interface) which is part of the .NET SDK. This tool lets you create, build, run, test, and publish .NET applications from the terminal.

```bash
# Install the .NET SDK (if not already installed)
dotnet new
dotnet build
dotnet run
dotnet test
```

## Creating a new C# application

If you run the first command mentioned above you will be given a list of templates to choose from. For example, to create a new console application, you can use the following command:

```bash
dotnet new console
```

This will create a new directory with the necessary files for a console application. You can then navigate to that directory, build the application, and run it using the following commands:

```bash
dotnet run
```

After this command you will notice a new folder named `bin` has been created. This folder contains the compiled output of your application. The binaries



## C# vs .NET

C# is a programming language and .NET is a framework. The .NET framework can be used not only with the C# but also with F# or VB.NET.

### CLR
.NET consists of two parts: **CLR** (Common Language Runtime) and **Class Library**.

Before C# there were two languages in the C family: C and C++. With C and C++ when we compile our application on a certain machine that compiled app will run only on that machine. If we compile our app on an x86 Windows machine this app will not run on a linux, mac or other windows machine. So form C/C++ code we compile to **Native Code** for the current machine.

When C# was created the developers borrowed the idea from Java that compiles from Java code to **ByteCode**. C# compiles from C# code **IL** (Intermediat Language) code which is independant from the computer it is running on. This is where CLR comes into the picture. CLR is what compiles the IL code into native code. This process is called **Just-In-Time** compilation or **JIT**. That way you dont have to worry if your app will compile on another computer. As long as that other machine has a CLR, you can run your app.

### Architecture of .NET applications

A .NET application consists of **Classes** which are the building blocks of the app. A Class is a structure that has some **Data** and **Methods**