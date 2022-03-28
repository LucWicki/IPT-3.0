#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const char tab[] = "\t\t\t\t\t";

//Struktur der Karte
//Author: Luc
typedef struct GenshinKarte {
	char name[50]; //Charaktername
	int atk; // Angriffspunkte
	double height; // Energieaufladerate
	struct GenshinKarte* pNext; // Positions-Pointer
}struGenshinKarte;

// Kartenwerte zuweisen
// Author: Luc
struGenshinKarte* CreateCard(const char* pName, int atk, double height)
{
	// Platzreservation, instanzierung einer neuen Karte
	struGenshinKarte* pKarte = (struGenshinKarte*) malloc(sizeof(struGenshinKarte));
	strcpy_s(pKarte->name, pName);
	pKarte->atk = atk;
	pKarte->height = height;
	pKarte->pNext = NULL;
	return pKarte;
}

// Karte Hinzufügen
// Author: Edina & Luc
struGenshinKarte* AddCard(struGenshinKarte* pStart, struGenshinKarte* pNew) {
	// Falls Liste leer, gib neues Element zurück um es als Start zu interpretieren.
	if (pStart == NULL) return pNew;
	// sonst: gehe an das Ende der Liste
	struGenshinKarte* current = pStart;
	while (current->pNext != NULL) current = current->pNext;
	// hängt das neue Element ans Ende an
	current->pNext = pNew;
	// gibt den Start wieder zurück (ändert sich nur beim ersten Aufruf)
	return pStart;
}

// Karte Entfernen und Lücke in der Liste beheben
// Author: Edina & Luc
struGenshinKarte* RemoveCard(struGenshinKarte* pStart, struGenshinKarte* pRemove) {
	// Wenn Liste bereits leer, gib sie leer zurück.
	if (pStart == NULL) {
		return NULL;
	}
	// Wenn gesuchtes Element = pStart, gib das 2. Element zurück und entferne den Start.
	if (pRemove == pStart) {
		// Neuer Start ist 2. Element
		pStart = pStart->pNext;
		//folgendes Element des zu löschenden Elements soll NULL sein.
		pRemove->pNext = NULL;
		return pStart;
	}
	GenshinKarte* pPrev = pStart;
	// Geht durch alle Elemente, speicher vorheriges
	while (pPrev->pNext != pRemove && pPrev->pNext != NULL) pPrev = pPrev->pNext;
	// Element war nicht in der Liste.
	if (pPrev->pNext == NULL) {
		// Gib den Start unverändert zurück.
		return pStart;
	}

	//P Next wird auf das folgende Element gesetzt
	pPrev->pNext = pRemove->pNext;
	pRemove->pNext = NULL;
	return pStart;
}

// Karteninformationen ausgeben
// Author: Edina & Luc
void PrintCard(struGenshinKarte* card) {
	if (card == NULL) return;
	// Ausgabe
	printf("%sName = %s, Angriff = %i, Gr\x94sse = %.2lf m\n", tab, card->name, card->atk, card->height);
}

// Gehe durch eine Liste und gib die Elemente aus
// Author: Edina & Luc
void OutputList(struGenshinKarte* pFirst) {
	for (struGenshinKarte* pOut = pFirst; pOut != NULL; pOut = pOut->pNext) PrintCard(pOut);
}

// Gehe durch eine Liste und zähle die Elemente
// Author: Edina & Luc
int CountCards(struGenshinKarte* pStart) {
	if (pStart == NULL) return 0;
	int count = 0;
	// Gehe über die Liste und erhöhe den Zähler um 1 für jeden Durchgang
	for (GenshinKarte* p = pStart; p != NULL; p = p->pNext) count++;
	return count;
}


//Funktion halbiert eine Liste in zwei zufällig verteilte Hälften.
// Author: Edina & Luc
GenshinKarte* GetCards(GenshinKarte** ppStart) {
	// ppStart wird auf Adresse des Pointer PStart gesetzt
	GenshinKarte* pStart = *ppStart;
	// Zähle die Karten
	int total = CountCards(pStart);
	printf("%sAnzahl Karten Total: %d\n", tab, total);

	// Berechne die Hälfte der Länge der Liste
	int half = total / 2;
	int count = 0;
	// Definiere den Start der Liste des Users
	GenshinKarte* userStart = NULL;
	// Variable für aktuelle Liste
	GenshinKarte* current = pStart;
	// Hinzufügen der Hälfte der Karten
	while (count < half) {
		GenshinKarte* next = current->pNext;
		// kreiert Zufallszahl von 0 - 9.
		int random = rand() % 10;
		// Falls die Züfällige Zahl in der obere Hälfte liegt (über 4)
		if (4 < random) {
			// Entfernt die aktuelle Karte von der ursprünglichen Liste und aktualisiert den Pointer 
			pStart = RemoveCard(pStart, current);
			// Fügt dieselbe Karte der neuen Liste hinzu.
			userStart = AddCard(userStart, current);
			count++;
		}
		// Aktualisiere das aktuelle Element
		current = next;
		// Setzt current wieder an Start, falls es am Ende der Liste ist
		if (current == NULL) {
			current = pStart;
		}
	}
	// Pointer in der Main funktion wird aktuallisiert
	*ppStart = pStart;
	return userStart;
}

