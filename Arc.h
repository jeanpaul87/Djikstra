/*
 * Fichier: Arc.h
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Definition la classe Arc.
 */

#ifndef ARC_HEADER
#define ARC_HEADER

#include <vector>

class Sommet;

class Arc
{
public:
	Arc();
	Arc(Sommet* debut, Sommet* fin, int longeurArc);
	~Arc();

	int GetLongeurArc() const;

	Sommet* getDebut() const;
	Sommet* getFin() const;
	Sommet* getSommets() const;
	int getLongeurArc();
private:
	int longeurArc_;
	Sommet* debut_;
	Sommet* fin_;
	std::vector<Sommet*> directionSommet_;

};

#endif