(function(window) {
    
    function ClickEvent() {
        var that = this;
        var ORINGINAL_URL = "original";
        
        function addEvent(o, t, f){
            if (o.addEventListener) {
                o.addEventListener(t, f, false);
            } else {
                if (o.attachEvent) {
                    o.attachEvent('on' + t, function() {
                        f.apply(o, arguments);
                    });
                } else {
                    o['on' + t] = f;
                }
            }
        }
        
        function getMousePoint(e) {
            e = e || window.event;
            
            var point = {
                x: 0,
                y: 0
            };
            
            if (e.type == "touchstart" && e.touches.length > 0) {
                var touch = e.touches[0];
                return {
                    x: touch.pageX,
                    y: touch.pageY
                };
            }
            
            if (e.pageX || e.pageY) {
                return {
                    x: e.pageX,
                    y: e.pageY
                };
            }
            
            if (typeof window.pageXOffset != "undefined") {
                point.x = window.pageXOffset;
                point.y = window.pageYOffset;
            } else if (typeof document.documentElement != "undefined") {
                point.x = document.documentElement.scrollLeft;
                point.y = document.documentElement.scrollTop;
            } else if (typeof document.body != "undefined") {
                point.x = document.body.scrollLeft;
                point.y = document.body.scrollTop;
            }
            
            point.x += e.clientX;
            point.y += e.clientY;
            
            return point;
        }
        
        function getValueFromString(str, key) {
            var matches = str.match(new RegExp("(?:[?|&])" + key + "=([^&]+)"));
            if (matches == null) {
                return "";
            }
            
            return matches[1];
        }
        
        function convertToString(value) {
            if (typeof value == "number") {
                value = (value).toString();
            }
            
            return value;
        }
        
        function shuffle(x, y, t) {
            t = convertToString(t);
            var tLen = t.length;
            x = Math.round(x) + t.substring(tLen - 3);
            y = Math.round(y) + t.substring(tLen - 4);
           
            var str = x.length + x + y,
                strLen = str.length,
                reverseT = t.split("").reverse().join("");
            
            var left = [], right = [];
            
            for (var i = 0; i < strLen; i++) {
                var intStr = str.charCodeAt(i) - "0".charCodeAt(0) + 3;
                var intT = i < reverseT.length ? reverseT.charCodeAt(i) - "0".charCodeAt(0) : 0;
                left.push(String.fromCharCode("a".charCodeAt(0) + intStr + intT));
                right.push(String.fromCharCode("z".charCodeAt(0) - intStr - intT));
            }

            return left.join("") + right.join("");
        }
        
        this.shuffle = function(e, redirectUrl) {
            var point = getMousePoint(e);
            var t = getValueFromString(decodeURIComponent(redirectUrl), "t");
            return shuffle(point.x, point.y, t);
        };
        
        this.register = function(elem, options) {
            addEvent(elem, "mousedown", function(e) {
                var url = this.getAttribute("href");
                var clickUrl = this.getAttribute("clickUrl"),
                    originalUrl = this.getAttribute(ORINGINAL_URL);
                
                if (!originalUrl) {
                    this.setAttribute(ORINGINAL_URL, url);
                    originalUrl = url;
                }
                
                if (clickUrl) { // for ad click
                    clickUrl += "&oc=" + that.shuffle(e, clickUrl);
                } else if (options["redirectUrl"]) { // for item with redirect click
                    clickUrl = options["redirectUrl"] + "&url=" + encodeURIComponent(originalUrl) + "&ts=" + new Date().getTime();
                } else { // !! do not suggest
                    clickUrl = originalUrl;
                }
                
                this.setAttribute("href", clickUrl);
                
                options["mousedown"] && options["mousedown"]();
            });
            
            addEvent(elem, "mouseup", function() {
                var link = this;
                
                setTimeout(function() {
                    var originalUrl = link.getAttribute(ORINGINAL_URL);
                    
                    if (originalUrl) {
                        link.setAttribute("href", link.getAttribute(ORINGINAL_URL));
                        options["mouseup"] && options["mouseup"]();
                    }
                }, 50);
            });
        };
    }
    
    window.ClickEvent = new ClickEvent();
})(window);