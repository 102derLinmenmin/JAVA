$(function () {
    var index=0;
    var img=$("#imgList");
    var img_width=img.find('li').width();//轮播图宽度
    var indicators=$("#indicators li");
    var timer=timer=setInterval(rightClick,2500);//自动播放
    img.find('li:eq(0)').clone(true).appendTo(img);

    $("#carousel").hover(function () {
        clearInterval(timer);
        $(this).find('span').show();
    },function () {
        $(this).find('span').hide();
        timer=setInterval(rightClick,2500);
    });

    indicators.hover(function () {
        if(index===6){
            img.css('left','0');
        }
        index=indicators.index(this);
        img.stop(true,false)
            .animate({"left": -index*img_width+"px"},800);
        $(this).addClass('active')
            .siblings('li').removeClass('active');
    });
    $("#left").click(function () {
        if(index===0){
            img.css('left',-6*img_width+'px');
            index=6;
        }
        index--;
        img.stop(true,false)
            .animate({"left": -index*img_width+"px"},800);
        indicators.eq(index).addClass('active')
            .siblings('li').removeClass('active');
    });
    $("#right").click(rightClick);
    function rightClick() {
        if(index===6){
            img.css('left','0');
            index=0;
        }
        index++;
        img.stop(true,false)
            .animate({"left": -index*img_width+"px"},800);
        if(index===6){
            indicators.eq(0).addClass('active')
                .siblings('li').removeClass('active');
        }else{
            indicators.eq(index).addClass('active')
                .siblings('li').removeClass('active');
        }
    }
});