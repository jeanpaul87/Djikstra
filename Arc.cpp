/*
 * Fichier: Arc.cpp
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Implémenter la classe Arc.
 */

#include "Arc.h"

Arc::Arc()
{
}

Arc::Arc(Sommet* debut, Sommet* fin, int longeurArc)
    :debut_(debut), fin_(fin), longeurArc_(longeurArc)
{
    directionSommet_.push_back(debut_);
    directionSommet_.push_back(fin_);
}

Arc::~Arc()
{
    delete debut_;
    delete fin_;
}

int Arc::GetLongeurArc() const
{
    return longeurArc_;
}

Sommet* Arc::getDebut() const
{
    return directionSommet_.front();
}

Sommet* Arc::getFin() const
{
    return directionSommet_.back();
}

Sommet* Arc::getSommets() const
{
    Sommet* sommets[2];

    sommets[0] = directionSommet_.front();
    sommets[1] = directionSommet_.back();

    return *sommets;
}

int Arc::getLongeurArc()
{
    return longeurArc_;
}