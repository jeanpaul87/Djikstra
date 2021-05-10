/*
 * Fichier: Sommet.cpp
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Implementation de la classe Sommet.
 */

#include "Sommet.h"

using namespace std;

Sommet::Sommet()
{
}

Sommet::Sommet(const std::string& nom, const std::string& type) :
	nom_(nom), type_(type)
{
}

Sommet::~Sommet()
{
}

const string& Sommet::getNom() const
{
	return nom_;
}

const string& Sommet::getType() const
{
	return type_;
}

vector<Arc*> Sommet::getArcs() const
{
	return arcsAdjacents_;
}

Arc* Sommet::getArcDeDeuxSommets(Sommet* fin)
{
	Arc* arcTrouver;
	for (Arc* arc : arcsAdjacents_) {
		cout << "FOUNDD";
		if (arc->getFin() == fin) {
			return arc;
		}
	}
	return nullptr;
}

vector<Sommet*> Sommet::getSommetsVoisinsSortant() const
{
	vector<Sommet*> sommentsVoisins;
	for (Arc* arcAdjacents : arcsAdjacents_) {
		sommentsVoisins.push_back(arcAdjacents->getFin());
	}
	return sommentsVoisins;
}

vector<Sommet*> Sommet::getVecteurSommetsVoisinSortant() const
{
	return sommetsVoisinSortant_;
}

vector<Sommet*> Sommet::getVecteurSommetsVoisinEntrant() const
{
	return sommetsVoisinEntrant_;
}

void Sommet::setSommetsVoisinsSortant(Sommet* sommet)
{

	sommetsVoisinSortant_.push_back(sommet);

}

void Sommet::setSommetsVoisinsEntrant(Sommet* sommet)
{
	sommetsVoisinEntrant_.push_back(sommet);
}

bool Sommet::rechargementPossible(Vehicule* vehicule) const
{
	if (type_ == "hybrid" || type_ == vehicule->getType()) {
		return true;
	}
	else
		return false;
}