//Hauptprogramm
//Author: Edina
int main() {
	time_t t;
	srand((unsigned)time(&t));
	int game = 0;

	//Menü
	do {
		printf("\n");
		printf("%sWILLKOMMEN ZU:\n", tab);
		printf("%sGENSHIN-QUARTETT\n", tab);
		printf("%s_______________\n", tab);
		printf("%sSpiel Starten =\t1\n", tab);
		printf("%sHow to Play =\t2\n", tab);
		printf("%sBeenden =\t3\n", tab);
		scanf_s("%i", &game);

		//Anzeige alle Karten
		if (game == 1) {
			GenshinKarte* pStart = NULL;
			pStart = AddCard(pStart, CreateCard("Eula", 342, 1.72));
			pStart = AddCard(pStart, CreateCard("Beidou", 225, 1.72));
			pStart = AddCard(pStart, CreateCard("Chongyun", 223, 1.62));
			pStart = AddCard(pStart, CreateCard("Ganyu", 335, 1.6));
			pStart = AddCard(pStart, CreateCard("HuTao", 106, 1.56));
			pStart = AddCard(pStart, CreateCard("Kequing", 323, 1.56));
			pStart = AddCard(pStart, CreateCard("Klee", 311, 1.27));
			pStart = AddCard(pStart, CreateCard("Ningguang", 212, 1.8));
			pStart = AddCard(pStart, CreateCard("Yanfei", 240, 1.57));
			pStart = AddCard(pStart, CreateCard("Xiao", 349, 1.6));
			OutputList(pStart);

			//Liste für den Nutzer
			GenshinKarte* pUser = GetCards(&pStart);
			// Gibt den Rest der ursprünglichen Liste and den Computer
			GenshinKarte* pComputer = pStart;

			
			// Solange beide Listen noch Karten haben
			while (pUser != NULL && pComputer != NULL) {
				//Ausgabe der obersten Karte des Users
				GenshinKarte* uKarte = pUser;
				printf("\n");
				printf("%sDeine oberste Karte:\n", tab);
				PrintCard(uKarte);
				// Auswahl vom User
				printf("%sW\x84hle Wert 1 Angriff oder 2 Gr\x94sse.\n", tab);
				int Wert;
				scanf_s("%i", &Wert);
				// Eingabe überprüfen
				while (Wert != 1 && Wert != 2 && Wert != 3) {
					printf("%sBitte gib einen korrekten Wert ein. 1 Angriff / 2 Gr\x94sse\n", tab);
					scanf_s("%i", &Wert);
				}
				// Ende
				if (Wert == 3) {
					game = 3;
					break;
				}
				//Author: Luc
				// Ausgabe der obersten Karte des Computers
				GenshinKarte* cKarte = pComputer;
				printf("%sOberste Karte des Computers:\n", tab);
				PrintCard(cKarte);
				printf("\n");
				// Entfernt die oberste Karte des Nutzers
				pUser = RemoveCard(pUser, uKarte);
				// Entfernt die oberste Karte des Computers
				pComputer = RemoveCard(pComputer, cKarte);
				//User gewonnen oder verloren?
				bool verloren;
				// Überprüfung entscheidender Wert
				if (Wert == 1) {
					// Falls erster Wert gleich, nimmt den zweiten
					if (uKarte->atk == cKarte->atk) {
						verloren = uKarte->height < cKarte->height;
					}
					
					else {
						verloren = uKarte->atk < cKarte->atk;
					}
				}
				else {
					//Falls zweiter Wert gleich, nimm den ersten
					if (uKarte->height == cKarte->height) {
						verloren = uKarte->atk < cKarte->atk;
					}
					else {
						verloren = uKarte->height < cKarte->height;
					}
				}
				printf("\n");
				if (verloren) {
					//Wenn User verliert, wird Karte dem Computer gegeben
					pComputer = AddCard(pComputer, uKarte);
					// Karte des Computers wird unten in den Stapel gelegt
					pComputer = AddCard(pComputer, cKarte);
					// Ausgabe
					printf("%sKarte verloren!\n", tab);
				}
				else {
					// Wenn user gewinnt, wird Karte vom Computer dem User gegeben
					pUser = AddCard(pUser, cKarte);
					//Karte wird unten in den Stapel gelegt
					pUser = AddCard(pUser, uKarte);
					printf("%sKarte gewonnen!\n", tab);
				}
				//Author: Edina
				// Ausgabe anzahl Karten
				printf("%sVerbleibende Karten von dir: %d\n", tab, CountCards(pUser));
				printf("%sVerbleibende Karten Computer: %d\n", tab, CountCards(pComputer));
			}
			// Ausgabe Spielstand
			if (pUser == NULL) printf("%sGAME OVER! :(\n", tab);
			else printf("%sGl\x81""ckwunsch. Du hast gewonnen! :)\n", tab);
			system("pause");
			continue;
		}
		//Spielerklärung
		else if (game == 2)
		{
			printf("%sBeim Quartett gegen den Computer wird dir die oberste Karte angezeigt.\n", tab);
			printf("\n");
			printf("%sDanach kannst du ausw\x84hlen, welche Werte du mit der Karte des Computers\n", tab);
			printf("%svergleichen m\x94""chtest.\n", tab);
			printf("\n");
			printf("%sDer Spieler mit dem h\x94heren Wert, erh\x84lt die Karte des Verlierers\n", tab);
			printf("\n");
			printf("%sDie Karte des Verlieres wird zuerst unter den Stapel des Gewinners gelegt.\n", tab);
			printf("%sDann folgt die Karte des Gewinners.\n", tab);
			printf("\n");
			printf("%sDas Spiel ist zu Ende, wenn jemandem keine Karten mehr bleiben.\n", tab);
			printf("\n");
			system("pause");
			continue;
		}
		//Ende
		else if (game == 3) {
			break;
		}
		//ungültige Eingabe
		else {
			printf("%sBis 3 Z\x84hlen ist schwierig.\n", tab);
			system("pause");
			continue;
		}
	} while (game != 3);
	return 0;
}