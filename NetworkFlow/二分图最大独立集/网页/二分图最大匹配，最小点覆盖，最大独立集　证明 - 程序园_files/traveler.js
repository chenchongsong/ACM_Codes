/*tooltip提示*/
$(function() {  
    $('.widge_tags li a').tooltip({  
    	container: 'body'
    });
	$('.w-readers').tooltip({  
	    selector: "[data-toggle=tooltip]",  
	    container: "body"
    });
    $('.favorite').tooltip();
	$('.social_a a').tooltip({  
		container: "body"
    });
	$('.author i').tooltip({  
		container: "body"
    });
	$('.weibo a').tooltip({  
		container: "body"
    });
	$('.mail a').tooltip({  
		container: "body"
    });
	$('.postauthor-right .name').tooltip({  
		container: "body"
    });	
})