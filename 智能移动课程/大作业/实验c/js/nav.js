$(".down").hover(function(){
	$(this).find("ul").stop(true,true);
	$(this).find("ul").removeClass("disnone");
	$(this).find("ul").animate({'left':'-10px','opacity':'1'},80)
},function(){
	$(this).find("ul").stop(true,true);
	$(this).find("ul").animate({'left':'-120px','opacity':'0'},80);
	$(this).find("ul").addClass("disnone");
})