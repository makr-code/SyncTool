# Ressourcen-Management Policy (Python)

## Ziele

- Ressourcenlecks (Datei-Handles, DB-Verbindungen, Netzwerk-Sockets) vermeiden
- Lebensdauer und Ownership von Ressourcen explizit dokumentieren
- Kontextmanager als Standard durchsetzen

## Regeln

1. **Context Manager** (`with`-Statement) für alle I/O-Ressourcen verwenden — Dateien, Netzwerkverbindungen, Locks, DB-Sessions.
2. Eigene Ressourcen-Klassen als Context Manager implementieren (`__enter__`/`__exit__` oder `contextlib.contextmanager`).
3. **Generators** für lazy Datenströme verwenden, um Speicherverbrauch zu minimieren.
4. `weakref.ref` oder `weakref.WeakValueDictionary` für Caches nutzen, um zirkuläre Referenzen und Memory-Leaks zu vermeiden.
5. Asynchrone Ressourcen über `async with` und `asynccontextmanager` absichern.
6. Keine globalen Mutable-State-Objekte ohne explizite Lebensdauer-Dokumentation.
7. Jede API-Funktion dokumentiert, wer für das Schließen einer zurückgegebenen Ressource verantwortlich ist.

## Beispiele

```python
# Gut: Context Manager
with open("data.json") as f:
    data = json.load(f)

# Gut: eigener Context Manager
from contextlib import asynccontextmanager

@asynccontextmanager
async def db_session(pool: ConnectionPool):
    async with pool.acquire() as conn:
        yield conn

# Gut: Generator für Lazy-Loading
def stream_chunks(path: Path) -> Generator[str, None, None]:
    with open(path) as f:
        for line in f:
            yield line.strip()

# Vermeiden: Ressource ohne explizites Schließen
f = open("data.json")   # Nicht so!
data = json.load(f)
```
