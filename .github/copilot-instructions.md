# Copilot Instructions (Python)

## Sprache & Analyse

- Verwende bei Symbolsuche und Referenzanalyse zuerst Python-Sprachwerkzeuge (Pylance/Pyright), nicht reine Textsuche.
- Berücksichtige aktive `pyproject.toml`-Konfiguration (ruff, mypy, pytest).

## Modern Python (3.10+)

- **Typing** ist verpflichtend: Alle öffentlichen Funktionen und Methoden erhalten vollständige Type Hints.
  - Verwende `type | None` (Union-Syntax ab 3.10) statt `Optional[type]`.
  - Nutze `TypeVar`, `Generic` und `Protocol` für generische APIs.
  - Nutze `TypedDict` und `dataclass` für strukturierte Daten; bevorzuge `pydantic.BaseModel` an API-Grenzen.
- **Async/Await**: Alle I/O-Operationen (HTTP, DB, Dateisystem) asynchron implementieren.
  - Exception-Handling explizit: kein nacktes `except Exception`.
  - Timeouts immer setzen (`asyncio.wait_for` oder `httpx`-Timeout).
- **Ressourcen**: Context Manager (`with`/`async with`) für alle I/O-Ressourcen.
- **Validierung**: `pydantic.BaseModel` für alle externen Eingaben (API, Config, Umgebungsvariablen).
- **Konfiguration**: `pydantic-settings` mit `.env`-Fallback, keine `os.environ.get` im Applikationscode.

## Toolchain

- **Linting/Formatting**: `ruff check` + `ruff format` (kein separates `flake8`/`isort`).
- **Type Checking**: `mypy --strict` (neue Dateien), mindestens `mypy` ohne `--ignore-missing-imports` für Kernmodule.
- **Testing**: `pytest` + `pytest-asyncio` (asyncio_mode = "auto"), Coverage ≥ 80 %.
- **Keine `print()`** im Produktionscode — stattdessen `structlog` oder `logging`.

## Architekturprinzipien

- Dependency Injection statt globaler Singletons.
- Vermeide unnötige Abstraktionen: YAGNI vor Over-Engineering.
- Schreibe Code, der testbar und mockbar bleibt (Interfaces über `Protocol`, kein direktes `import` von Infrastruktur in Domänenlogik).

## Bevorzugt

- Kleine, fokussierte Funktionen mit klaren Ein- und Ausgaben.
- `dataclass` oder `pydantic.BaseModel` statt roher `dict`-Rückgaben.
- Fehlerbehandlung mit spezifischen Exception-Typen (eigene Exceptions von `Exception` ableiten).

## Vermeiden

- Mutable Default-Argumente (`def f(x=[]):`).
- Versteckte globale Zustände und Singleton-Imports mit Seiteneffekten.
- `Any`-Typen ohne Kommentar-Begründung.
- Komplexität ohne klaren Wartungsnutzen.
