# Jest

[Jest](https://jestjs.io/) is a delightful JavaScript Testing Framework with a focus on simplicity. It works with projects using Babel, TypeScript, Node.js, React, Angular, Vue.js and Svelte and is widely used for testing JavaScript applications.

Jest runs the tests, provides an assertion library, and offers built-in code coverage reports. It is known for its ease of use, powerful features, and great developer experience. Here are some of the things you can do with jest:

- [test setups and teardowns](https://jestjs.io/docs/api):
    - run some code before and after each test or test suite using the `beforeEach`, `afterEach`, `beforeAll`, and `afterAll` hooks.
    - scoping using `describe` blocks to group related tests together.
    - running a single test or test suite using `.only` modifier.
    - skipping tests using `.skip` modifier.
- [matchers and assertions](https://jestjs.io/docs/expect):
    - assert values using `expect` function.
    - use built-in matchers like `toBe`, `toEqual`, `toContain`, `toHaveLength`, etc.
        - truthiness:
            - `toBeNull()`
            - `toBeUndefined()`
            - `toBeDefined()`
            - `toBeTruthy()`
            - `toBeFalsy()`
        - numbers:
            - `toBeGreaterThan()`
            - `toBeGreaterThanOrEqual()`
            - `toBeLessThan()`
            - `toBeLessThanOrEqual()`
            - `toBeCloseTo()`
        - strings:
            - `toMatch()`
        - arrays and iterables:
            - `toContain()`
        - exceptions:
            - `toThrow()`
    - create custom matchers for specific assertions.