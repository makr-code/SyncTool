# CLAUDE.md — Project Conventions for Claude

This file is read by Claude at the start of every session.
It mirrors the conventions defined in `AGENTS.md` and `.github/copilot-instructions.md`.

---

## Project Overview

Python 3.10+ project using FastAPI, asyncio, Pydantic, and a pluggable vector store architecture.

```
AGENTS.md           ← LLM agent schema (read this too)
wiki/               ← LLM-maintained knowledge base
  index.md          ← content catalog (read first when searching)
  log.md            ← append-only operation log
raw/                ← immutable source documents (never modify)
ai_context/         ← ADRs, API specs, governance policies
ai_working/         ← short-lived working artifacts (not committed)
respo/              ← Python package source code
tests/              ← pytest test suite
```

---

## Python Coding Standards

- **Typing**: Full type hints on all public functions. Use `type | None` (not `Optional`).
- **Async**: All I/O is `async/await`. Use `httpx.AsyncClient`, not `requests`. Always set timeouts.
- **Validation**: `pydantic.BaseModel` for external data; `dataclass` for internal structures.
- **Config**: `pydantic-settings` with `.env` fallback; no bare `os.environ.get`.
- **Logging**: `structlog` — never `print()`.
- **Resources**: `with`/`async with` for all I/O resources.
- **Errors**: specific exception types; no bare `except Exception`.
- **No mutable default arguments** (`def f(x=[]):`).
- **No hidden global state** or singleton imports with side effects.
- **No `Any` types** without a justifying comment.

---

## Toolchain

| Tool | Command | Purpose |
|------|---------|---------|
| Lint | `ruff check .` | Must pass clean |
| Format | `ruff format --check .` | Must pass clean |
| Type check | `mypy` | No new errors |
| Tests | `pytest --cov` | Must be green; coverage ≥ 80 % |
| Security | CodeQL (Python) | No open High/Critical findings |

---

## Architecture Principles

- Dependency Injection over global singletons.
- YAGNI over over-engineering.
- `Protocol` for interfaces — keep domain logic free of infrastructure imports.
- Small, focused functions with clear inputs and outputs.

---

## Wiki Workflows

### Ingest a new source
1. Read the source in `raw/`.
2. Write a summary page in `wiki/sources/`.
3. Update relevant concept pages in `wiki/`.
4. Update `wiki/index.md`.
5. Append to `wiki/log.md`:
   ```
   ## [YYYY-MM-DD] ingest | Title
   Added summary page. Updated: page-a.md, page-b.md.
   ```

### Answer a query
1. Read `wiki/index.md`, then relevant pages.
2. Synthesize answer with citations.
3. File valuable answers as new wiki pages; update index.
4. Append to `wiki/log.md`.

---

## PR Behaviour

- Label AI-generated PRs with `ai-generated`.
- No merge without green CI and human approval.

---

## Key References

- Full coding standards: `.github/copilot-instructions.md`
- Full agent schema: `AGENTS.md`
- ADRs & API specs: `ai_context/`
