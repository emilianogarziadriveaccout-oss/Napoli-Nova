# Napoli Nova — M001 Vertical Slice

Pacchetto di test per Unreal Engine 5.
Contiene lo scheletro C++ e le istruzioni per assemblare il Vertical Slice M001.

IMPORTANTE
- Questo pacchetto non contiene asset binari `.uasset`/`.umap` creati dall'editor.
- I Blueprint indicati nelle istruzioni vanno creati nell'Editor UE5.
- Il codice è organizzato per essere integrato in un progetto C++ esistente chiamato NapoliNova.
- Prima del test verifica la versione UE5 e gli eventuali cambi API.

Ordine:
1. Copia Source/NapoliNova nel progetto.
2. Aggiungi/aggiorna i file di build.
3. Compila Development Editor.
4. Crea i Blueprint indicati in Docs/M001_SETUP.md.
5. Crea la mappa greybox.
6. Esegui il test end-to-end descritto in Docs/M001_TEST.md.
