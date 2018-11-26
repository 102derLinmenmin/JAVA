// JavaScript Document

function cleardesc() {
     d = document.getElementById("description");
     d.innerHTML = "";
}
function hover(e) {
    if (!e) var e = window.event;
    whichlink = (e.target) ? e.target.id : e.srcElement.id;
    if (whichlink=="one") desc = "lovely";
    

d = document.getElementById("description");
    d.innerHTML = desc;
}
orderlink = document.getElementById("one");
orderlink.onmouseover=hover;
orderlink.onmouseout=cleardesc;


