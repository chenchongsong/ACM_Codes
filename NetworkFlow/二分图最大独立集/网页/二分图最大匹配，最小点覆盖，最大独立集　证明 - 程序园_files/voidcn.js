$(document).ready(function() {
    $("#show-index").click(function() {
        if ($("#show-index").html() == "[ 隐藏 ]") {
            $("#index-ul").fadeOut("normal");
            $("#show-index").html("[ 展开 ]")
        } else if ($("#show-index").html() == "[ 展开 ]") {
            $("#index-ul").fadeIn("normal");
            $("#show-index").html("[ 隐藏 ]")
        } else {
            return false
        }
    })
});
	
+ (function($){
		window._bd_share_config = {
			common: {
				"bdText": "【" + $("title").text() + "】" + $(".post-content p:lt(2)").text(),
				"bdMini": "2",
				"bdMiniList": false,
				"bdPic": $(".post-content img:first") ? $(".post-content img:first").attr("src") : "",
				"bdStyle": "0",
				"bdSize": "24"
			},
			share: [{
				bdCustomStyle: 'http://www.voidcn.com/css/share.css'
			}],
		};
		with(document) 0[(getElementsByTagName("head")[0] || body).appendChild(createElement("script")).src = "http://bdimg.share.baidu.com/static/api/js/share.js?cdnversion=" + ~ ( - new Date() / 36e5)];
})(window.jQuery);


//$('.archives ul.archives-monthlisting').hide();
//$('.archives ul.archives-monthlisting:first').show();
//$('.archives .m-title').click(function() {
//	$(this).next().slideToggle('fast');
//	return false;
//});