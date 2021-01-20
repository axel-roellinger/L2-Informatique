homme(albert).
homme(jean).
homme(paul).
homme(bertrand).
homme(louis).
homme(benoit).
femme(germaine).
femme(christiane).
femme(simone).
femme(marie).
femme(sophie).
parent(albert, jean).
parent(paul, bertrand).
parent(paul, sophie).
parent(jean, paul).
parent(jean, simone).
parent(louis, benoit).
parent(germaine, jean).
parent(christiane, simone).
parent(christiane, paul).
parent(simone, benoit).
parent(marie, bertrand).
parent(marie, sophie).

%Exercice 1 :

/*
Q1. Est-ce que Jean est un homme
	=> homme(jean).
		=> yes

Q2. Est-ce que Benoît est une femme ?
	=> femme(benoit)
		=> no

Q3. Qui est une femme ?
	=> femme(X).
		=> germaine
		=> christiane
		=> simone
		=> marie
		=> sophie

Q4. Est-ce que Marie est un parent de Sophie ?
	=> parent(marie, sophie).
		=> yes

Q5. Quels sont les parents de Jean ?
	=> parent(X, jean)
		=> albert
		=> germaine

Q6. Quels sont les enfants de Paul ?
	=> parent(paul, X)
		=> bertrand 
		=> sophie

Q7. Quels hommes sont parents ?
	=> homme(X), parent(X, Y).
		=> X = albert
		   Y = jean
		=> X = jean
		   Y = paul
*/

%Exercice 2 :

%Q1. X est le fils de Y

	fils(X, Y) :- homme(Y), parent(X, Y).


%Q2. X est la soeur de Y

	soeur(X, Y) :- femme(X), parent(Z, X), parent(Z, Y).


%Q3. X est une grand-mère de Y

	grand_mere(X, Y) :- femme(X), parent(X, Z), parent(Z, Y)


%Q4. X est une tante de Y 

	tante(X,Y) :- femme(X), soeur(X, Z), parent(Z, Y)



personne(alice, f, 85, paris, retraitee, 1500.0).
personne(edouard, m, 40, strasbourg, ingenieur, 3000.0).
personne(luc, m, 27, paris, enseignant, 1800.0).
personne(pauline, f, 35, marseille, informaticien, 2000.0).


%Exercice 3 :

%Nouvelles règles :

individu(X):- personne(X, _, _, _, _, _).
masculin(X):- personne(X, m,_ , _, _, _).
feminin(X):- personne(X, f, _, _, _, _).
est_age_de(X,A):- personne(X, _, A, _, _, _).

%Q1
	majeur(X) :- personne(X, _, A, _, _, _), A >= 18.


%Q2	
	mineur(X) :- personne(X, _, A, _, _, _), A < 18.


%Q3
	meme_age(X, Y) :- est_age_de(X, A1), est_age_de(Y, A2), A1 = A2.


%Q4
	meme_ville(X, Y) :- personne(X, _, _, Ville1, _, _), personne(Y, _, _, Ville2, _, _), Ville1 = Ville2.


%Q5
	epoux_possibles(X, Y) :- personne(X, Genre1, _, _, _, _), personne(Y, Genre2, _, _, _, _), Genre1 \= Genre2.


%Q6
	meme_job(X, Y) :- personne(X, _, _, _, Job1, _), personne(Y, _, _, _, Job2, _), Job1 = Job2.


%Q7
	gagne_plus_que(X, Y) :- personne(X, _, _, _, _, Paie1), personne(Y, _, _, _, _, Paie2), Paie1 > Paie2.


%Q8
	paies_meme_ordre(X, Y) :- personne(X, _, _, _, _, Paie1), personne(Y, _, _, _, _, Paie2), (Paie1/Paie2 >= 0.8 ; Paie1/Paie2 =< 1.2).


%Exercice 4 :

/*
personne(marie,vin)
personne(pierre,personne(_,vin))
voleur(pierre)
*/
%vol(X,Y) : X vole Y

vol(X,Y):- voleur(X), personne(X,Y)

%Ne fonctionne pas, Prolog ne peut pas remplacer (personne_,vin) par un élément de la base de données

%Correction : 

voleur(pierre).
aime(marie, vin).
aime(pierre, X) :- aime(X, vin).
vole(X, Y) :- voleur(X), aime(X, Y).

%Pierre vole Marie
