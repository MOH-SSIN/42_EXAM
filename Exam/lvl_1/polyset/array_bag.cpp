						/* File deja m3ti */

#include "array_bag.hpp"
#include <iostream>

array_bag::array_bag() : data(0), size(0) {}

array_bag::array_bag(const array_bag &other) {
	this->data = new int[other.size]; //implémente un tableau de taille 'size'
	for (int i = 0; i < other.size; i++)
		this->data[i] = other.data[i];
	this->size = other.size;
}

array_bag &array_bag::operator=(const array_bag &other) {
	this->clear();
	this->data = new int[other.size];
	for (int i = 0; i < other.size; i++)
		this->data[i] = other.data[i];
	this->size = other.size;
	return *this;
}

array_bag::~array_bag() {
	delete this->data;
}

//créé un tableau temporaire d'une taille supérieur à l'existant de 1 unité puis recopie les valeurs et ajoute la nouvelle valeur à la fin puis supprime la tableau existant pour le remplacer par tmp.
void array_bag::insert(int val) {
	int *tmp = new int[size + 1]; 
	for (int i = 0; i < size; i++)
		tmp[i] = this->data[i];
	tmp[this->size] = val;
	delete this->data;
	this->data = tmp;
	this->size++;
}

void array_bag::insert(int *a, int s) {
	for (int i = 0; i < s; i++)
		this->insert(a[i]);
}

void array_bag::print() const {
	for (int i = 0; i < this->size; i++)
		std::cout << this->data[i] << " ";
	std::cout << std::endl;
}

void array_bag::clear() {
	delete this->data;
	this->data = 0;
	this->size = 0;
}

/* info supli :
	-> insert(int val) :
		* Crée un nouveau tableau plus grand (+1)
		* Copie tous les éléments existants
		* Ajoute le nouveau nombre à la fin
		* Supprime l’ancien tableau
		* Remplace data par le nouveau
		* Augmente size

	-> insert(int* a, int s) :
		* Tu as un tableau a de taille s
		* Tu ajoutes chaque élément avec insert(int)
		* Réutilise la fonction précédente → pas de répétition de code
	
	-> print() :
		* Parcours le tableau
		* Affiche chaque nombre avec un espace
		* À la fin, passe à la ligne
	
	-> clear() : 
		* Supprime le tableau actuel
		* Remet le sac vide (data = 0, size = 0)

*/