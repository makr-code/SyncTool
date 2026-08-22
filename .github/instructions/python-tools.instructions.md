# Python Tools Instructions

## Tooling Priorität

1. Nutze Python Language Server (Pylance/Pyright) und Typ-Informationen zuerst
2. Nutze `grep`/Textsuche nur als Fallback

## Codierstandards (Python 3.10+)

- **Typing** ist verpflichtend: vollständige Type Hints für alle öffentlichen APIs
- Verwende `type | None` statt `Optional[type]`
- `Protocol` für strukturelles Subtyping; `TypeVar`/`Generic` für generische Klassen
- `pydantic.BaseModel` an API-Grenzen, `dataclass` für interne Strukturen
- `async/await` für alle I/O-Operationen; Timeouts immer explizit setzen
- Context Manager (`with`/`async with`) für alle Ressourcen

## Qualitätsgrenzen

- `ruff check` und `ruff format --check` müssen sauber durchlaufen
- `mypy` darf keine neuen Errors einführen
- Keine `Any`-Typen ohne Kommentar-Begründung
- Keine Mutable Default-Argumente
- Lesbarkeit und Wartbarkeit haben Vorrang vor Mikro-Optimierungen
