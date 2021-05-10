/*
 * Fichier: Sommet.h
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Definition la classe Sommet.
 */

#ifndef SOMMET_HEADER
#define SOMMET_HEADER

#include <iostream>
#include <vector>

#include "Arc.h"
#include "Vehicule.h"

using namespace std;

class Sommet
{
public:
	Sommet();
	Sommet(const string& nom, const string& type);
	~Sommet();

	const string& getNom() const;
	const string& getType() const;
	vector<Arc*> getArcs() const;
	Arc* getArcDeDeuxSommets(Sommet* fin);
	vector<Sommet*> getSommetsVoisinsSortant() const;
	vector<Sommet*> getVecteurSommetsVoisinSortant() const;
	vector<Sommet*> getVecteurSommetsVoisinEntrant() const;

	void setSommetsVoisinsSortant(Sommet* sommet);
	void setSommetsVoisinsEntrant(Sommet* sommet);
	bool rechargementPossible(Vehicule* vehicule) const;

private:
	string nom_;
	string type_;
	vector<Sommet*> sommetsVoisinSortant_;
	vector<Sommet*> sommetsVoisinEntrant_;
	vector<Arc*> arcsAdjacents_;

};

#endif