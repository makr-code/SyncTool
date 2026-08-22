# AI Context

Dieser Ordner enthält **langlebigen, architektonischen Kontext** für KI-Agenten — gemeinsam von Mensch und KI gepflegt.

## Inhalt

- `adr/` — Architecture Decision Records (warum wurde was entschieden?)
- `api-specs/` — OpenAPI-Spezifikationen für FastAPI-Endpoints
- `memory-management-policy.md` — Python Ressourcen-Management (Context Manager)
- `prompt-engineering-guidelines.md` — Prompting-Tipps für Python
- `governance-and-metrics.md` — Governance, Compliance und KPI-Tracking

## Abgrenzung zu anderen Verzeichnissen

| Verzeichnis | Zweck | Autor |
|-------------|-------|-------|
| `ai_context/` | Architektur-Richtlinien, ADRs, API-Specs | Mensch + LLM |
| `wiki/` | Persistente Wissensbasis (Domain Knowledge, Source-Summaries) | LLM (Mensch liest) |
| `raw/` | Unveränderliche Quell-Dokumente | Mensch (LLM liest) |
| `ai_working/` | Kurzlebige Arbeits-Artefakte (nicht committed) | LLM |

Siehe [`AGENTS.md`](../AGENTS.md) für den vollständigen Agent-Schema und die Wiki-Workflows.
