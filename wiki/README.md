# Wiki

This directory is the **LLM-maintained persistent knowledge base** for this project.

The LLM writes and maintains all content here. You read it.

## Structure

```
wiki/
├── index.md          ← content catalog — read this first when searching
├── log.md            ← append-only operation log
├── sources/          ← one summary page per ingested source document
└── <concept>.md      ← concept, entity, and topic pages
```

## Rules

- **LLM writes** — humans don't edit wiki pages directly (to avoid conflicts).
- **Human curates** — you decide what sources to ingest and what questions to ask.
- Every page uses relative links for cross-references.
- `index.md` and `log.md` are updated on every operation.

See [`AGENTS.md`](../AGENTS.md) for full wiki conventions and workflows.
