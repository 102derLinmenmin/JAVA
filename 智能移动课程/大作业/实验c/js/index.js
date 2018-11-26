$(function(){
	$(".dask").css({'height':$(document).height()});
	$(".dask-box").css({'height':$(this).parent().find("img").height()});
})

$(".detail-box").hover(function(){
	$(this).find(".dask-box").css({'height':$(this).find("img").height()-20,'width':$(this).find("img").width()-20})
})

$(".submit").click(function(){
	var flag=true;
	for(var i=0;i<2;i++){
		if($(this).parent().find("label").eq(i).find("input[type='text']").val()==""){
			flag=false;
		}
	}
	if(flag==false){
		alert("请填写完整信息");
	}else{
		$(".message table tr:eq(0)").find("td").eq(1).text($(".form label").eq(0).find("input[type='text']").val());
		$(".message table tr:eq(1)").find("td").eq(1).text($(".form label").eq(1).find("input[type='text']").val());
		$(".dask").removeClass("disnone");
		$(".message").removeClass("disnone");
		$(".message").animate({'opacity':1,'marginTop':'-40px'},150)
	}
})

$(".close").click(function(){
	closeMessage();
})

$(".dask").click(function(){
	closeMessage();
})

function closeMessage(){
	$(".message").animate({'opacity':0,'marginTop':'-80px'},150);
	$(".dask").addClass("disnone");
	$(".message").addClass("disnone");
	for(var i=0;i<2;i++){
		$(".message").find("tr").eq(i).find("td:eq(1)").text("");
		$(".form label").eq(1).find("input[type='text']").val("");
	}
}