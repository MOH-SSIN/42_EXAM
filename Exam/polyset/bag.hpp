						/* File deja m3ti */

#ifndef EXAM_ASSIGNMENTS_BAG_HPP
#define EXAM_ASSIGNMENTS_BAG_HPP

class bag
{
public:
	virtual void insert(int) = 0;// Ajouter un seul nombre dans le bag.
	virtual void insert(int *, int)  = 0; // Ajouter plusieurs nombres d’un tableau. (tableau, taille)
	virtual void print() const = 0; // Afficher le contenu du bag.
	virtual void clear() = 0; // Supprimer tout le contenu.
};

#endif

/* info supli :
	
	-> Pourquoi virtual ?
		- Ça veut dire : Cette fonction sera redéfinie dans la classe enfant.
	-> Pourquoi = 0 ?
		- Le = 0 signifie :
			* 👉 Fonction virtuelle pure
			* 👉 Classe abstraite
			* 👉 On ne peut PAS faire :
				bag b; ❌ interdit
			* Mais on peut faire :
				bag* b = new array_bag(); <==> Ça s’appelle le polymorphisme.
	-> Résumé très simple
		- bag est comme une règle :
			-> Tout bag doit :
				* pouvoir insérer
				* pouvoir insérer un tableau
				* pouvoir afficher
				* pouvoir se vider
		- Mais bag ne dit pas COMMENT.
		- array_bag et tree_bag vont dire comment.
	
	-> Image simple 
		- bag = contrat 📜
		- Il dit : "Si tu veux être un bag, tu dois savoir faire ces 4 choses."
			* array_bag signe le contrat et implémente.
			* tree_bag signe le contrat et implémente.
		
*/