$(function(){
	current();
	setInterval(function(){
		current();
	},1000);
	$(".picture").css({'height':$(window).height()-3})
})

function current(){
	var date=new Date();
	var year=date.getFullYear();
	var month=date.getMonth()+1;
	var day=date.getDate();
	var hour=date.getHours();
	var minute=date.getMinutes();
	var second=date.getSeconds();
	month=justify(month);
	day=justify(day);
	hour=justify(hour);
	minute=justify(minute);
	second=justify(second);	
	$(".time").html(year+'-'+month+'-'+day+'&nbsp;&nbsp;&nbsp;&nbsp;'+hour+':'+minute+':'+second);
}

function justify(index){
	if(index<10){
		index='0'+index;
	}
	return index;
}

$(".title").change(function(){
	change($(this),$(".left h2"))
})

$(".content").change(function(){
	change($(this),$(".left p"))
})

function change(obj,p){
	if(obj.find("option:selected").text()=='黄色'){
		p.css({'color':'yellow'})
	}else if(obj.find("option:selected").text()=='红色'){
		p.css({'color':'red'})
	}else{
		p.css({'color':'black'})
	}
}