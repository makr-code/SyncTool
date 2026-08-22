# AGENTS.md — LLM Agent Schema

This file is the **schema document** for all LLM agents working in this repository.
It defines the structure of the project, the conventions for the persistent wiki, and the workflows for ingesting sources, answering questions, and maintaining the knowledge base.

Read this file at the start of every session. Keep it up to date as conventions evolve.

---

## Project Overview

This is a Python 3.10+ project using FastAPI, asyncio, Pydantic, and a pluggable vector store architecture. The primary toolchain is `ruff` (lint + format), `mypy` (type checking), and `pytest` (testing, coverage ≥ 80 %).

Key directories:

```
AGENTS.md           ← this file (LLM agent schema)
wiki/               ← LLM-maintained persistent knowledge base
  index.md          ← content catalog (read first when searching)
  log.md            ← append-only operation log
raw/                ← immutable source documents (never modify)
ai_context/         ← long-lived architectural context (ADRs, API specs, guidelines)
ai_working/         ← short-lived working artifacts (plans, debug, notes — not committed)
respo/              ← Python package source code
tests/              ← pytest test suite
```

---

## The Wiki

The `wiki/` directory is a **persistent, LLM-maintained knowledge base**. You write it; the human reads it.

### Conventions

- One markdown file per concept, entity, or topic.
- File names: `kebab-case.md` (e.g., `rag-pipeline.md`, `vector-store-interface.md`).
- Every page starts with a level-1 heading matching the file name concept.
- Cross-reference related pages using relative links: `[RAG Pipeline](rag-pipeline.md)`.
- Add YAML frontmatter for metadata:
  ```yaml
  ---
  tags: [rag, architecture]
  sources: 2
  updated: 2026-08-01
  ---
  ```
- Keep pages focused. Prefer many small pages over one large page.
- `index.md` and `log.md` are special files — follow their format exactly (see below).

### index.md format

```markdown
# Wiki Index

## Architecture
- [RAG Pipeline](rag-pipeline.md) — End-to-end retrieval-augmented generation flow
- [Vector Store Interface](vector-store-interface.md) — Pluggable VectorStore abstraction

## Concepts
- …

## Sources
- …
```

Update `index.md` on every ingest and every time a new page is created.

### log.md format

Append-only. Each entry starts with a consistent prefix for grep-ability:

```markdown
## [YYYY-MM-DD] <operation> | <title>

Short description of what was done and what changed.
```

Example operations: `ingest`, `query`, `lint`, `create-page`, `update-page`.

---

## Workflows

### Ingest a new source

1. Read the source document in `raw/`.
2. Discuss key takeaways if the human is present.
3. Write a summary page in `wiki/` (e.g., `wiki/sources/article-title.md`).
4. Update all relevant concept and entity pages — a single source typically touches 5–15 pages.
5. Update `wiki/index.md` with new or changed pages.
6. Append an entry to `wiki/log.md`:
   ```
   ## [2026-08-01] ingest | Article Title
   Added summary page. Updated: rag-pipeline.md, vector-store-interface.md.
   ```

### Answer a query

1. Read `wiki/index.md` to find relevant pages.
2. Read the relevant pages.
3. Synthesize an answer with citations (link to wiki pages).
4. If the answer is valuable and reusable, file it as a new wiki page and update the index.
5. Append to `wiki/log.md`:
   ```
   ## [2026-08-01] query | How does reranking work?
   Answered. Filed result as wiki/reranking.md.
   ```

### Lint the wiki

Periodically check for:
- Contradictions between pages
- Stale claims superseded by newer sources
- Orphan pages with no inbound links
- Important concepts mentioned but lacking their own page
- Missing cross-references
- Data gaps worth investigating

Append a lint report entry to `wiki/log.md`.

---

## Python Coding Standards

When writing or reviewing Python code in this repository:

- **Typing**: Full type hints on all public functions. Use `type | None` (not `Optional`).
- **Async**: All I/O is `async/await`. Use `httpx.AsyncClient`, not `requests`.
- **Validation**: `pydantic.BaseModel` for external data; `dataclass` for internal structures.
- **Config**: `pydantic-settings` with `.env` fallback; no bare `os.environ.get`.
- **Logging**: `structlog` — never `print()`.
- **Resources**: `with`/`async with` for all I/O resources.
- **Errors**: specific exception types; no bare `except Exception`.

See `.github/copilot-instructions.md` for the full coding standards reference.
See `ai_context/` for ADRs, API specs, and governance policies.

---

## ai_context/ vs. wiki/ vs. ai_working/

| Directory | Owner | Lifetime | Purpose |
|-----------|-------|----------|---------|
| `ai_context/` | Human + LLM (co-authored) | Permanent | Architectural decisions, API specs, team guidelines |
| `wiki/` | LLM (human reads) | Permanent, compounding | Domain knowledge, source summaries, concept pages |
| `raw/` | Human (LLM reads only) | Permanent | Immutable source documents |
| `ai_working/` | LLM | Temporary (not committed) | Plans, debug traces, short-lived notes |
