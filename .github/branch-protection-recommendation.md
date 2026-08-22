# Branch Protection Empfehlung

Diese Einstellungen sollten in den Repository-Einstellungen aktiviert werden:

- Require status checks before merging:
  - `format-check`
  - `clang-tidy`
  - `asan-tests`
  - `Analyze (C++)`
- Require at least one approving review
- Dismiss stale approvals when new commits are pushed
