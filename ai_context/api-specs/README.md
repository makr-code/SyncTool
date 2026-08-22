# API Specs

Hier liegen versionierte OpenAPI-Spezifikationen für alle FastAPI-Endpoints und Integrationsgrenzen.

## Konventionen

- Dateien im Format `vN-<service>.yaml` (z. B. `v1-respo-api.yaml`)
- OpenAPI 3.1.0 als Standard
- Alle Schemas werden mit Pydantic generiert (`app.openapi()`) und hier eingecheckt
- Änderungen an Schemas erfordern eine neue Versionsdatei (kein In-Place-Überschreiben)

## Bestehende Specs

| Datei | Version | Beschreibung |
|-------|---------|--------------|
| [openapi-template.yaml](openapi-template.yaml) | — | Minimales FastAPI OpenAPI-Template |
