/*
 * Fichier: Graphe.cpp
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Implementation de la classe Graphe.
 */

#include "Graphe.h"

#include <fstream>
#include <algorithm>
#include <map>
#include <utility>
#include <sstream>

using namespace std;

Graphe::Graphe() {}

Graphe::Graphe(const Graphe& graphe) {
	for (int i = 0; i < graphe.tableauSommets_.size(); i++)
		tableauSommets_.push_back(new Sommet(*(graphe.tableauSommets_[i])));

	for (int i = 0; i < graphe.tableauArcs_.size(); i++)
		tableauArcs_.push_back(new Arc(*(graphe.tableauArcs_[i])));
}

Graphe::~Graphe() {
	tableauArcs_.clear();
	tableauSommets_.clear();
}

void Graphe::creerGraphe(const string& nomFichier) {

	ifstream fichier(nomFichier);
	if (fichier) {
		tableauArcs_.clear();
		tableauSommets_.clear();

		bool lectureReussie = true;

		string ligne, valeur1, valeur2, valeur3;

		getline(fichier, ligne);
		istringstream stream(ligne);

		while (true) {
			getline(stream, valeur1, ',');
			getline(stream, valeur2, ';');
			if (stream.eof()) break;

			tableauSommets_.push_back(new Sommet(string(valeur1), string(valeur2)));
			}

		std::getline(fichier, ligne);
		stream.clear();
		stream.str(ligne);

		while (true) {
			Sommet* sommets[2];
			getline(stream, valeur1, ',');
			sommets[0] = trouverSommet(valeur1);
			getline(stream, valeur2, ',');
			sommets[1] = trouverSommet(valeur2);
			getline(stream, valeur3, ';');
			if (stream.eof()) break;
			tableauArcs_.push_back(new Arc(sommets[0], sommets[1], stoi(valeur3)));
			sommets[0]->setSommetsVoisinsSortant(sommets[1]);
			sommets[1]->setSommetsVoisinsEntrant(sommets[0]);
		}
	}
	else { cout << endl << "Erreure de lecture" << endl << endl; }
}

void Graphe::lireGraphe()
{
	for (int i = 0; i < tableauSommets_.size(); i++)
	{
		cout << endl << "(" << tableauSommets_[i]->getNom() << ", " << tableauSommets_[i]->getType() << ", (";
		if (!tableauSommets_[i]->getVecteurSommetsVoisinSortant().empty()) {
			for (int j = 0; j < (tableauSommets_[i]->getVecteurSommetsVoisinSortant().size() - 1); j++)
			{
				cout << tableauSommets_[i]->getVecteurSommetsVoisinSortant().at(j)->getNom() << ", ";
			}
			cout << tableauSommets_[i]->getVecteurSommetsVoisinSortant().back()->getNom();
		}

		if (!tableauSommets_[i]->getVecteurSommetsVoisinEntrant().empty()) {
			for (int k = 0; k < ((tableauSommets_[i]->getVecteurSommetsVoisinEntrant().size())); k++)
			{
				if (k == 0 && tableauSommets_[i]->getVecteurSommetsVoisinSortant().empty()) { cout << tableauSommets_[i]->getVecteurSommetsVoisinEntrant().at(k)->getNom(); }
				else { cout << ", " << tableauSommets_[i]->getVecteurSommetsVoisinEntrant().at(k)->getNom(); }
			}
		}
		cout << "))";

	}
}

