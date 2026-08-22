# Governance, Compliance und Metriken

## Governance

- Menschliche Freigabe für produktive Änderungen bleibt Pflicht
- Senior-Entwickler validieren KI-Annahmen und Architekturentscheidungen

## Recht & Compliance

- Keine Secrets oder sensiblen Daten in Prompts
- Copilot/AI-Policies über Organisationseinstellungen zentral steuern
- IP- und Lizenzprüfung in den Reviewprozess integrieren

## KPI-Vorschläge

- Pull-Request Cycle Time
- Deployment-Frequenz
- Test Coverage (Ziel: ≥ 80 %)
- Anzahl der `mypy`-Errors im Haupt-Branch
- Anzahl der `ruff`-Findings (Linting-Schulden)
- Anzahl der CodeQL-Funde (Python, High/Critical)
- Anteil automatisiert validierter KI-Beiträge (grüne CI + Label `ai-generated`)
