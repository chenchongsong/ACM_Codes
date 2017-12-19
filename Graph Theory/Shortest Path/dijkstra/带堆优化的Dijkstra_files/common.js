Date.prototype.Format = function (fmt) {
    var o = {
        "M+": this.getMonth() + 1,
        "d+": this.getDate(),
        "h+": this.getHours(),
        "m+": this.getMinutes(),
        "s+": this.getSeconds(),
        "q+": Math.floor((this.getMonth() + 3) / 3),
        "S": this.getMilliseconds()
    };
    if (/(y+)/.test(fmt)) {
        fmt = fmt.replace(RegExp.$1, (this.getFullYear() + "").substr(4 - RegExp.$1.length))
    }
    for (var k in o) {
        if (new RegExp("(" + k + ")").test(fmt)) {
            fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)))
        }
    }
    return fmt
}

function reIsOk(re) {
    return re && typeof re == "object" && re.Ok
}

function showAlert(id, msg, type, id2Focus) {
    $(id).html(msg).removeClass("alert-danger").removeClass("alert-success").removeClass("alert-warning").addClass("alert-" + type).show();
    if (id2Focus) {
        $(id2Focus).focus()
    }
}

function hideAlert(id, timeout) {
    if (timeout) {
        setTimeout(function () {
            $(id).hide()
        }, timeout)
    } else {
        $(id).hide()
    }
}

function ajaxGet(url, param, func) {
    $.get(url, param, func)
}

function ajaxPost(url, param, func) {
    $.post(url, param, func)
}

function ajaxGetP(url, param, callback) {
    ajaxP("GET", url, param, callback)
}

function ajaxPostP(url, param, callback) {
    ajaxP("POST", url, param, callback)
}

function ajaxP(method, url, param, callback) {
    param = param || {};
    callback = callback || function () {};
    $.ajax({
        dataType: "jsonp",
        url: url,
        type: method,
        data: param,
        jsonp: "callback",
        jsonpCallback: "jsonpCallback",
        success: callback
    })
}
var windowParam = 'width=700, height=580, top=180, left=320, toolbar=no, menubar=no, scrollbars=no, location=yes, resizable=no, status=no';

function getShareUrl() {
    return location.href
}

function getShareTitle(title) {
    return encodeURI(title + " (from https://leanote.com)")
}

function shareSinaWeibo(noteId, title, pic) {
    var url = "http://service.weibo.com/share/share.php?title=" + getShareTitle(title) + "&url=" + getShareUrl(noteId);
    window.open(url, 'Share', windowParam)
}

function shareTencentWeibo(noteId, title, pic) {
    var _appkey = '801542571';
    var url = "http://share.v.t.qq.com/index.php?c=share&a=index&appkey=" + _appkey + "&title=" + getShareTitle(title) + "&url=" + getShareUrl(noteId) + "&pic=" + pic;
    window.open(url, 'Share', windowParam)
}

function shareQQ(noteId, title, pic) {
    var url = 'http://sns.qzone.qq.com/cgi-bin/qzshare/cgi_qzshare_onekey?url=' + getShareUrl(noteId) + '&title=' + title + '&pics=' + pic;
    window.open(url, 'Share', windowParam)
}

function shareRenRen(noteId, title, pic) {
    var url = 'http://widget.renren.com/dialog/share?resourceUrl=' + getShareUrl(noteId) + '&srcUrl=' + getShareUrl(noteId) + '&title=' + getShareTitle(title) + '&pic=' + pic;
    window.open(url, 'Share', windowParam)
}

function shareTwitter(noteId, title, pic) {
    var url = 'https://twitter.com/intent/tweet?text=' + getShareTitle(title) + '&pic=' + pic;
    window.open(url, 'Share', windowParam)
}

function shareFacebook(noteId, title, pic) {
    var url = ' http://www.facebook.com/sharer.php?t=' + getShareTitle(title) + '&pic=' + pic;
    window.open(url, 'Share', windowParam)
}

function goNowToDatetime(goNow) {
    if (!goNow) {
        return ""
    }
    return goNow.substr(0, 10) + " " + goNow.substr(11, 8)
}

function goNowToDate(goNow) {
    if (!goNow) {
        return ""
    }
    var str = goNow.substr(0, 10) + " " + goNow.substr(11, 8);
    var tempStrs = str.split(" ");
    var dateStrs = tempStrs[0].split("-");
    var year = parseInt(dateStrs[0], 10);
    var month = parseInt(dateStrs[1], 10) - 1;
    var day = parseInt(dateStrs[2], 10);
    var timeStrs = tempStrs[1].split(":");
    var hour = parseInt(timeStrs[0], 10);
    var minute = parseInt(timeStrs[1], 10) - 1;
    var second = parseInt(timeStrs[2], 10);
    var date = new Date(year, month, day, hour, minute, second);
    return date
}
var diff = {
    minute: 1000 * 60,
    hour: 1000 * 60 * 60,
    day: 1000 * 60 * 60 * 24,
    halfamonth: 1000 * 60 * 60 * 24 * 15,
    month: 1000 * 60 * 60 * 24 * 30
}