Graphe Graphe::extractionGraphe(Vehicule* vehicule, const string& depart)
{
	unordered_map<string, std::pair<int, string>> tableauDeDonne_;
	bool toutesLesSommetsSontVisiter = false;
	string sommetEtudier = depart;
	int INF = 999;
	int sommeTemp = 0;
	int sommeTemp2 = 0;
	string stringTemp;
	int valeurMin = INF;
	string sommetChoisiLeCalculAvant = sommetEtudier;


//DEBUT DE DJIKSTRA 

	//initialiser BAse de donnee
		for (int i = 0; i < tableauSommets_.size(); i++)
	{
		tableauDeDonne_.emplace(tableauSommets_[i]->getNom(), make_pair(INF, "INDEFINI"));
		tableauSommetsNonVisiter_.push_back(tableauSommets_[i]);
	}
	

	while (!toutesLesSommetsSontVisiter) {
		// UPDATE BASE DE DONNE DEPART = 0
		auto trouver = tableauDeDonne_.find(depart);
		if (trouver != tableauDeDonne_.end()) {
			trouver->second.first = 0;
			trouver->second.second = depart;
		}
		if (!trouverSommet(sommetEtudier)->getVecteurSommetsVoisinSortant().empty()) {
			//UPDATE BASE DE DONNEEE
			for (int i = 0; i < trouverSommet(sommetEtudier)->getVecteurSommetsVoisinSortant().size(); i++)
			{
				auto sommet = trouverSommet(sommetEtudier)->getVecteurSommetsVoisinSortant().at(i);
					//iterate all arcs
				for (int j = 0; j < (tableauArcs_.size()); j++)
				{		//								   FIN == voisinSortant											DEBUT  == SOMMETETIDIER
					if (tableauArcs_.at(j)->getFin()->getNom() == sommet->getNom() && tableauArcs_.at(j)->getDebut()->getNom() == sommetEtudier) {
						//		ITERATE TABLEAU DE DONNEE
						for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
							//IF VOISIN SORTANT == TABLEAU DE DONNE FIRST
							if (sommet->getNom() == it->first) {
								for (auto it2 = tableauDeDonne_.begin(); it2 != tableauDeDonne_.end(); ++it2) {
									if (it2->first == sommetEtudier) {
										sommeTemp = it2->second.first;
										//it->second.second = it2->first;
									}
								}
								int distanceDeDepart = (-(tableauArcs_.at(j)->getLongeurArc()) + sommeTemp);
								if (it->second.first > distanceDeDepart) {
									it->second.first = distanceDeDepart;
									it->second.second = sommetEtudier;
								}
							}
						}
					}
				}
			}
		}
		//set depart comme sommet visiter + enlever sommet non visiter
		tableauSommetsVisiter_.push_back(trouverSommet(sommetEtudier));
		enleverSommetDeTableauNonVisiter(sommetEtudier);

		int temp3 = 999;
		for (int k = 0; k < tableauSommetsNonVisiter_.size(); k++) {
			for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
				if (it->first == tableauSommetsNonVisiter_.at(k)->getNom()) {
					if (it->second.first < temp3) {
						//ici on prend le somemt non visiter avec le minimum de cost
						sommetEtudier = it->first;
						temp3 = it->second.first;
					}
				}
			}
		}
		//if (!tableauSommetsNonVisiter_.empty()) {
		//	sommetEtudier = tableauSommetsNonVisiter_.back()->getNom();
		//}
		//valeurMin = INF;
		//for (int k = 0; k < tableauSommetsNonVisiter_.size(); k++) {

		//	for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
		//		// IF UN VOISIN SORTANT == SOMMET ITERATEUR
		//		if (tableauSommetsNonVisiter_.at(k) == trouverSommet(it->first)) {
		//				//IF DISTANCE ARC < VAL MIN
		//			if (it->second.first < valeurMin) {
		//				valeurMin = it->second.first;
		//				stringTemp = it->first;
		//				//it->second.second = sommetEtudier;
		//				sommeTemp2 = it->second.first;
		//			}
		//		}
		//	}

		//}
		//cout << sommetEtudier<<"\n";
		//sommetEtudier = stringTemp;
		//sommeTemp = sommeTemp2;


		//SI on a visiter tousles sommet, on quite de la boucle
		if (tableauSommetsNonVisiter_.empty())
			toutesLesSommetsSontVisiter = true;
		for (int k = 0; k < tableauSommetsVisiter_.size(); k++) {
			//cout << tableauSommetsVisiter_.at(k) << "  string graphePLusPetit = ;				string arrow =;			string iterateur = arrive;			int distanceDePlusPetit = 0;	t;}";
			if (sommetEtudier == tableauSommetsVisiter_.at(k)->getNom())
				toutesLesSommetsSontVisiter = true;
		}
	}

	////verifier fin 
	string graphePLusGrand = " ";
	string arrow = " --> ";
	string iterateur;
	int distanceDePlusPetit = 0;
	vector<int> listeDeCost;
	vector<string> listeDeSommet;

	//verifier c'est quoi le plus long chemin
	for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
		if (it->second.first < distanceDePlusPetit)
			distanceDePlusPetit = it->second.first;
		iterateur = it->first;
	}

	while (iterateur != depart) {
		for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
			
			if (it->first == iterateur) {
				graphePLusGrand.insert(0, iterateur);
				listeDeCost.push_back(it->second.first);
				listeDeSommet.push_back(it->first);
				graphePLusGrand.insert(0, arrow);
				iterateur = it->second.second;
			}
		}
	}
	graphePLusGrand.insert(0, iterateur);

	for (int i = 0; i < listeDeCost.size() - 1; i++)
	{
		if (vehicule->getAutonomieRestante() + (listeDeCost.at(i) - (listeDeCost.at(i + 1))) > 0) {
			if (trouverSommet(listeDeSommet.at(i))->getType() == vehicule->getType() || trouverSommet(listeDeSommet.at(i))->getType() == "hybride")
				vehicule->plein();
		}
		else {
			for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
				if (iterateur == it->first) {
					it->second.first = INF;
				}
			}
		}
	}

	vehicule->setAutonomieRestante((vehicule->getAutonomieComplete()) + distanceDePlusPetit);
	
	cout << graphePLusGrand << '\n'
		
		<< "trajet (km) : " << -distanceDePlusPetit;



	return Graphe();

}

