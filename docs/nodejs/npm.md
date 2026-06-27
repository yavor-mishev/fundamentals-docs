# NPM

NPM (Node Package Manager) is the default package manager for Node.js. It allows developers to install, share, and manage dependencies (node modules) for their Node.js projects.

NPM is used to add third-party libraries and tools to a project, making it easier to manage and maintain code. It also provides a way to publish and distribute your own packages to the wider Node.js community.

## Installing NPM

NPM is included with Node.js, so when you install Node.js, you also get NPM. You can download and install Node.js from the official website: [https://nodejs.org/](https://nodejs.org/).

## Unisng NPM

First you need to initialize it in your project folder by running:

```bash
npm init
```

This command will walk you through some initial setup of a series of metadata that will later be stored in a `package.json` file in your project directory. In that file you can define your project name, version, description, entry point, test command, git repository, keywords, author, and license.

After you finnish with that initial setup you are ready to start installing packages.

## Installing Packages

To install a package, you can use the `npm install` or `npm i` command followed by the package name. For example, to install the popular Express framework or a th epopular package Underscore, you would run:

```bash
npm install express
npm i underscore
```

Now in your project folder a new folder named `node_modules` will be created where all the installed packages will be stored.

A `package-lock.json` file will be created to keep track of the exact versions of the installed packages.
And the `package.json` file will be updated to include the installed packages as dependencies.

```json
dependencies: {
  "express": "^4.17.1",
  "underscore": "^1.9.1"
}
```
## node_modules Folder

The node_modules folder is where NPM stores all the installed packages for your project. This folder can become quite large, as it contains not only the packages you explicitly install and use but also their dependencies.

It's important to note that the node_modules folder should not be committed to version control systems like Git. Instead, you should commit the package.json and package-lock.json files, which allow others to recreate the node_modules folder by running `npm install`. To ignore the node_modules folder, you can add it to your `.gitignore` file. If you don't have a `.gitignore` file yet, you can create one in the root of your project folder and add the following line:

```text
node_modules/
```

You will see how the node_modules folder turns dark in your code editor, indicating that it is being ignored by Git.

In the past if two npm packages that you installed depended on some other package but required different versions of that package, npm would install both versions in a nested manner. This could lead to very deep and complex folder structures within node_modules. However, with the introduction of npm v3 and later versions, npm now uses a flat dependency structure whenever possible, reducing the depth of the node_modules folder and making it easier to manage.

## Global vs Local Installation

By default, NPM installs packages locally to the project directory (inside the node_modules folder). However, you can also install packages globally using the `-g` flag. Global installations make the package available system-wide, allowing you to use command-line tools provided by the package from any location on your machine.

```bash
npm install -g <package-name>
```

The `npm` command-line tool itself is an example of a globally installed package.

If you install a package locally, you can't use it from the command line unless you reference it directly from the `node_modules/.bin` directory or use `npx` (which comes with NPM) to run it. If you want to use a package's command-line tool globally, you should install it with the `-g` flag.

## Semantic Versioning (SemVer)

NPM uses Semantic Versioning (SemVer) to manage package versions. A version number is typically in the format of `MAJOR.MINOR.PATCH`:
- **MAJOR** version when you make incompatible API changes,
- **MINOR** version when you add functionality in a backward-compatible manner,
- **PATCH** version when you make backward-compatible bug fixes.

When specifying package versions in your `package.json`, you can use symbols like `^` and `~` to indicate version ranges:
- `^1.2.3` allows updates that do not change the leftmost non-zero digit (i.e., it will accept any version from `1.2.3` to `<2.0.0`).
- `~1.2.3` allows updates to the most recent patch version (i.e., it will accept any version from `1.2.3` to `<1.3.0`).

## Viewing an NPM Package

On way to view and get familiar with an NPM package is to visit the NPM website at [https://www.npmjs.com/](https://www.npmjs.com/) and search for the package you are interested in. Each package page provides information about the package, including its description, version history, dependencies, and usage instructions.

Another way is to use the command line:

```bash
npm view <package-name>
npm view <package-name> versions
npm view <package-name> dependencies
```

## DevDependencies

Some of the npm packages that you install; will be essential for your project to run, while others are only needed during development (e.g., testing frameworks, build tools).

To install a package as a development dependency, you can use the `--save-dev` or `-D` flag:

```bash
npm install <package-name> --save-dev
```

This will add the package to the `devDependencies` section of your `package.json` file:

```json
"devDependencies": {
  "<package-name>": "^1.0.0"
}
```

When you or someone else runs `npm install`, NPM will install both `dependencies` and `devDependencies` by default. However, in production environments, you can choose to install only the `dependencies` by using the `--production` flag:

```bash

## Common NPM Commands

Here are some common NPM commands you might find useful:

- `npm install <package-name>`: Installs a package locally.
- `npm install -g <package-name>`: Installs a package globally.
- `npm uninstall <package-name>`: Uninstalls a package.
- `npm update <package-name>`: Updates a package to the latest version.
- `npm list`: Lists all installed packages in the current project including the ones you might not be using directly in your project.
- `npm list -g`: Lists all globally installed packages.
- `npm list --depth=0`: Lists only the top-level packages in the current project.
- `npm outdated`: Checks for outdated packages.
- `npm init`: Initializes a new Node.js project and creates a package.json file.
- `npm run <script-name>`: Runs a script defined in the package.json file.
- `npm publish`: Publishes a package to the NPM registry.
