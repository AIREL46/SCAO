function affi(){
startSubmenu("mb12","mmenu",300 );
si("Activer la loupe","/Art.nsf/A?Open&RA=8BWSK7");si("---","aaaa");
si("Passer commande d'une reproduction à l'huile","Buy-OilPainting?OpenForm&RA=8BWSK7");
si("Achat d'une impression sur toile","Buy-PrintTextured?OpenForm&RA=8BWSK7");
si("Achetez un ensemble polyptique encadré","Buy-GroupSetOilPainting?OpenForm&RA=8BWSK7");
si("Envoyer une E-Carte avec cette oeuvre","Ecard?OpenForm&RA=8BWSK7");
si("Affichez cette oeuvre sur votre site internet","/Art.nsf/EmbedHTML?OpenForm&RA=8BWSK7");
si("Ajouter aux favoris ","/Art.nsf/MyFavorites?OpenForm&Action=add&RA=8BWSK7");
si("---","aaaa");
si("Oeuvres similaires à celle ci sur WahooArt.com","/Art.nsf/Art_FR?Open&Query=(%22555500%22,%22@hcRS5D%22,%22@hpSSP%22,%22@hcMTzKE%22,%22@hpSTQP%22,%22@hpTTTMQ%22) AND (%22Jour%22,%22Heureux%22,%22Joaquin Sorolla Y Bastida%22,%22Huile Sur Toile%22)&Complex&FS=True");
si("Toutes oeuvres avec couleur principale (<Span class='Artwork-Square' style='background-color:#555500;'>_</span>) et aussi (<Span class='Artwork-Square' style='background-color:#;'>_</Span>)","/Art.nsf/Art_FR?Open&Query=([COLORSMAIN]=555500) AND &Complex&FS=True");
si("Oeuvres dans le musée Galleria d'Arte Moderna di Udine (Udine, Italy)","/Art.nsf/Art_FR?Open&Query=([Champ32]=%22Galleria d'Arte Moderna di Udine (Udine, Italy)%22) AND (%22Galleria d'Arte Moderna di Udine (Udine, Italy)%22,%22Joaquin Sorolla Y Bastida%22,%221900%22,%22@Landscape@%22,%22555500%22)&Complex&FS=True");
endSubmenu("mb12");
}