Graphe Graphe::plusCourtChemin(const string& depart, const string& arrive, Vehicule* vehicule) {
	unordered_map<string, std::pair<int, string>> tableauDeDonne_;
	bool toutesLesSommetsSontVisiter = false;
	string sommetEtudier = depart;
	int INF = 999;
	int sommeTemp = 0;
	int sommeTemp2 = 0;
	string stringTemp;
	int valeurMin = INF;
	string sommetChoisiLeCalculAvant = sommetEtudier;

	//initialiser BAse de donnee
	if (depart == arrive) {
		cout << "\nLe Sommet du depart ne peut pas etre le sommet d'arrive !\n";
		return Graphe();
	}

//DEBUT DE DJIKSTRA

	for (int i = 0; i < tableauSommets_.size(); i++)
	{
		tableauDeDonne_.emplace(tableauSommets_[i]->getNom(), make_pair(INF, "INDEFINI"));
		tableauSommetsNonVisiter_.push_back(tableauSommets_[i]);
	}

	while (!toutesLesSommetsSontVisiter) {
		// UPDATE BASE DE DONNE DEPART = 0
		auto trouver = tableauDeDonne_.find(depart);
		if (trouver != tableauDeDonne_.end()) {
			trouver->second.first = 0;
			trouver->second.second = depart;
		}
		if (!trouverSommet(sommetEtudier)->getVecteurSommetsVoisinSortant().empty()) {


			//UPDATE BASE DE DONNEEE
			for (int i = 0; i < trouverSommet(sommetEtudier)->getVecteurSommetsVoisinSortant().size(); i++)
			{
				auto sommet = trouverSommet(sommetEtudier)->getVecteurSommetsVoisinSortant().at(i);
				//iterate all arcs
				for (int j = 0; j < (tableauArcs_.size()); j++)
				{		//								   FIN == voisinSortant											DEBUT  == SOMMETETIDIER
					if (tableauArcs_.at(j)->getFin()->getNom() == sommet->getNom() && tableauArcs_.at(j)->getDebut()->getNom() == sommetEtudier) {
						//		ITERATE TABLEAU DE DONNEE
						for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
							//IF VOISIN SORTANT == TABLEAU DE DONNE FIRST
							if (sommet->getNom() == it->first) {
								for (auto it2 = tableauDeDonne_.begin(); it2 != tableauDeDonne_.end(); ++it2) {
									if (it2->first == sommetEtudier) {
										sommeTemp = it2->second.first;
									}
								}
								int distanceDeDepart = ((tableauArcs_.at(j)->getLongeurArc()) + sommeTemp);
								if (it->second.first > distanceDeDepart) {
									it->second.first = distanceDeDepart;
									it->second.second = sommetEtudier;
								}
							}
						}
					}
				}
			}
		}
		//set depart comme sommet visiter + enlever sommet non visiter
		tableauSommetsVisiter_.push_back(trouverSommet(sommetEtudier));
		enleverSommetDeTableauNonVisiter(sommetEtudier);

		int temp3=999;
		for (int k = 0; k < tableauSommetsNonVisiter_.size(); k++) {
			for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
				if (it->first == tableauSommetsNonVisiter_.at(k)->getNom()) {
					if (it->second.first < temp3) {
						//ici on prend le somemt non visiter avec le minimum de cost
						sommetEtudier = it->first;
						temp3 = it->second.first;
					}
				}
			}
		}
	
		//SI on a visiter tousles sommet, on quite de la boucle
		if (tableauSommetsNonVisiter_.empty())
			toutesLesSommetsSontVisiter = true;
		for (int k = 0; k < tableauSommetsVisiter_.size(); k++) {
			if (sommetEtudier == tableauSommetsVisiter_.at(k)->getNom())
			toutesLesSommetsSontVisiter = true;
		}
	}
	
	//verifier fin 
	string graphePLusPetit = " ";
	string arrow = " --> ";
	string iterateur = arrive;
	int distanceDePlusPetit = 0;
	vector<int> listeDeCost;
	vector<string> listeDeSommet;
	bool arriveExiste = false;
	//verifier si il ya un arrive dans le tableaud e donner creer
	for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {
		if (it->first == arrive) {
			if(it->second.first != INF)
				arriveExiste = true;
		}
	
	}	
	if (arriveExiste) {

			while (iterateur != depart) {


				for (auto it = tableauDeDonne_.begin(); it != tableauDeDonne_.end(); ++it) {

					if (it->first == arrive) {
						distanceDePlusPetit = it->second.first;

					}
					if (it->first == iterateur) {

						graphePLusPetit.insert(0, iterateur);
						listeDeCost.push_back(it->second.first);
						listeDeSommet.push_back(it->first);
						graphePLusPetit.insert(0, arrow);
						iterateur = it->second.second;
					}
				}

			}
	}
	else {
		cout << "\nPas de chemin possible.\n";
		return Graphe();
	}
		
	
	graphePLusPetit.insert(0, iterateur);

	for (int i = 0; i < listeDeCost.size() - 1; i++)
	{
		if (vehicule->getAutonomieRestante() - (listeDeCost.at(i) - (listeDeCost.at(i + 1))) > 0) {
			if (trouverSommet(listeDeSommet.at(i))->getType() == vehicule->getType() || trouverSommet(listeDeSommet.at(i))->getType() == "hybride")
				vehicule->plein();
		}
		else {
			cout << "\nImpossible d'aller, puisque l'autonomie restante est egale a zero.\n" << endl;
			break;
		}
	}
	if (vehicule->getAutonomieRestante() - (listeDeCost.back()) > 0) {
		if (trouverSommet(listeDeSommet.back())->getType() == vehicule->getType() || trouverSommet(listeDeSommet.back())->getType() == "hybride")
			vehicule->plein();
	}
	else {
		cout << "\nImpossible d'aller, puisque l'autonomie restante est egale a zero.\n" << endl;
	}


	vehicule->setAutonomieRestante((vehicule->getAutonomieComplete()) - distanceDePlusPetit);
	cout << endl<<graphePLusPetit << '\n'
		<< "Autonomie restant (%) : " << vehicule->getPourcentageAutonomieRestante() << '\n'
		<< "trajet (km) : " << distanceDePlusPetit;

	return Graphe();
}

Sommet* Graphe::trouverSommet(const string& identifiant)
{
	for (int i = 0; i < tableauSommets_.size(); i++)
	{
		if (identifiant == tableauSommets_[i]->getNom()) {
			return tableauSommets_[i];
		}
	}
	return nullptr;
}

void Graphe::enleverSommetDeTableauNonVisiter(const string& identifiant)
{
	for (int i = 0; i < tableauSommetsNonVisiter_.size(); i++)
	{
		if (identifiant == tableauSommetsNonVisiter_[i]->getNom()) {
			tableauSommetsNonVisiter_.erase(tableauSommetsNonVisiter_.begin() + i);
		}
	}
}