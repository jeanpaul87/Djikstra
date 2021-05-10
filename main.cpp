/*
 * Fichier: Main.cpp
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Implementation du main du programme; interface pour le user. 
 * Toutes les fonctions implementees dans Graphe.cpp sont utilisees ici. 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Arc.h"
#include "Vehicule.h"
#include "Graphe.h"
#include "Sommet.h"

int main() {

	Graphe graphe;
	Vehicule* vehicule = new Vehicule();

	int autonomieComplete;
	int autonomieRestante;

	string nomFichier;
	string carte;
	string typeVehicule;
	ifstream fichier;

	bool EXIT = false;
	bool REPONSE_USER = false;
	const int CONVERT_ASCII = 96;

	bool estUnCharactere(const string & choix);
	bool estUnNumero(const string & reponse);
	/*graphe.creerGraphe("graphe1.txt");
	graphe.plusCourtChemin("C", "U", vehicule);*/
	while (!EXIT)
	{
		string choixUser;
		string reponseUser = "";

		do {
			cout<< endl
			    << endl
				<< "Choisissez une option entre a, b, c, d et e: " << endl << endl
				<< "(a) Entrer les caracteristiques du vehicule." << endl
				<< "(b) Mettre a jour la carte." << endl
				<< "(c) Extraire un sous-graphe." << endl
				<< "(d) Determiner le plus court chemin." << endl
				<< "(e) Quitter." << endl << endl
				<< "Choix : ";

			cin >> choixUser;
		} while (!estUnCharactere(choixUser));

		cout << endl;

		char a = choixUser[0];

		int numeroCase = int(a) - CONVERT_ASCII;


		switch (numeroCase)
		{

		case 1:
			do {
				cout << "Entrer le type de plein du vehicule (essence, electrique ou hybride) : ";
				cin >> typeVehicule;

			} while (!(typeVehicule == "hybride" || typeVehicule == "electrique" || typeVehicule == "essence"));

			cout << endl;

			vehicule->setType(typeVehicule);

			do {
				cout << "Veuillez entrer l'autonomie maximale du vehicule en kilometres : ";
				cin >> reponseUser;
			} while (!estUnNumero(reponseUser));

			cout << endl;

			autonomieComplete = stoi(reponseUser);
			vehicule->setAutonomieComplete(autonomieComplete);

			do {
				cout << "Entrez l'autonomie restante du vehicule : ";
				cin >> reponseUser;
			} while (!estUnNumero(reponseUser) || (autonomieComplete < stoi(reponseUser)));

			cout << endl;

			autonomieRestante = stoi(reponseUser);
			vehicule->setAutonomieRestante(autonomieRestante);

			REPONSE_USER = true;

			break;

		case 2:

			do {
				cout << "Entrer le nom complet du fichier txt a lire sans l'extension: ";
				cin >> nomFichier;
				cout << endl;

				nomFichier = nomFichier.append(".txt");

				fichier.open(nomFichier);

				graphe.creerGraphe(nomFichier);
				graphe.lireGraphe();

			} while (!fichier);

			break;

		case 3:

			if (REPONSE_USER)
			{
				string sommetDebut;

				do {

					cout << "Sommet de debut (en majuscule): ";
					cin >> sommetDebut;

				} while (!estUnCharactere(sommetDebut) || !isupper(sommetDebut[0]) );

				Graphe grapheExtrait = graphe.extractionGraphe(vehicule, sommetDebut);

			}
			else
			{
				do {
					cout<< endl
						<< endl
						<< "Choisissez une option entre a, b, c, d et e: " << endl << endl
						<< "(a) Entrer les caracteristiques du vehicule." << endl
						<< "(b) Mettre a jour la carte." << endl
						<< "(c) Extraire un sous-graphe." << endl
						<< "(d) Determiner le plus court chemin." << endl
						<< "(e) Quitter." << endl << endl
						<< "Choix : ";

					cin >> choixUser;
				} while (!estUnCharactere(choixUser));

				cout << endl;

				char a = choixUser[0];

				int numeroCase = int(a) - CONVERT_ASCII;
			}
			break;

		case 4:
			if (REPONSE_USER)
			{
				string debut;

				do {

					cout << "Sommet de debut (en majuscule): ";
					cin >> debut;

				} while (!estUnCharactere(debut) || !isupper(debut[0]));


				string fin;

				do {

					cout << "Sommet de d'arrivee (en majuscule): ";
					cin >> fin;

				} while (!estUnCharactere(fin) || !isupper(fin[0]));

				cout << "Voici le chemin le plus court possible : ";

				Graphe plusCourtChemin = graphe.plusCourtChemin(debut, fin, vehicule);
				
			}else{
				string choixUser;
				string reponseUser = "";

				do {
					cout<< endl
						<< endl
						<< "Choisissez une option entre a, b, c, d et e: " << endl << endl
						<< "(a) Entrer les caracteristiques du vehicule." << endl
						<< "(b) Mettre a jour la carte." << endl
						<< "(c) Extraire un sous-graphe." << endl
						<< "(d) Determiner le plus court chemin." << endl
						<< "(e) Quitter." << endl << endl
						<< "Choix : ";

					cin >> choixUser;
				} while (!estUnCharactere(choixUser));

				cout << endl;

				char a = choixUser[0];

				int numeroCase = int(a) - CONVERT_ASCII;
			}
			break;
		case 5:
			EXIT = true;
			break;

		}
	}

	if (vehicule) { delete vehicule; }
}

bool estUnNumero(const string& reponse) {
	string::const_iterator i = reponse.begin();
	while (i != reponse.end() && isdigit(*i)) ++i;
	if (!reponse.empty() && i == reponse.end())
		return true;
	else {
		cout << endl << "***Choisir une option valide***" << endl << endl;
		return false;
	}
}

bool estUnCharactere(const string& choix) {
	if (choix.length() != 1) {
		cout << endl << "***Choisir une option valide***" << endl << endl;
		return false;
	}
	return true;
}