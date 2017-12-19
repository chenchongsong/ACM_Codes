// leanote blog share & comment
var C = {
	info: null,
	noteId: noteId,
	preLikeNum: preLikeNum,
	commentNum: commentNum,
	likeBtnO: $("#likeBtn"),
	likeNumO: $("#likeNum"),
	tLikersO: $("#tLikers"),
	likersO: $("#likers"),
	tCommentsO: $("#tComments"),
	commentsO: $("#comments"),
	
	commentBtnO: $("#commentBtn"),
	
	commentsLoadingO: $(".comments-loading"),
	commentsMoreO: $(".comments-more"),
	
	commentBoxO: $(".comment-box"),
	init: function() {
		var self = this;
		if(blogInfo.OpenComment && blogInfo.CommentType != "disqus") {
			self.initLikesAndComments();
		} else {
			self.initLikes();
		}
		self.initEvent();
		self.incReadNum();
	},
	
	// 博客的统计信息
	getPostStat: function() {
	},
	// 增加阅读量
	incReadNum: function() {
		incReadNum(self.noteId);
	},
	initLikes: function() {
		var self = this;
		getLikes(self.noteId, function(ret) {
			if(reIsOk(ret)) {
				ret = ret.Item;
				self.info = ret;
				self.toggleLikeBtnActive();
				self.renderLikers();
				self.visitUserInfo = self.info.visitUserInfo || {};
			}
		});
	},
	initLikesAndComments: function() {
		var self = this;
		getLikesAndComments(self.noteId, function(ret) {
			if(reIsOk(ret)) {
				ret = ret.Item;
				self.info = ret;
				self.toggleLikeBtnActive();
				self.renderLikers();
				// 是否需要renderComments?
				self.info.commentUserInfo = self.info.commentUserInfo || {};
				self.visitUserInfo = self.info.visitUserInfo || {};
				// 为了防止第一条评论找不到用户信息情况
				if(self.visitUserInfo.UserId) {
					self.info.commentUserInfo[self.visitUserInfo.UserId] = self.visitUserInfo;
				}
				self.renderComments();
				
				// 之前是隐藏的, 取消之
				self.commentBoxO.removeClass("hide");
				self.commentsLoadingO.addClass("hide");
				if(self.info.pageInfo.TotalPage > self.info.pageInfo.CurPage) {
					self.commentsMoreO.removeClass("hide");
					self.initMoreComments();
				}
				
				// 是否已经登录?
				if(self.visitUserInfo.UserId) {
					$("#commentForm").removeClass("hide");
					$("#visitUserLogo").attr("src", self.visitUserInfo.Logo);
				} else {
					$("#noLoginContainer").removeClass("hide");
				}
			}
			       	    	// taken from mo.js demos
	function isIOSSafari() {
		var userAgent;
		userAgent = window.navigator.userAgent;
		return userAgent.match(/iPad/i) || userAgent.match(/iPhone/i);
	};

	// taken from mo.js demos
	function isTouch() {
		var isIETouch;
		isIETouch = navigator.maxTouchPoints > 0 || navigator.msMaxTouchPoints > 0;
		return [].indexOf.call(window, 'ontouchstart') >= 0 || isIETouch;
	};
	
	// taken from mo.js demos
	var isIOS = isIOSSafari(),
		clickHandler = isIOS || isTouch() ? 'touchstart' : 'click';

	function extend( a, b ) {
		for( var key in b ) { 
			if( b.hasOwnProperty( key ) ) {
				a[key] = b[key];
			}
		}
		return a;
	}

	function Animocon(el, options) {
		this.el = el;
		this.options = extend( {}, this.options );
		extend( this.options, options );

		this.checked = false;

		this.timeline = new mojs.Timeline();
		
		for(var i = 0, len = this.options.tweens.length; i < len; ++i) {
			this.timeline.add(this.options.tweens[i]);
		}

		var selfs = this;
		this.el.addEventListener(clickHandler, function() {
		        if(!self.visitUserInfo.UserId) {
		        }else{
		           	 if(! $(selfs.el).hasClass("active")) {
        			    selfs.options.onCheck();
        				selfs.timeline.replay();
        			}
        			else {
        				selfs.options.onUnCheck();
        			} 
		        }		
			selfs.checked = !self.checked;
		});
	}

	Animocon.prototype.options = {
		tweens : [
			new mojs.Burst({})
		],
		onCheck : function() { return false; },
		onUnCheck : function() { return false; }
	};

	// grid items:
	var items = [].slice.call(document.querySelectorAll('ol.grids > .grids__item'));

	function init() {


		/* Icon 3 */
		var el3 = items[0].querySelector('button.icobutton'), el3span = el3.querySelector('span');
		new Animocon(el3, {
			tweens : [
				// burst animation
				new mojs.Burst({
					parent: 		el3,
					count: 			6,
					radius: 		{40:90},
					children: {
						fill: 			[ '#FF6666', '#99CC99', '#8AAEDE', '#8ADEAD', '#DEC58A', '#8AD1DE' ],
						opacity: 		0.6,
						scale: 			1,
						radius:     { 7: 0 },
						duration: 	1500,
						delay: 			300,
						easing: 		mojs.easing.bezier(0.1, 1, 0.3, 1)
					}
				}),
				// ring animation
				new mojs.Shape({
					parent: 			el3,
					type: 				'circle',
					scale:        { 0: 1 },
					radius: 			50,
					fill: 				'transparent',
					stroke: 			'#FF6666',
					strokeWidth: 	{35:0},
					opacity: 			0.6,
					duration:  		750,
					easing: 			mojs.easing.bezier(0, 1, 0.5, 1)
				}),
				// icon scale animation
				new mojs.Tween({
					duration : 1100,
					onUpdate: function(progress) {
						if(progress > 0.3) {
							var elasticOutProgress = mojs.easing.elastic.out(1.43*progress-0.43);
							el3span.style.WebkitTransform = el3span.style.transform = 'scale3d(' + elasticOutProgress + ',' + elasticOutProgress + ',1)';
						}
						else {
							el3span.style.WebkitTransform = el3span.style.transform = 'scale3d(0,0,1)';
						}
					}
				})
			],
			onCheck : function() {
				el3.style.color = '#FF6666';
			},
			onUnCheck : function() {
				el3.style.color = '#C0C1C3';	
			}
		});
		/* Icon 3 */
		
		// bursts when hovering the mo.js link
		var molinkEl = document.querySelector('.special-link'),
			moTimeline = new mojs.Timeline(),
			moburst1 = new mojs.Burst({
				parent: 			molinkEl,
				count: 				6,
				left: 				'0%',
				top:  				'-50%',
				radius: 			{0:60},
				children: {
					fill : 			[ '#988ADE', '#DE8AA0', '#8AAEDE', '#8ADEAD', '#DEC58A', '#8AD1DE' ],
					duration: 	1300,
					easing: 		mojs.easing.bezier(0.1, 1, 0.3, 1)
				}
			}),
			moburst2 = new mojs.Burst({
				parent: 	molinkEl,
				left: '-100%', top: '-20%',
				count: 		14,
				radius: 		{0:120},
				children: {
					fill: 			[ '#988ADE', '#DE8AA0', '#8AAEDE', '#8ADEAD', '#DEC58A', '#8AD1DE' ],
					duration: 	1600,
					delay: 			100,
					easing: 		mojs.easing.bezier(0.1, 1, 0.3, 1)
				}
			}),
			moburst3 = new mojs.Burst({
				parent: 			molinkEl,
				left: '130%', top: '-70%',
				count: 				8,
				radius: 			{0:90},
				children: {
					fill: 			[ '#988ADE', '#DE8AA0', '#8AAEDE', '#8ADEAD', '#DEC58A', '#8AD1DE' ],
					duration: 	1500,
					delay: 			200,
					easing: 		mojs.easing.bezier(0.1, 1, 0.3, 1)
				}
			}),
			moburst4 = new mojs.Burst({
				parent: molinkEl,
				left: '-20%', top: '-150%',
				count: 		14,
				radius: 	{0:60},
				children: {
					fill: 			[ '#988ADE', '#DE8AA0', '#8AAEDE', '#8ADEAD', '#DEC58A', '#8AD1DE' ],
					duration: 	2000,
					delay: 			300,
					easing: 		mojs.easing.bezier(0.1, 1, 0.3, 1)
				}
			}),
			moburst5 = new mojs.Burst({
				parent: 	molinkEl,
				count: 		12,
				left: '30%', top: '-100%',
				radius: 		{0:60},
				children: {
					fill: 			[ '#988ADE', '#DE8AA0', '#8AAEDE', '#8ADEAD', '#DEC58A', '#8AD1DE' ],
					duration: 	1400,
					delay: 			400,
					easing: 		mojs.easing.bezier(0.1, 1, 0.3, 1)
				}
			});

		moTimeline.add(moburst1, moburst2, moburst3, moburst4, moburst5);
	    }
	init(); 
		});
	},
	initMoreComments: function() {
		var self = this;
		self.commentsMoreO.find("a").click(function(){ 
			if(self.info.pageInfo.TotalPage > self.info.pageInfo.CurPage) {
				self.commentsMoreO.addClass("hide");
				self.commentsLoadingO.removeClass("hide");
				getComments(self.noteId, self.info.pageInfo.CurPage+1, function(ret) {
					var pageInfo = ret.pageInfo;
					var comments = ret.comments;
					var commentUserInfo = ret.commentUserInfo;
					
					$.extend(self.info.commentUserInfo, commentUserInfo);
					
					// 渲染之
					for(var i in comments) {
						var comment = comments[i];
						comment = self.parseComment(comment);
					}
					var html = self.tCommentsO.render({comments: comments, visitUserInfo: self.visitUserInfo});
					self.commentsO.append(html);
					
					self.info.pageInfo = pageInfo;
					
					if(self.info.pageInfo.TotalPage > self.info.pageInfo.CurPage) {
						self.commentsMoreO.removeClass("hide");
					} else {
						self.commentsMoreO.addClass("hide");
					}
					
					self.commentsLoadingO.addClass("hide");
				});
			}
		});
	},
	addCommentRender: function(comment){
		var self = this;
		comment = self.parseComment(comment);
		var html = self.tCommentsO.render({comments: [comment], visitUserInfo: self.visitUserInfo});
		self.commentsO.prepend(html);
		var li = self.commentsO.find("li").eq(0);
		li.hide();
		li.show(500);
		li.addClass("item-highlight");
		setTimeout(function() {
			li.removeClass("item-highlight");
		}, 2000);
	},
	parseComment: function(comment) {
		var self = this;
		var authorUserId = blogInfo.UserId;
		commentUserInfo = self.info.commentUserInfo;
		comment.UserInfo = commentUserInfo[comment.UserId];
		// 是作者自己
		if(self.visitUserInfo.UserId == authorUserId) {
			comment.IsMyNote = true;
		}
		if(comment.UserId == authorUserId) {
			comment.IsAuthorComment = true;
		}
		if(comment.UserId == self.visitUserInfo.UserId) {
			comment.IsMyComment = true;
		}
		// 不是回复自己
		if(comment.ToUserId && comment.ToUserId != comment.UserId) { 
			comment.ToUserInfo = commentUserInfo[comment.ToUserId];
			if(comment.ToUserInfo.UserId == authorUserId) {
				comment.ToUserIsAuthor = true;
			}
		}
		comment.PublishDate = new Date(comment.CreatedTime).Format('yyyy-MM-dd hh:mm:ss');
		return comment;
	},
	// 渲染评论
	renderComments: function() {
		var self = this;
		var comments = self.info.comments || [];
		if(comments.length == 0) {
			return;
		}
		
		// 整理数据
		// 回复谁, 是否是作者?
		// 回复日期, 几天前, 刚刚
		for(var i in comments) {
			var comment = comments[i];
			comment = self.parseComment(comment);
		}
		var html = self.tCommentsO.render({comments: comments, visitUserInfo: self.visitUserInfo});
		self.commentsO.html(html);
	},
	
	// 重新渲染likers
	reRenderLikers: function(addMe) {
		var self = this;
		var likedUsers = self.info.likedUsers || [];
		for(var i = 0; i < likedUsers.length; ++i) {
			var user = likedUsers[i];
			if(user.UserId == self.visitUserInfo.UserId) {
				likedUsers.splice(i, 1);
				break;
			}
		}
		if(addMe) {
			likedUsers = [self.visitUserInfo].concat(likedUsers);
			self.info.likedUsers = likedUsers;
		}
		self.renderLikers();
	},
	renderLikers: function() {
		var self = this;
		var users = self.info.likedUsers || [];
		var html = self.tLikersO.render({users: users});
		self.likersO.html(html);
	},
	toggleLikeBtnActive: function() {
		var self = this;
		if(self.info.isILikeIt) {
			self.likeBtnO.addClass("active");
		} else {
			self.likeBtnO.removeClass("active");
		}
	},
	commentNumO: $("#commentNum"),
	bindCommentNum: function(fix) {
		var self = this;
		self.commentNum += fix;
		self.commentNumO.text(self.commentNum);
	},
	initEvent: function() {
		var self = this;
		
		// like or not
		self.likeBtnO.click(function() {
			if(!self.visitUserInfo.UserId) {
				needLogin();
				return;
			}
			likePost(noteId, function(ret) {
				if(ret.Ok) {
					// like
					if(ret.Item) {
						var num = self.preLikeNum+1;
					} else {
						var num = self.preLikeNum-1;
					}
					self.preLikeNum = num >= 0 ? num : 0;
					self.likeNumO.text(self.preLikeNum);
					self.info.isILikeIt = ret.Item;
					self.toggleLikeBtnActive();
					
					// 重新render likers
					// 我是否在列表中
					self.reRenderLikers(ret.Item);
				}
			});
		});
		
		// 显示回复回复
		$("#comments").on("click", ".comment-reply", function() {
			var form = $(this).closest("li").find("form");
			if(form.is(":hidden")) {
				form.show();
				form.find("textarea").focus();
			} else {
				form.hide();
			}
		});
		$("#comments").on("click", ".reply-cancel", function() {
			$(this).closest("form").hide();
		});
		
		// 回复
		$(".comment-box").on("click", ".reply-comment-btn", function(e) {
			e.preventDefault();
			var commentId = $(this).data("comment-id");
			var $form = $(this).closest("form");
			var $content = $form.find("textarea");
			var content = $.trim($content.val());
			if(!content) {
				$content.focus();
				return;
			}
			var t = $(this);
			t.button("loading");
			var data = {noteId: self.noteId, toCommentId: commentId, content: content};
			commentPost(self.noteId, commentId, content, function(ret) {
				t.button("reset");
				$content.val("");
				self.bindCommentNum(1);
				if(commentId) {
					$form.hide();
				}
				
				if(commentId) {
					scrollToTarget("#comments", -200);
				}
				
				// 添加一个
				self.addCommentRender(ret.Item);
			});
		});
		
		// 删除
		$(".comment-box").on("click", ".comment-trash", function(e) {
			var commentId = $(this).parent().data("comment-id");
			var t = this;
		try {
			    swal({    
			        title: "",    
			        text: "Confirm to delete this comment?",    
			        type: "warning",   
			        showCancelButton: true,  
			        allowEscapeKey : true,
			        confirmButtonColor: "#D18F80",   
			        confirmButtonText: "confirm",    
			        closeOnConfirm: false 
			        
			    }, 
			        function(){
			            deleteComment(noteId, commentId, function(ret) {
							if(ret.Ok) {
								var li = $(t).closest("li");
								li.hide(500); // remove();
								setTimeout(function() {
									li.remove();
								}, 300);
								
								self.bindCommentNum(-1);
							}
						});
			            swal({
			                title:'',
			                text:'Deleted successfully',
			                type:'success',
			                confirmButtonColor: "#D18F80",   
			                confirmButtonText: "Okay"
			            });  
			            
			        });
			} catch(e) {}
		});
		
		// 点zan
		$(".comment-box").on("click", ".comment-like", function(e) {
			var commentId = $(this).parent().data("comment-id");
			var t = this;
			
			likeComment(commentId, function(re) {
				if(re.Ok) {
					var ret = re.Item;
					if(ret.Num <= 0) {
						$(t).parent().find(".like-num").addClass("hide");
					} else {
						$(t).parent().find(".like-num").removeClass("hide");
						$(t).parent().find(".like-num-i").text(ret.Num)
					}
					if(ret.IsILikeIt) {
						var ever = $(t).find(".like-text").text();
						if(ever == "赞") {
							$(t).find(".like-text").text("取消赞");
						} else {
							$(t).find(".like-text").text("Unlike");
						}
					} else {
						var ever = $(t).find(".like-text").text();
						if(ever == "取消赞") {
							$(t).find(".like-text").text("赞");
						} else {
							$(t).find(".like-text").text("Like");
						}
					}
				}
			});
		});
		self.initShare();
	},
	weixinQRCodeO: $("#weixinQRCode"),
	initShare: function() {
		var self = this;
		$(".btn-weixin").click(function() {
			if(!self.weixinQRCodeO.html()) {
				self.weixinQRCodeO.qrcode(location.href);
			}
			BootstrapDialog.show({
	            title: "Open Wechat to scan the code",
	            message: self.weixinQRCodeO
	        });
		});
		
		$(".btn-share").click(function() {
			var $this = $(this);
			var map = {"btn-weibo": shareSinaWeibo, "tencent-weibo": shareTencentWeibo, "qq": shareQQ, "renren": shareRenRen};
			for(var i in map) {
				if($this.hasClass(i)) {
					map[i](self.noteId, document.title);
					break;
				}	
			}
		});
	},
}
$(function() {
	C.init();
});