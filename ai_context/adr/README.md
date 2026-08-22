# Architecture Decision Records (ADR)

Lege pro Architekturentscheidung eine Datei im Format `NNN-kurztitel.md` an.

## ADR-Template

```markdown
# NNN – Titel der Entscheidung

**Status:** proposed | accepted | deprecated | superseded by [NNN](NNN-...)

## Kontext

Warum musste diese Entscheidung getroffen werden? Welches Problem oder welche Anforderung liegt vor?

## Entscheidung

Was wurde entschieden? (konkret und knapp)

## Konsequenzen

### Positiv
- …

### Negativ / Trade-offs
- …
```

## Bestehende ADRs

| Nr. | Titel | Status |
|-----|-------|--------|
| [001](001-python-async-strategy.md) | Python Async-Strategie (asyncio + FastAPI) | accepted |
