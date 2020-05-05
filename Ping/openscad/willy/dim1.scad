//L'objet de ce fichier est de consigner les dimensions et les contraintes communes aux trois pieces de la e-poignee.
//Ces trois pieces sont fabriquees sur imprimante 3D, elles sont completees d'un Circuit Imprime (CI) et d'un isolateur.
//Le montage de l'ensemble est realise à l'aide d'un jeu de visserie compose
//de vis, de rondelles, d'un ecrou autobloquant et d'entretoises filetees.
//Les noms attribues a ces trois pieces sont la jupe, le top et le logo.
//Les dimensions relatives au CI sont exprimees en pouces et converties en mm à l'aide d'un Coefficient de Conversion (CC).
CC=25.4;//Coefficient de Conversion (pouce -> mm)
L1=1.6*CC;//longueur du CI
L2=1.3*CC;//entre axes des trous de fixation du CI
l1=1.2*CC;//largeur du CI
l2=0.9*CC;//entre axes des trous de fixation du CI
r=(0.087*CC)/2;//rayon de percage des trous de fixation du CI
e=0.1*CC;//epaisseur des parois
R=37.15;//Rayon du cercle de revolution du tore
//La premiere contrainte commune au logo et au top est la visibilite de l'embase USB.
//Cette visibilite est necessaire quand l'utilisateur etablit la connection du cable sur l'embase USB.
//La seconde contrainte est thermique, la temperature du couvercle peut atteindre des valeurs aux environ des 90°C.
//L'experience a montree que la matiere (PLA ou ABS) ramolie a ces temperatures.
//Cette contrainte est prise en compte par l'insertion de l'isolateur, elle concerne egalement la perimetre inferieur de la jupe.

//---------------CHANGEMENT DE CI = CONSERVATION DES VALEURS POUR LA JUPE-------------------
x1=2.25*CC;//entre axes des trous de fixation du CI
y1=0.8*CC;//entre axes des trous de fixation du CI

