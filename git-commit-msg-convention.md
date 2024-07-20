# Contributing Guidelines

## Commit Message Convention

Follow a strict commit message convention to keep project history clean and
readable. Please follow the format:
```
<type>(<scope>): <subject>
<BLANK LINE>
<body>
<BLANK LINE>
<footer>
```

## Types

- `feat` : A new feature
- `fix`: A bug fix
- `docs`: Documentation only changes
- `style`: Changes that do not affect the meaning of the code (white-space,
           formatting, etc.)
- `refactor`: A code change that neither fixes a bug nor adds a feature
- `perf`: A code change that improves performance
- `test`: Adding missing or correcting existing tests
- `chore`: Changes to the build process or auxiliary tools and libraries such as
           documentation generation

## Examples

```
feat(parser): add ability to parse arrays

This commit adds a new feature to the parser module which allows it to parse
arrays.

Closes #123
```

```
fix(login): handle authentication error

Fixes a bug where the login process would not handle authentication errors
correctly.

Closes #456
```