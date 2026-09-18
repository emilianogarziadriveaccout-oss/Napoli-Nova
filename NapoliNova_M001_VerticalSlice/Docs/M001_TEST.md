# M001 — Play Test

Stato iniziale atteso:
- Money 500
- Followers 100
- Viral 0
- Reputation 0
- Attention 0
- XP 0

Test:
1. Play.
2. Entra nel Mission Trigger.
3. Verifica "Raggiungi il parcheggio."
4. Entra nel Parking Area.
5. Verifica "Individua il veicolo..."
6. Apri smartphone con M.
7. Inquadra BP_Event_M001_IllegalParking.
8. Verifica TARGET TROVATO.
9. Premi SPACE.
10. Mantieni il target nell'inquadratura per almeno 3 secondi.
11. Verifica VIDEO VALIDO.
12. Verifica reazione dell'owner.
13. Premi ENTER.
14. Verifica pubblicazione.
15. Verifica:
   - +100 €
   - +250 XP
   - +1 Reputation
   - +10 Attention
   - follower/viralità aggiornati
16. Verifica M001 completata.
17. Verifica M002 sbloccata.
18. Verifica autosave.
19. Ricarica.
20. Verifica persistenza dello stato.

Test negativi:
- Entrare nel parcheggio prima di M001 non deve avanzare la missione.
- Inquadrare un NPC non deve acquisire il target.
- Inquadrare un'altra auto non deve acquisire il target.
- Registrare meno di 3 secondi non deve rendere il video valido.
- Perdere il target durante REC deve fermare l'accumulo del tempo utile.
- Pubblicare senza video valido non deve dare ricompense.
- Completare M001 due volte non deve dare una seconda ricompensa.