function getDateDiff(dateTimeStamp) {
    var now = new Date().getTime();
    var diffValue = now - dateTimeStamp;
    if (diffValue < 0) {
        return ""
    }
    var monthC = diffValue / diff.month;
    var weekC = diffValue / (7 * diff.day);
    var dayC = diffValue / diff.day;
    var hourC = diffValue / diff.hour;
    var minC = parseInt(diffValue / diff.minute);
    if (monthC >= 1) {
        result = parseInt(monthC) + " month ago"
    } else if (weekC >= 1) {
        result = parseInt(weekC) + " weeks ago"
    } else if (dayC >= 1) {
        result = parseInt(dayC) + " days ago"
    } else if (hourC >= 1) {
        result = parseInt(hourC) + " hours ago"
    } else if (minC > 1) {
        result = minC + " minutes ago"
    } else {
        result = "Just now"
    }
    return result
}

function weixin() {
    var local = window.location.href;
    var title = $.trim($(".title").text());
    var desc = $.trim($("#desc").text());
    var imgUrl = $("#content img").eq(0).attr('src');
    window.shareData = {
        "imgUrl": imgUrl,
        "timeLineLink": local,
        "sendFriendLink": local,
        "weiboLink": local,
        "tTitle": title,
        "tContent": desc,
        "fTitle": title,
        "fContent": desc,
        "wContent": desc
    };
    document.addEventListener('WeixinJSBridgeReady', function onBridgeReady() {
        WeixinJSBridge.on('menu:share:appmessage', function (argv) {
            WeixinJSBridge.invoke('sendAppMessage', {
                "img_url": window.shareData.imgUrl,
                "img_width": "200",
                "link": window.shareData.sendFriendLink,
                "desc": window.shareData.fContent,
                "title": window.shareData.fTitle
            }, function (res) {
                hs_guide('none');
                _report('send_msg', res.err_msg)
            })
        });
        WeixinJSBridge.on('menu:share:timeline', function (argv) {
            WeixinJSBridge.invoke('shareTimeline', {
                "img_url": window.shareData.imgUrl,
                "img_width": "200",
                "link": window.shareData.timeLineLink,
                "desc": window.shareData.tContent,
                "title": window.shareData.tTitle
            }, function (res) {
                hs_guide('none');
                _report('timeline', res.err_msg)
            })
        });
        WeixinJSBridge.on('menu:share:weibo', function (argv) {
            WeixinJSBridge.invoke('shareWeibo', {
                "content": window.shareData.wContent,
                "url": window.shareData.weiboLink,
            }, function (res) {
                hs_guide('none');
                _report('weibo', res.err_msg)
            })
        })
    }, false)
}

function scrollTo(self, tagName, text) {
    var iframe = $("#content");
    location.href = "#" + text;
    var target = iframe.find(tagName + ":contains(" + text + ")");
    var navs = $('#blogNavContent [data-a="' + tagName + '-' + encodeURI(text) + '"]');
    var len = navs.size();
    for (var i = 0; i < len; ++i) {
        if (navs[i] == self) {
            break
        }
    }
    if (target.size() >= i + 1) {
        target = target.eq(i);
        var top = target.offset().top;
        if (LEA.isMobile) {
            top -= 50
        }
        var nowTop = $(document).scrollTop();
        $('html,body').animate({
            scrollTop: top
        }, 200);
        return
    }
}

function genNav() {
    var $con = $("#content");
    var html = $con.html();
    var tree = [];
    var hs = $con.find("h1,h2,h3,h4,h5,h6").toArray();
    $con.find("h1,h2,h3,h4,h5,h6").each(function () {
        var $h = $(this);
        var value = $h.text();
        var insert = "<a name='" + value + "'></a>";
        $h.before(insert)
    });
    var titles = '<ul>';
    for (var i = 0; i < hs.length; ++i) {
        var text = $(hs[i]).text();
        var tagName = hs[i].tagName.toLowerCase();
        titles += '<li class="nav-' + tagName + '"><a data-a="' + tagName + '-' + encodeURI(text) + '" onclick="scrollTo(this, \'' + tagName + '\', \'' + text + '\')">' + text + '</a></li>'
    }
    titles += "</ul>";
    $("#blogNavContent").html(titles);
    if (!hs.length) {
        $("#blogNav").hide();
        return false
    }
    return true
}

