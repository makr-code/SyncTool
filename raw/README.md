# Raw Sources

This directory contains **immutable source documents** — the input layer of the LLM Wiki.

## Rules

- **Never modify** files in this directory once added. They are source-of-truth.
- The LLM reads from here but never writes here.
- You (the human) add sources; the LLM ingests them into `wiki/`.

## Supported formats

- Markdown (`.md`) — clipped articles, notes, documentation
- Plain text (`.txt`) — transcripts, logs
- PDF (`.pdf`) — papers, reports (LLM reads via tool or prior conversion)
- YAML / JSON (`.yaml`, `.json`) — structured data, configs

## Workflow

1. Drop a new source file into `raw/` (or a subdirectory for organization).
2. Tell the LLM: _"Ingest `raw/<filename>`"_
3. The LLM follows the ingest workflow defined in [`AGENTS.md`](../AGENTS.md).

## Organization (optional)

```
raw/
├── papers/       ← academic papers
├── articles/     ← web articles, blog posts
├── docs/         ← documentation, specs
├── transcripts/  ← meeting notes, podcast transcripts
└── assets/       ← images referenced by source files
```
