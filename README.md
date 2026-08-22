# RESPO - RAG-Enhanced Software Programming Optimizer

[![Status](https://img.shields.io/badge/status-development-yellow)](.)
[![Python](https://img.shields.io/badge/python-3.10+-blue)](.)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![python-quality](https://github.com/makr-code/RespoTemplate-Python/actions/workflows/python-quality.yml/badge.svg)](https://github.com/makr-code/RespoTemplate-Python/actions/workflows/python-quality.yml)
[![CodeQL](https://github.com/makr-code/RespoTemplate-Python/actions/workflows/codeql-python.yml/badge.svg)](https://github.com/makr-code/RespoTemplate-Python/actions/workflows/codeql-python.yml)

## 🎯 Übersicht

RESPO ist ein **eigenständiges, on-premise RAG LLM Programmierhilfe-System**:

- **Unabhängig** - Keine Abhängigkeit von spezifischen Datenbanken
- **Pluggable Vector Stores** - ChromaDB, Qdrant, Weaviate, ThemisDB, etc.
- **vLLM** - Hochperformante LLM-Inferenz mit LoRA Support
- **Ohne Vendor-Login** - Vollständig lokale Ausführung
- **Air-Gapped Deployment** - Läuft komplett offline

## 🏗️ Architektur

```
┌─────────────────────────────────────────────────────────────────┐
│                        RESPO API (FastAPI)                       │
├─────────────────────────────────────────────────────────────────┤
│  /chat  │  /complete  │  /explain  │  /review  │  /search      │
└─────────────────────────────────────────────────────────────────┘
                              │
          ┌───────────────────┼───────────────────┐
          ▼                   ▼                   ▼
   ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
   │ RAG Pipeline│     │ vLLM Engine │     │Vector Store │
   │             │     │             │     │ (Pluggable) │
   │ - Retrieval │     │ - Inference │     │             │
   │ - Reranking │     │ - LoRA      │     │ - ChromaDB  │
   │ - Context   │     │ - Streaming │     │ - Qdrant    │
   └─────────────┘     └─────────────┘     │ - Weaviate  │
                                           │ - ThemisDB  │
                                           └─────────────┘
```

## 🚀 Quick Start

### Installation

```bash
# Clone the repository
git clone https://github.com/makr-code/respo.git
cd respo

# Install dependencies
pip install -e .

# Or with optional vector stores
pip install -e ".[qdrant]"    # With Qdrant
pip install -e ".[all]"       # All optional dependencies

# Copy configuration
cp .env.example .env
# Edit .env with your settings

# Start RESPO API
respo server --port 8080
```

### Mit Docker Compose

```bash
cd docker
docker compose up -d
```

## 📡 API Endpoints

| Endpoint | Methode | Beschreibung |
|----------|---------|--------------|
| `/chat` | POST | Interaktiver Chat mit Code-Kontext |
| `/complete` | POST | Code Completion |
| `/explain` | POST | Code Explanation |
| `/review` | POST | Code Review |
| `/search` | POST | Semantic Code Search |
| `/ingest` | POST | Code Repository Indexing |

### Beispiel: Chat

```bash
curl -X POST http://localhost:8080/chat \
  -H "Content-Type: application/json" \
  -d '{
    "message": "Wie implementiere ich einen LRU Cache in Python?",
    "context": {
      "repo": "my-project",
      "language": "python"
    }
  }'
```

## 🔍 GitHub Scraper

RESPO enthält einen leistungsfähigen GitHub Scraper zum Sammeln von Trainingsdaten.

### CLI Befehle

```bash
# Repository scrapen
respo scrape owner/repo -o ./output

# Mit GitHub Token (höhere Rate Limits)
respo scrape owner/repo -t $GITHUB_TOKEN -o ./output

# Repository suchen
respo search "machine learning" --language python --min-stars 1000

# Batch-Scraping aus Datei
respo batch-scrape repos.txt -o ./data -j metadata.json
```

### Beispiele

```bash
# Python-Repositories scrapen
respo scrape python/cpython -o ./python-src -e py

# Top TypeScript Repos finden
respo search "typescript framework" -l typescript -s 5000 -n 50

# Batch-Scraping
cat > repos.txt << EOF
facebook/react
microsoft/TypeScript
rust-lang/rust
EOF
respo batch-scrape repos.txt -o ./training-data -j metadata.json
```

## 📁 Projektstruktur

```
respo/
├── respo/                  # Python Package
│   ├── api/                # FastAPI Endpoints
│   ├── rag/                # RAG Pipeline
│   ├── embedding/          # Embedding Service
│   ├── ingestion/          # Code Ingestion + GitHub Scraper
│   ├── llm/                # vLLM Integration
│   ├── vectorstore/        # Pluggable Vector Stores
│   │   ├── base.py         # Abstract Interface
│   │   ├── chroma.py       # ChromaDB (default)
│   │   ├── qdrant.py       # Qdrant
│   │   ├── weaviate.py     # Weaviate
│   │   └── themis.py       # ThemisDB
│   ├── graph/              # Code Graph Analysis
│   └── utils/              # Utilities
├── training/               # LoRA Training
├── tests/                  # Tests
├── docker/                 # Docker Configs
└── docs/                   # Dokumentation
```

## 🔧 Konfiguration

### Umgebungsvariablen

```bash
# Vector Store (choose one)
VECTOR_STORE=chroma                    # chroma, qdrant, weaviate, themis
CHROMA_PERSIST_DIR=./data/chroma
# QDRANT_URL=http://localhost:6333
# WEAVIATE_URL=http://localhost:8080
# Für ThemisDB aus https://github.com/makr-code/themisdb
# THEMIS_URL=http://localhost:8765
# THEMIS_AUTH_TOKEN=

# vLLM
VLLM_URL=http://localhost:8000
VLLM_MODEL=codellama/CodeLlama-13b-Instruct-hf

# Embedding
EMBEDDING_MODEL=microsoft/codebert-base

# Logging
LOG_LEVEL=INFO
```

## 🧪 LoRA Training

```bash
cd training
python train_lora.py --config configs/python.yaml
```

Siehe [training/README.md](training/README.md) für Details.

## 📊 Performance

| Operation | Latenz | Anmerkung |
|-----------|--------|-----------|
| Vector Search | 5-20 ms | ChromaDB/Qdrant |
| Reranking | 100-200 ms | CPU |
| LLM First Token | 500-1000 ms | A100 |
| LLM Total (500 Token) | 3-8 s | A100 |

## 🔒 Security

- ✅ **On-Premise** - Keine Cloud-Abhängigkeiten
- ✅ **Kein Vendor-Login** - Vollständig lokal
- ✅ **DSGVO-konform** - Alle Daten bleiben lokal
- ✅ **Air-Gapped Deployment** - Läuft komplett offline
- ✅ **Unabhängig** - Kein Lock-in zu spezifischen Backends

## 🔌 Vector Store Backends

RESPO unterstützt verschiedene Vector Store Backends:

| Backend | Status | Beschreibung |
|---------|--------|--------------|
| ChromaDB | ✅ Default | Lokale Embedded-Datenbank |
| Qdrant | ✅ Supported | Hochperformante Vector-DB |
| ThemisDB | ✅ Supported | Multi-Model DB mit Graph & Hybrid Search |
| Weaviate | 🔧 Planned | GraphQL-basierte Vector-DB |

## 🔗 ThemisDB Integration

Bei Verwendung von ThemisDB als Backend werden zusätzliche Features freigeschaltet:

Referenz-Implementierung: **https://github.com/makr-code/themisdb**

### Graph-basierte Code-Analyse

```python
from respo.ingestion import IngestionPipeline

# Ingestion mit Graph-Extraktion
pipeline = IngestionPipeline(
    vector_store=themis_store,
    embedder=embedder,
)

# Repository indexieren - Graph wird automatisch aufgebaut
await pipeline.ingest_github_repo("owner", "repo")

# Dependency-Analyse
deps = await pipeline.analyze_dependencies("module.function_name")
print(f"Dependencies: {deps['dependencies']}")
print(f"Used by: {deps['usages']}")

# Call Graph abrufen
call_graph = await pipeline.get_call_graph("main.process_data", depth=3)
```

### Hybrid Search mit Graph Expansion

```python
from respo.vectorstore.themis import ThemisVectorStore

store = ThemisVectorStore()

# Standard Vector Search
results = await store.search(query_embedding, k=10)

# Hybrid Search: Vector + Keyword + Graph
results = await store.hybrid_search(
    query_embedding=embedding,
    query_text="database connection",
    k=10,
    expand_graph=True,  # Findet auch verwandte Code-Entitäten
    graph_depth=2,
)

# Graph Traversal
callees = await store.graph_traverse(
    start_id="utils.db.connect",
    edge_types=["calls"],
    direction="outgoing",
    depth=3,
)
```

### Extrahierte Beziehungen

| Beziehungstyp | Beschreibung |
|---------------|--------------|
| `imports` | Modul-Import-Beziehungen |
| `calls` | Funktionsaufrufe |
| `inherits` | Klassen-Vererbung |
| `implements` | Interface-Implementierung |
| `uses` | Variablen-/Typen-Nutzung |
| `contains` | Modul/Klasse enthält Funktion |
| `defines` | Klasse definiert Methode |

## 🤖 AI Vibe Coding Setup

Dieses Repository ist als **AI Vibe Coding Template** für Python eingerichtet. Alle KI-Agenten-Konventionen, Copilot-Richtlinien und CI-Anforderungen sind vollständig dokumentiert.

### Verzeichnisstruktur für KI-Agenten

```
AGENTS.md                          # LLM Agent Schema (Wiki-Konventionen + Workflows)

.github/
├── copilot-instructions.md        # Copilot: Python-Kodierstandards + Toolchain
├── instructions/
│   ├── python-tools.instructions.md   # Python Language Server, ruff, mypy
│   └── ci-logic.instructions.md       # CI-Pflichtprüfungen für PRs
└── workflows/
    ├── python-quality.yml         # lint (ruff) + typecheck (mypy) + tests (pytest)
    ├── codeql-python.yml          # CodeQL Security Scan (Python)
    └── label-ai-generated.yml     # Labeling von KI-generierten PRs

raw/                               # Unveränderliche Quell-Dokumente (LLM liest, Mensch schreibt)

wiki/                              # LLM-gepflegte persistente Wissensbasis
├── index.md                       # Inhaltsverzeichnis aller Wiki-Seiten
├── log.md                         # Append-only Operationslog
└── sources/                       # Eine Summary-Seite pro Quell-Dokument

ai_context/                        # Architektonischer Langzeit-Kontext (Mensch + LLM)
├── adr/                           # Architecture Decision Records
│   └── 001-python-async-strategy.md
├── api-specs/                     # OpenAPI-Spezifikationen (FastAPI)
├── memory-management-policy.md   # Python Ressourcen-Management (Context Manager)
├── prompt-engineering-guidelines.md  # Prompting-Tipps für Python
└── governance-and-metrics.md     # Governance + KPIs

ai_working/                        # Temporäre Agenten-Artefakte (nicht committen)
├── plans/                         # Arbeitspläne, Checklisten
├── debug/                         # Stack Traces, Reproduktions-Skripte
└── notes/                         # Kurzzeit-Entscheidungsnotizen
```

### LLM Wiki (Karpathy-Pattern)

Das Repository folgt dem [LLM Wiki-Pattern](https://gist.github.com/karpathy/442a6bf555914893e9891c11519de94f): statt RAG-Retrieval aus Roh-Dokumenten bei jeder Anfrage baut und pflegt der LLM-Agent eine **persistente, wachsende Wissensbasis**.

| Schicht | Verzeichnis | Autor | Beschreibung |
|---------|-------------|-------|--------------|
| Raw Sources | `raw/` | Mensch | Unveränderliche Quell-Dokumente |
| Wiki | `wiki/` | LLM | Persistente, verlinkte Markdown-Seiten |
| Schema | `AGENTS.md` | Mensch + LLM | Konventionen und Workflows für den Agenten |

**Grundprinzip:** Der Mensch kuratiert Quellen und stellt Fragen. Der LLM liest, fasst zusammen, pflegt Cross-References, aktualisiert das Wiki — und das Wissen akkumuliert sich statt bei jeder Anfrage neu abgeleitet zu werden.

**Workflow:**
```bash
# Neue Quelle einpflegen
# → "Ingest raw/articles/mein-artikel.md"

# Wissensbasis abfragen
# → "Wie funktioniert das Reranking im RAG-Pipeline?"

# Wiki aufräumen
# → "Lint the wiki — check for contradictions and orphan pages"
```

### ai_context/ vs. wiki/ vs. ai_working/

| | `ai_context/` | `wiki/` | `ai_working/` |
|---|---|---|---|
| **Lebensdauer** | Dauerhaft | Dauerhaft, wachsend | Temporär (.gitignore) |
| **Autor** | Mensch + LLM | LLM (Mensch liest) | LLM |
| **Inhalt** | ADRs, API-Specs, Richtlinien | Domain-Wissen, Source-Summaries | Pläne, Debug-Traces, Notizen |

### ADR-Prozess

Architekturentscheidungen werden als ADR in `ai_context/adr/` dokumentiert. Siehe [`ai_context/adr/README.md`](ai_context/adr/README.md) für das Template und die Übersicht.

### CI-Anforderungen für PRs

Jeder PR muss folgende Checks bestehen:

1. **`ruff check`** — keine Linting-Findings
2. **`ruff format --check`** — korrekte Formatierung
3. **`mypy`** — keine neuen Type Errors
4. **`pytest --cov`** — alle Tests grün, Coverage ≥ 80 %
5. **CodeQL** — keine High/Critical Security Findings

KI-generierte PRs werden automatisch mit dem Label `ai-generated` versehen.

---



## 🛠️ Development

```bash
# Tests ausführen
pytest tests/

# Linting
ruff check respo/

# Type Checking
mypy respo/

# Formatierung
ruff format respo/
```

## 📄 Lizenz

MIT License

---

**Status:** Development  
**Version:** 0.1.0  
**Maintainer:** RESPO Team
