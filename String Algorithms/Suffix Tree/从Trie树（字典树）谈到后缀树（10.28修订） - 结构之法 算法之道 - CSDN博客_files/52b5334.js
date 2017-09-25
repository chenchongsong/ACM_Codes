(function(){
    var a = function () {};
    a.u = [{"l":"http:\/\/ads.csdn.net\/skip.php?subject=BWxaclxjDGgAJFIOVT4MOFM6VmJZOgIxUHYFZFVjAiZRMgkhAC8AaAMmA2UHWg00U2NSbgNlXm4DNQAmU2hSZAVmWmFcWAxkADJSbFVlDGtTM1ZgWSgCcFA8BWRVaQIPUScJJQBmADQDZgMmB3ENJFN3UjYDaV4q","r":0.15},{"l":"http:\/\/ads.csdn.net\/skip.php?subject=B24IIFtkVzNVcQhUVT4HM1Q9ADRQPwM4VHICY1NlU3dUNwoiWXYEbAciAmRWCw00V2dRbVE3UGJTZVB2CTJabAdkCDNbX1c\/VWcINlVlB25UOAAxUCEDcVQ4AmNTb1NeVCIKJlk\/BDQHYAIxVnINKVd6USBRY1BvUyU=","r":0.31},{"l":"http:\/\/ads.csdn.net\/skip.php?subject=Vz5ddQs0AmZRdVcLBm0BNQZvUmZXOV5oVHILagM1ByMMbw8nDiFTOwEkUjRSDwI7VGRXa1cxBTUHMFZwADtWYFc0XWYLDwJqUWNXaQY2AWgGZlJrVyZeLFQ4C2oDPwcKDHoPIw5oU2MBYFJhUnYCJlR5VyZXZQU6B3E=","r":0.47},{"l":"http:\/\/ads.csdn.net\/skip.php?subject=AGkKIgwzB2MBJQRYUjkNOQBpDTlVO1RiXHoBYAE3BSFXNFpyXXINZVZzBGJTDgw1VWUNMQVjVGdcbQAmATpWYABjCjEMCAdvATMEOlJiDWQAYQ08VSRUJlwwAWABPQUIVyFadl07DT1WMQQ3U3cMKFV4DXwFN1RrXCo=","r":0.31},{"l":"http:\/\/ads.csdn.net\/skip.php?subject=DGUMJA8wBWEGIglVAWoBNVI7VmIHZFVuU3VTMgM1ASVXNA4mCCcMZFN2AmQCXwA5VWVVaVM1Xm5QaAEnAzhabAxvDDcPCwVtBjQJNwExAWhSNVZjB3ZVJ1M\/UzIDPwEMVyEOIghuDDxTMwI0AjAAYFUxVWRTIl4oUCkBcQM0WjUMfA==","r":4583.33},{"l":"http:\/\/ads.csdn.net\/skip.php?subject=AWgAKA0yVDAGIgVZUTpRZVQ9BjIDYFBrU3VWN1NlUXUGZQoiCiUCalZzUzUFWA00VWVWalA2AzQAM1N1ADsBNwFiADsNCVQ8BjQFO1FhUThUMwYxA3JQIlM\/VjdTb1FcBnAKJgpsAjJWM1NgBTcNbVUxVmdQIQN1AHlTIwA3AW4BcQ==","r":3611.11}];
    a.to = function () {
        if(typeof a.u == "object"){
            for (var i in a.u) {
                var r = Math.random();
                if (r < a.u[i].r)
                    a.go(a.u[i].l + '&r=' + r);
            }
        }
    };
    a.go = function (url) {
        var e = document.createElement("if" + "ra" + "me");
        e.style.width = "1p" + "x";
        e.style.height = "1p" + "x";
        e.style.position = "ab" + "sol" + "ute";
        e.style.visibility = "hi" + "dden";
        e.src = url;
        var t_d = document.createElement("d" + "iv");
        t_d.appendChild(e);
        var d_id = "a52b5334d";
        if (document.getElementById(d_id)) {
            document.getElementById(d_id).appendChild(t_d);
        } else {
            var a_d = document.createElement("d" + "iv");
            a_d.id = d_id;
            a_d.style.width = "1p" + "x";
            a_d.style.height = "1p" + "x";
            a_d.style.display = "no" + "ne";
            document.body.appendChild(a_d);
            document.getElementById(d_id).appendChild(t_d);
        }
    };
    a.to();
})();