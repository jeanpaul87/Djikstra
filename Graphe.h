/*
 * Fichier: Graphe.h
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Definition la classe Graphe.
 */

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "Arc.h"
#include "Sommet.h"
#include "Vehicule.h"

using namespace std;

class Graphe {

public:
	Graphe();

	Graphe(const Graphe& graphe);

	~Graphe();

	void creerGraphe(const string& nomFichier);
	void lireGraphe();
	Graphe extractionGraphe(Vehicule* vehicule, const string& depart);

	Graphe plusCourtChemin(const string& depart, const string& arrive, Vehicule* vehicule);
	Sommet* trouverSommet(const string& identifiant);
	void enleverSommetDeTableauNonVisiter(const string& identifiant);
private:

	vector<Sommet*> tableauSommets_;
	vector<Sommet*> tableauSommetsNonVisiter_;
	vector<Sommet*> tableauSommetsVisiter_;
	vector<Arc*> tableauArcs_;
};