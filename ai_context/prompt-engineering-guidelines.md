# Prompt Engineering Guidelines

## Task-Dekomposition

- Komplexe Aufgaben in atomare Teilschritte aufteilen
- Pro Schritt klare Akzeptanzkriterien formulieren
- Explizite Testfälle je Schritt angeben

## Iteration

- Frühzeitig mit Follow-up-Prompts korrigieren
- Nach jedem größeren Schritt Checkpoint definieren
- Bei fehlgeschlagenem Refactoring auf letzten Checkpoint zurücksetzen

## Python-spezifische Tipps

### Type Hints immer vollständig angeben
Formuliere deine Prompts so: _„Schreibe eine Funktion mit vollständigen Type Hints (Python 3.10+). Verwende `type | None` statt `Optional`."_

### pytest-Marker explizit nennen
Bei asynchronen Tests: _„Schreibe einen `pytest.mark.asyncio`-Test (asyncio_mode = auto) für …"_  
Oder kürzer, da `asyncio_mode = "auto"` aktiv ist: _„Schreibe einen async pytest-Test für …"_

### Pydantic-Modelle einfordern
_„Definiere ein `pydantic.BaseModel` für das Request-Schema mit Validierung für …"_

### Kontext mitgeben
- Nenne das relevante Modul/die relevante Datei: _„In `respo/api/routes.py` …"_
- Gib den erwarteten Input-/Output-Typ an: _„Die Funktion erhält `list[str]` und gibt `AsyncIterator[str]` zurück."_

### Fehlerbehandlung einfordern
_„Behandle `httpx.TimeoutException` explizit und wirf eine eigene `ServiceUnavailableError`-Exception."_

### Keine `print()`-Statements
_„Verwende `structlog.get_logger()` statt `print()` für alle Log-Ausgaben."_
