# AI Working Area

Temporärer Arbeitsbereich für agentische Zwischenartefakte. Dateien hier sind **nicht** als langfristige Dokumentation gedacht und werden standardmäßig nicht committed (`.gitignore`-Einträge vorhanden).

## Unterordner

| Ordner | Zweck |
|--------|-------|
| `plans/` | Agent-Arbeitspläne, Checklisten, Aufgabenzerlegungen |
| `debug/` | Stack Traces, Reproduktions-Skripte, Fehleranalysen |
| `notes/` | Kurzzeit-Entscheidungsnotizen, Zwischenergebnisse |

## Konventionen

- Dateinamen mit Datum-Präfix: `2026-08-01-refactoring-plan.md`
- Erledigte Artefakte löschen oder in `ai_context/` überführen, wenn sie langfristigen Wert haben
- Keine Secrets oder sensiblen Daten in diesen Dateien ablegen
