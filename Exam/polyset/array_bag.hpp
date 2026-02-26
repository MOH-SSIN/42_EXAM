						/* File deja m3ti */

#ifndef EXAM_ASSIGNMENTS_ARRAY_BAG_HPP
#define EXAM_ASSIGNMENTS_ARRAY_BAG_HPP

#include "bag.hpp"

class array_bag : virtual public bag
{
	protected:
		int *data; // Pointeur vers le tableau de données
		int size;  // Taille actuelle du tableau

	public:
		array_bag(); 
		array_bag(const array_bag &); 
		array_bag &operator=(const array_bag &other); 
		~array_bag(); 

		void insert(int); 
		void insert(int *, int); // Insère plusieurs éléments à partir d'un tableau
		void print() const; 
		void clear();
};

#endif


/* info supli :
	- C’est quoi array_bag : class array_bag : virtual public bag
		* 👉 array_bag est un vrai bag.
		* 👉 Il respecte les règles de bag.
		* 👉 Mais il utilise un tableau pour stocker les nombres.
		* Donc :
			# bag = idée 📜
			# array_bag = vraie implémentation avec tableau 📦
	
	- Les variables importantes : (int *data; et int size;)
		🔹 "int* data" : C’est un tableau dynamique.
		🔹 "int size " : C’est combien d’éléments on a.

	- Pourquoi protected ?
		* Parce que plus tard :
		* 👉 searchable_array_bag va hériter de array_bag
		* 👉 Il aura besoin d’accéder à data et size
		* Si on met private ❌
		* La classe enfant ne peut pas les utiliser.

	- Les fonctions 
		* array_bag() : Créer un bag vide , Au début (data = NULL, size = 0)
		* array_bag(const array_bag &) : Copier un autre bag.
		* operator= : Même chose que copie mais avec =
		* ~array_bag() : Libère la mémoire du tableau.

	- Les fonctions obligatoires de bag :
		* insert(int)       : Ajouter un seul nombre.
		* insert(int*, int) : Ajouter plusieurs nombres d’un tableau.
		* print()           : Afficher les nombres.
		* clear()           : Supprimer tout.
	
	- 🎯 Résumé très simple :
		- array_bag = un sac de nombres
		- Il utilise :
			* un tableau (data)
			*une taille (size)

		- Il sait :
			*ajouter
			*afficher
			*vider
			*copier
*/