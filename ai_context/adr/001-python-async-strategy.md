# 001 – Python Async-Strategie: asyncio + FastAPI

**Status:** accepted

## Kontext

Das Projekt ist ein on-premise RAG-System mit mehreren I/O-intensiven Operationen:
- HTTP-Anfragen an vLLM und Embedding-Dienste
- Zugriffe auf Vector Stores (ChromaDB, Qdrant, etc.)
- GitHub-Scraper mit parallelen Repository-Anfragen

Die Wahl zwischen synchronem und asynchronem Python-Code hat weitreichende Auswirkungen auf Durchsatz, Latenz und die Komplexität des Codes.

## Entscheidung

Alle I/O-Operationen werden mit `asyncio` implementiert. Als Web-Framework wird **FastAPI** eingesetzt, das nativ auf `asyncio` aufbaut und automatische OpenAPI-Dokumentation sowie Pydantic-Integration bietet.

- Alle API-Endpoints sind `async def`-Funktionen.
- HTTP-Clients verwenden `httpx.AsyncClient` (nicht `requests`).
- Datenbankzugriffe nutzen asynchrone Clients (z. B. `qdrant-client` async API).
- Für CPU-intensive Operationen (Embedding, Reranking) wird `asyncio.run_in_executor` mit einem `ThreadPoolExecutor` verwendet.
- `pytest-asyncio` (asyncio_mode = "auto") für alle asynchronen Tests.

## Konsequenzen

### Positiv
- Hoher Durchsatz bei vielen parallelen I/O-Operationen ohne Thread-Overhead.
- FastAPI bietet automatische OpenAPI/Swagger-Dokumentation.
- Einheitlicher Code-Stil ohne Mix aus sync/async.
- Pydantic-Integration für Request/Response-Validierung out-of-the-box.

### Negativ / Trade-offs
- Synchrone Bibliotheken müssen in `run_in_executor` gekapselt werden.
- Debugging von async-Code erfordert mehr Erfahrung.
- `asyncio`-Event-Loop darf nicht blockiert werden — alle Entwickler müssen dieses Prinzip kennen.
