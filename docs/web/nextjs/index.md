# NEXT.js

NEXT.js is a popular React framework that enables developers to build server-side rendered and statically generated web applications with ease. It provides a set of features and conventions that simplify the development process, including automatic code splitting, optimized performance, and built-in routing.

## Onboarding Course Recap

Next.js is a React framework that adds functionality to React. Some of the useful features Next.js adds are:

- **Server-side rendering (SSR) and Server Components**: By default, Next.js components are Server Components that render on the server, which helps improve performance and SEO. Client-side components are available by using the `'use client'` directive at the top of the file for components that need interactivity or browser APIs.

- **Built-in compiler**: It comes with a compiler based on SWC (written in Rust) that transforms JSX/TypeScript into JavaScript. This is faster than Babel and requires no additional configuration.

- **File-based routing system**: Next.js uses a file-system based router where folders and files in the `app` directory (App Router) or `pages` directory (Pages Router) automatically become routes. This eliminates the need for manual route configuration.

### Additional Key Features:
- **Automatic code splitting**: Only loads the JavaScript needed for each page
- **Built-in optimizations**: Image optimization, font optimization, and more
- **API routes**: Create backend API endpoints within the same project
- **Static generation and incremental static regeneration**: Pre-render pages at build time or on-demand