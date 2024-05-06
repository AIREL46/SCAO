// <Script>  
var MTXT="";


function startMainMenu(file,h,w,dir,space,align)
{
}
function endMainMenu(file,h,w)
{
}
function mi(name,ext,h,w,url,tar,alt,dir,state,s)
{
	MTXT+=("<li class='HeaderMainMenuTitle' >");
//	MTXT+=("<A onclick=\"javascript:this.parentNode.childNodes[2].style.visibility='visible';\" style=\"cursor:pointer;\" >");
	MTXT+=("<A style=\"cursor:pointer;\" >");
	MTXT+=("<b>"+alt+"</b>");
	MTXT+=("</a>\n");
}
function startSubmenu(name,style,sw)
{
	MTXT+=("\n\n<ul class='HeaderMainMenuBlock' >");
}
function endSubmenu(name)
{
	MTXT+=("<hr style='padding:0; margin:0; border-width: 0px!important; height:5px; background-color: #8f2d03;'>\n");
	MTXT+=("</ul></li>\n\n");

	var GetMenu = document.getElementById('menu');
	if ( GetMenu )  GetMenu.innerHTML += MTXT;

	MTXT="";

}
function si(text,url)
{
	var letter= (MTXT.slice(-3));
	if (letter=="ul>"){
	MTXT+=("\n<hr style='padding:0; opacity: 0.4; margin:0; border-width: 0px!important; height:5px; background: url(\"menu-top-bg.jpg\") repeat-x;'>\n");
	}
	if(text=="---"){
	var letter= (MTXT.slice(-5));
	if (letter!="-x;'>"){
	MTXT+=("\n<hr style='margin:2px 0px 2px 0px; background-color: #89693B; height: 1px; width:100%;'>\n");
	}
	}
	else{
	
	MTXT+=("<li><a ");
	MTXT+=("href=\""+url+"\" >");
	MTXT+=(text+" </a></li>\n");
	}
}

// This Code is to make menu work on the tablets
$(function(){
$(".WahooArt-Header-menu li a").click(function(){
$(this).prev().after('ul').toggle();
});
});
