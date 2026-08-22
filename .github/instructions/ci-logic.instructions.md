# CI Logic Instructions

## Pflichtprüfungen für Python-Änderungen

- `ruff check` muss sauber laufen (keine neuen Findings)
- `ruff format --check` muss sauber laufen (Code korrekt formatiert)
- `mypy` darf keine neuen Errors einführen
- `pytest --cov` muss grün sein; Coverage ≥ 80 %
- CodeQL (Python) muss ohne offene High/Critical Findings durchlaufen

## PR-Verhalten

- KI-generierte PRs mit Label `ai-generated` kennzeichnen
- Ohne grüne CI und menschliche Freigabe kein Merge
