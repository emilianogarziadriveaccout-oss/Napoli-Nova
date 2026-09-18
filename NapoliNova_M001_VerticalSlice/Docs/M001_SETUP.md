# M001 — Setup Blueprint

## Asset
Crea:
- BP_M001_MissionTrigger
- BP_M001_ParkingArea
- BP_Event_M001_IllegalParking
- BP_NPC_M001_Owner
- WBP_HUD
- WBP_MissionPanel
- WBP_Phone
- WBP_MissionComplete

## Target
BP_Event_M001_IllegalParking:
- Actor Tag: M001_Target
- Visibility collision: Block
- posizionalo nell'area parcheggio

## Parking Area
BP_M001_ParkingArea:
- Box Collision
- Query Only
- Generate Overlap Events
- BeginOverlap -> Cast NovaPlayerCharacter -> Get NovaMissionSubsystem
  -> AdvanceObjective(ReachParking)

## Mission trigger
BP_M001_MissionTrigger:
- MissionID = M001
- BeginOverlap -> StartMission(M001)

## HUD
Aggiungi WBP_HUD al viewport del player.
WBP_HUD contiene:
- Followers
- ViralPoints
- Reputation
- Money
- Attention
- WBP_MissionPanel
- WBP_Phone
- WBP_MissionComplete

## Phone
M apre/chiude il telefono.
SPACE avvia/arresta REC.
ENTER pubblica un video valido.

Il telefono considera valido il target se:
- è entro 800 cm
- è colpito dal Line Trace Visibility
- ha il tag M001_Target
- la registrazione utile raggiunge 3 secondi

## Owner
BP_NPC_M001_Owner:
- AI Controller = NovaAIController
- Auto Possess AI = Placed in World or Spawned
- reagisce al delegate OnPlayerRecording
- raggiunge il player e avvia il dialogo.

Dialogo:
Proprietario: "Ma che stai facendo?"
Franco: "Sto documentando il parcheggio."
Proprietario: "È solo per un minuto."
Franco: "È quello che dicono tutti."