function initNav() {
    var hasNav = genNav();
    if (!hasNav) {
        return
    }
    var $title = $(".title");
    var titlePos = $title.offset();
    var top = titlePos.top + 10;
    if (LEA.isMobile) {
        top += 30
    }
    if (top < 0) {
        top = 10
    }
    var left = $title.width() + titlePos.left - 100;
    $("#blogNav").css("top", top).css("left", left);
    $("#blogNav").show();
    $("#blogNavNav").click(function () {
        var $o = $("#blogNavContent");
        if ($o.is(":hidden")) {
            $o.show()
        } else {
            $o.hide()
        }
    });
    var $d = $(document);

    function reNav() {
        var vtop = $d.scrollTop();
        if (vtop <= top) {
            $("#blogNav").css("top", top - vtop)
        } else {
            if (LEA.isMobile) {
                $("#blogNav").css("top", 50)
            } else {
                $("#blogNav").css("top", 10)
            }
        }
    }
    reNav();
    $(window).scroll(reNav)
}

function goLogin() {
    var loginUrl = siteUrl + '/login?from=' + encodeURI(location.href);
    location.href = loginUrl
}

function goRegister() {
    var registerUrl = siteUrl + '/register?from=' + encodeURI(location.href);
    location.href = registerUrl
}

function needLogin() {
    if (typeof visitUserInfo == "undefined" || !visitUserInfo || !visitUserInfo.UserId) {
        var loginUrl = siteUrl + '/login?from=' + encodeURI(location.href);
        var registerUrl = siteUrl + '/register?from=' + encodeURI(location.href);
        var textVal = '<a href="' + loginUrl + '" style="color:rgb(66, 185, 131) !important;font-weight:500;">Sign in</a> to leave a comment. <br/>No Leanote account ? <a href="' + registerUrl + '" style="color:rgb(66, 185, 131) !important;font-weight:500;">Sign up now</a>.';
        try {
            swal({
                title: "",
                text: textVal,
                html: true,
                allowEscapeKey: true,
                allowOutsideClick: true,
                confirmButtonText: 'No thanks',
                confirmButtonColor: '#E6B1A3'
            })
        } catch (e) {}
        return true
    }
    return false
}

function scrollToTarget(t, fixed) {
    if (!fixed) {
        fixed = 0
    }
    var $t = $(t);
    var targetOffset = $t.offset().top + fixed;
    $('html,body').animate({
        scrollTop: targetOffset
    }, 300)
}

function getCurVisitUserInfo() {}

function incReadNum(noteId) {
    ajaxGet(getCurHostUrl() + "/blog/incReadNum", {
        noteId: noteId
    });
}

function getCurHostUrl() {
    return "//" + location.host
}

function getLeanoteUrl() {
    return siteUrl || "http://leanote.com"
}

function getPostStat(noteId, callback) {
    ajaxGet(getCurHostUrl() + "/blog/getPostStat", {
        noteId: noteId
    }, callback)
}

function getLikes(noteId, callback) {
    ajaxGetP(getLeanoteUrl() + "/blog/getLikes", {
        noteId: noteId
    }, callback)
}

function getLikesAndComments(noteId, callback) {
    ajaxGetP(getLeanoteUrl() + "/blog/getLikesAndComments", {
        noteId: noteId
    }, callback)
}

function getComments(noteId, page, callback) {
    ajaxGetP(getLeanoteUrl() + "/blog/getComments", {
        noteId: noteId,
        page: page
    }, callback)
}

function likePost(noteId, callback) {
    ajaxPostP(getLeanoteUrl() + "/blog/likePost", {
        noteId: noteId
    }, callback)
}

function commentPost(noteId, commentId, content, callback) {
    var data = {
        noteId: self.noteId,
        toCommentId: commentId,
        content: content
    };
    ajaxPostP(getLeanoteUrl() + "/blog/commentPost", data, callback)
}

function deleteComment(noteId, commentId, callback) {
    ajaxPostP(getLeanoteUrl() + "/blog/deleteComment", {
        noteId: noteId,
        commentId: commentId
    }, callback)
}

function likeComment(commentId, callback) {
    ajaxPostP(getLeanoteUrl() + "/blog/likeComment", {
        commentId: commentId
    }, callback)
}
var LEA = {
    isMobile: false
};

function isMobile() {
    var u = navigator.userAgent;
    LEA.isMobile = false;
    LEA.isMobile = /Mobile|Android|iPhone/i.test(u);
    if (!LEA.isMobile && $(document).width() <= 600) {
        LEA.isMobile = true
    }
}
$(function () {
    isMobile()
});