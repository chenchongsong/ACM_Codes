/*jQuery.切换插件*/(function(a){a.fn.extend({soChange:function(b){b=a.extend({thumbObj:null,botPrev:null,botNext:null,thumbNowClass:"now",thumbOverEvent:true,slideTime:1000,autoChange:true,clickFalse:true,overStop:true,changeTime:5000,delayTime:300},b||{});var h=a(this);var i;var k=h.size();var e=0;var g;var c;var f;function d(){if(e!=g){if(b.thumbObj!=null){a(b.thumbObj).removeClass(b.thumbNowClass).eq(g).addClass(b.thumbNowClass)}if(b.slideTime<=0){h.eq(e).hide();h.eq(g).show()}else{h.eq(e).fadeOut(b.slideTime);h.eq(g).fadeIn(b.slideTime)}e=g;if(b.autoChange==true){clearInterval(c);c=setInterval(j,b.changeTime)}}}function j(){g=(e+1)%k;d()}h.hide().eq(0).show();if(b.thumbObj!=null){i=a(b.thumbObj);i.removeClass(b.thumbNowClass).eq(0).addClass(b.thumbNowClass);i.click(function(){g=i.index(a(this));d();if(b.clickFalse==true){return false}});if(b.thumbOverEvent==true){i.mouseenter(function(){g=i.index(a(this));f=setTimeout(d,b.delayTime)});i.mouseleave(function(){clearTimeout(f)})}}if(b.botNext!=null){a(b.botNext).click(function(){if(h.queue().length<1){j()}return false})}if(b.botPrev!=null){a(b.botPrev).click(function(){if(h.queue().length<1){g=(e+k-1)%k;d()}return false})}if(b.autoChange==true){c=setInterval(j,b.changeTime);if(b.overStop==true){h.mouseenter(function(){clearInterval(c)});h.mouseleave(function(){c=setInterval(j,b.changeTime)})}}}})})(jQuery);/*图片延迟加载插件*/(function($){$.fn.lazyload=function(options){var settings={threshold:0,failurelimit:0,event:"scroll",effect:"show",container:window};if(options){$.extend(settings,options)}var elements=this;if("scroll"==settings.event){$(settings.container).bind("scroll",function(event){var counter=0;elements.each(function(){if($.abovethetop(this,settings)||$.leftofbegin(this,settings)){}else if(!$.belowthefold(this,settings)&&!$.rightoffold(this,settings)){$(this).trigger("appear")}else{if(counter++>settings.failurelimit){return false}}});var temp=$.grep(elements,function(element){return!element.loaded});elements=$(temp)})}this.each(function(){var self=this;if(undefined==$(self).attr("original")){$(self).attr("original",$(self).attr("src"))}if("scroll"!=settings.event||undefined==$(self).attr("src")||settings.placeholder==$(self).attr("src")||($.abovethetop(self,settings)||$.leftofbegin(self,settings)||$.belowthefold(self,settings)||$.rightoffold(self,settings))){if(settings.placeholder){$(self).attr("src",settings.placeholder)}else{$(self).removeAttr("src")}self.loaded=false}else{self.loaded=true}$(self).one("appear",function(){if(!this.loaded){$("<img />").bind("load",function(){$(self).hide().attr("src",$(self).attr("original"))[settings.effect](settings.effectspeed);self.loaded=true}).attr("src",$(self).attr("original"))}});if("scroll"!=settings.event){$(self).bind(settings.event,function(event){if(!self.loaded){$(self).trigger("appear")}})}});$(settings.container).trigger(settings.event);return this};$.belowthefold=function(element,settings){if(settings.container===undefined||settings.container===window){var fold=$(window).height()+$(window).scrollTop()}else{var fold=$(settings.container).offset().top+$(settings.container).height()}return fold<=$(element).offset().top-settings.threshold};$.rightoffold=function(element,settings){if(settings.container===undefined||settings.container===window){var fold=$(window).width()+$(window).scrollLeft()}else{var fold=$(settings.container).offset().left+$(settings.container).width()}return fold<=$(element).offset().left-settings.threshold};$.abovethetop=function(element,settings){if(settings.container===undefined||settings.container===window){var fold=$(window).scrollTop()}else{var fold=$(settings.container).offset().top}return fold>=$(element).offset().top+settings.threshold+$(element).height()};$.leftofbegin=function(element,settings){if(settings.container===undefined||settings.container===window){var fold=$(window).scrollLeft()}else{var fold=$(settings.container).offset().left}return fold>=$(element).offset().left+settings.threshold+$(element).width()};$.extend($.expr[':'],{"below-the-fold":"$.belowthefold(a, {threshold : 0, container: window})","above-the-fold":"!$.belowthefold(a, {threshold : 0, container: window})","right-of-fold":"$.rightoffold(a, {threshold : 0, container: window})","left-of-fold":"!$.rightoffold(a, {threshold : 0, container: window})"})})(jQuery);/*url*/var i = 0, got = -1, len = document.getElementsByTagName('script').length;while ( i <= len && got == -1){	var js_url = document.getElementsByTagName('script')[i].src,			got = js_url.indexOf('lianyue.js'); i++ ;}var  theme_url = js_url.replace('script/lianyue.js','');/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*/// 延迟加载图片$(function() {    $(".sidebar img,.annex img,.related img,.home_1 newest  img,.home_3 img,.home_2 img,.cat img,.post .content img").lazyload({      effect: "fadeIn"    })});$(window).bind("load", function() { 	var timeout = setTimeout(function() {$("img").trigger("sporty")}, 5000);});/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*/jQuery(document).ready(function($) {/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*/	 //二级导航    $(function() {        $(".menu_head li").hover(function() {			$(this).find(".sub-menu:first").slideDown(120);		},function() {			$(this).find(".sub-menu:first").slideUp(70);		});    }); //二级导航右移    $(function() {        $(".menu_head .sub-menu li").hover(function() {			$(this).find("a:first").stop().animate({ paddingLeft: '20px'},130);		},function() {			$(this).find("a:first").stop().animate({ paddingLeft: '10px'},130);		});    });/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*///幻灯	$('.slide div.changeDiv').soChange({		thumbObj:'.slide .thumb li',		thumbNowClass:'on',slideTime:400,delayTime:150	});//幻灯下面的tab	$('.home_tab ul').soChange({		thumbObj:'.home_tab .nav_tab span',		thumbNowClass:'hover',changeTime:999999,slideTime:0,delayTime:150	});//分类tab	$('.home_cat_tab ul').soChange({		thumbObj:'.home_cat_tab .nav_tab span',		thumbNowClass:'hover',changeTime:999999,slideTime:0,delayTime:150	});/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*///用户	$(function(){		$('#author').focus(			function() {				if($(this).val() == 'Name :') {				$(this).val('');			}		}		).blur(		function(){			if($(this).val() == '') {				$(this).val('Name :');			}		}		);	});//邮箱	$(function(){		$('#email').focus(			function() {				if($(this).val() == 'Email :') {				$(this).val('');			}		}		).blur(		function(){			if($(this).val() == '') {				$(this).val('Email :');			}		}		);	});//网址	$(function(){		$('#url').focus(			function() {				if($(this).val() == 'Website :') {				$(this).val('');			}		}		).blur(		function(){			if($(this).val() == '') {				$(this).val('Website :');			}		}		);	});/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*///图片特效$(function () {	$('.sidebar img,.related img,.home_3 img,.home_2 img,.cat img,.post .content img,.simg img,.media_meta img').hover(		function() {$(this).fadeTo("fast", 0.7);},		function() {$(this).fadeTo("fast", 1);	});});//图片特效	$('.annex .simg ul li a').hover(function(){		$("span", this).stop().animate({top:'70px'},{queue:false,duration:160});	}, function() {		$("span", this).stop().animate({top:'145px'},{queue:false,duration:260});	});/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*/		var edit_mode = '1', // 再編輯模式 ( '1'=開; '0'=不開 )		ajax_php_url = theme_url + 'access/comment.php',		wp_url = js_url.substr(0, theme_url.indexOf('wp-content')),		pic_sb = wp_url + 'wp-admin/images/wpspin_light.gif', // 提交 icon		pic_no = wp_url + 'wp-admin/images/no.png',      // 錯誤 icon		pic_ys = wp_url + 'wp-admin/images/yes.png',     // 成功 icon		txt1 = '<div id="loading"><img src="' + pic_sb + '" style="vertical-align: top;border: 0;" alt=""/> 正在强力插入中...</div>',		txt2 = '<div id="error">#</div>',		txt3 = '"><img src="' + pic_ys + '" style="vertical-align: top;border: 0;" alt=""/> 提交成功',		edt1 = ', 刷新页面之前可以<a rel="nofollow" class="comment-reply-link" href="#edit" onclick=\'return addComment.moveForm("',		edt2 = ')\'>[重新编辑]</a>',		cancel_edit = '[取消编辑]',		edit, num = 1, comm_array=[]; comm_array.push('');jQuery(document).ready(function($) {		$comments = $('#comments-title'); // 評論數的 ID		$cancel = $('#cancel-comment-reply-link'); cancel_text = $cancel.text();		$submit = $('#commentform #submit'); $submit.attr('disabled', false);		$('#comment').after( txt1 + txt2 ); $('#loading').hide(); $('#error').hide();		$body = (window.opera) ? (document.compatMode == "CSS1Compat" ? $('html') : $('body')) : $('html,body');/** submit */$('#commentform').submit(function() {		$('#loading').slideDown();		$submit.attr('disabled', true).fadeTo('slow', 0.5);		if ( edit ) $('#comment').after('<input type="text" name="edit_id" id="edit_id" value="' + edit + '" style="display:none;" />');/** Ajax */	$.ajax( {		url: ajax_php_url,		data: $(this).serialize(),		type: $(this).attr('method'),		error: function(request) {			$('#loading').slideUp();			$('#error').slideDown().html('<img src="' + pic_no + '" style="vertical-align: top; border: 0;" alt=""/> ' + request.responseText);			setTimeout(function() {$submit.attr('disabled', false).fadeTo('slow', 1); $('#error').slideUp();}, 3000);			},		success: function(data) {			$('#loading').hide();			comm_array.push($('#comment').val());			$('textarea').each(function() {this.value = ''});			var t = addComment, cancel = t.I('cancel-comment-reply-link'), temp = t.I('wp-temp-form-div'), respond = t.I(t.respondId), post = t.I('comment_post_ID').value, parent = t.I('comment_parent').value;// comments		if ( ! edit && $comments.length ) {			n = parseInt($comments.text().match(/\d+/));			$comments.text($comments.text().replace( n, n + 1 ));		}// show comment		new_htm = '"id="new_comm_' + num + '"></';				new_htm = ( parent == '0' ) ? ('\n<li style="clear:both;border:0;" class="commentlist' + new_htm + 'li>') : ('\n<ul class="children' + new_htm + 'ul>');		ok_htm = '\n <div class="ajaxtipsdiv"><span class="ajaxtips" id="success_' + num + txt3;		if ( edit_mode == '1' ) {			div_ = (document.body.innerHTML.indexOf('div-comment-') == -1) ? '' : ((document.body.innerHTML.indexOf('li-comment-') == -1) ? 'div-' : '');			ok_htm = ok_htm.concat(edt1, div_, 'comment-', parent, '", "', parent, '", "respond", "', post, '", ', num, edt2);		}		ok_htm += '</span><span></span></div>\n';		$('#respond').before(new_htm);		$('#new_comm_' + num).hide().append(data);		$('#new_comm_' + num + ' li').append(ok_htm);		$('#new_comm_' + num).fadeIn(4000);		$body.animate( { scrollTop: $('#new_comm_' + num).offset().top - 200}, 900);		countdown(); num++ ; edit = ''; $('*').remove('#edit_id');		cancel.style.display = 'none';		cancel.onclick = null;		t.I('comment_parent').value = '0';		if ( temp && respond ) {			temp.parentNode.insertBefore(respond, temp);			temp.parentNode.removeChild(temp)		}		}	}); // end Ajax  return false;}); // end submit/** comment-reply.dev.js */addComment = {	moveForm : function(commId, parentId, respondId, postId, num) {		var t = this, div, comm = t.I(commId), respond = t.I(respondId), cancel = t.I('cancel-comment-reply-link'), parent = t.I('comment_parent'), post = t.I('comment_post_ID');		if ( edit ) exit_prev_edit();		num ? (			t.I('comment').value = comm_array[num],			edit = t.I('new_comm_' + num).innerHTML.match(/(comment-)(\d+)/)[2],			$new_sucs = $('#success_' + num ), $new_sucs.hide(),			$new_comm = $('#new_comm_' + num ), $new_comm.hide(),			$cancel.text(cancel_edit)		) : $cancel.text(cancel_text);		t.respondId = respondId;		postId = postId || false;		if ( !t.I('wp-temp-form-div') ) {			div = document.createElement('div');			div.id = 'wp-temp-form-div';			div.style.display = 'none';			respond.parentNode.insertBefore(div, respond)		}		!comm ? ( 			temp = t.I('wp-temp-form-div'),			t.I('comment_parent').value = '0',			temp.parentNode.insertBefore(respond, temp),			temp.parentNode.removeChild(temp)		) : comm.parentNode.insertBefore(respond, comm.nextSibling);		$body.animate( { scrollTop: $('#respond').offset().top - 180 }, 400);		if ( post && postId ) post.value = postId;		parent.value = parentId;		cancel.style.display = '';		cancel.onclick = function() {			if ( edit ) exit_prev_edit();			var t = addComment, temp = t.I('wp-temp-form-div'), respond = t.I(t.respondId);			t.I('comment_parent').value = '0';			if ( temp && respond ) {				temp.parentNode.insertBefore(respond, temp);				temp.parentNode.removeChild(temp);			}			this.style.display = 'none';			this.onclick = null;			return false;		};		try { t.I('comment').focus(); }		catch(e) {}		return false;	},	I : function(e) {		return document.getElementById(e);	}}; // end addCommentfunction exit_prev_edit() {		$new_comm.show(); $new_sucs.show();		$('textarea').each(function() {this.value = ''});		edit = '';}var wait = 15, submit_val = $submit.val();function countdown() {	if ( wait > 0 ) {		$submit.val(wait); wait--; setTimeout(countdown, 1000);	} else {		$submit.val(submit_val).attr('disabled', false).fadeTo('slow', 1);		wait = 15;  }}});// end jQ/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*/});/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*///图片特效$(function () {	$('.post_single .mood span').hover(		function() {$(this).fadeTo("fast", 0.8);},		function() {$(this).fadeTo("fast", 1);	});});/*提交表态*/function mood_comment(id, mood) {	jQuery.ajax({		type: 'POST',		url: theme_url + 'access/comment.php',		data: 'post_id='+ id +'&mood=' + mood + '&action=mood',		cache: false,		success: function(data) {			jQuery('.mood').html(data)		}	});}/*延迟加载广告*/function find(vid){	var chkid = document.getElementById(vid); 	var chkid_delay = document.getElementById(vid + "_delay"); 	if(chkid != null && chkid_delay != null ){		return true;	} else {		return false;	}}function show(vid){	if (find(vid)) {		document.getElementById(vid).innerHTML=document.getElementById(vid+"_delay").innerHTML;document.getElementById(vid+"_delay").innerHTML="";	}	}/*————————————————————————————————————————————————————我是可爱的分割线by:恋月————————————————————————————————————————————————————*///表情function grin(tag) {	var myField;	tag = ' ' + tag + ' ';	if (document.getElementById('comment') && document.getElementById('comment').type == 'textarea') {		myField = document.getElementById('comment');	} else {		return false;	}	if (document.selection) {		myField.focus();		sel = document.selection.createRange();		sel.text = tag;		myField.focus();	}	else if (myField.selectionStart || myField.selectionStart == '0') {		var startPos = myField.selectionStart;		var endPos = myField.selectionEnd;		var cursorPos = endPos;		myField.value = myField.value.substring(0, startPos)					  + tag					  + myField.value.substring(endPos, myField.value.length);		cursorPos += tag.length;		myField.focus();		myField.selectionStart = cursorPos;		myField.selectionEnd = cursorPos;	}	else {		myField.value += tag;		myField.focus();	}}