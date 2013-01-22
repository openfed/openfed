(function ($) {
	$(document).ready(function(){
		// Url persistant.
		$('.url-file-persistent').each(function(){
		  // Hide.
		  $(this).hide();
		  // Get the link.
		  var url = $(this).html();
		  // Set the new content for the container.
		  var output = '<span><input type="text" class="url-file-persistent-input" value="' + url + '"/></span>';
		  $(this).html(output);
		});
		$(".field-name-file-url-persistent a").each(function(){
		  $(this).click(function(e){
			e.preventDefault();
			$(this).parent().find('span.url-file-persistent').slideToggle('fast', function(){
			  $(this).find('span input.url-file-persistent-input').select();
			});
		  });
		});  
	  if ( $(window).width() < 768 ){
		menuSmartphone();
	  }
	  else{
		$("nav#navigation .block-menu").show();
	}
	// Detect width of the window browser
	/*$(window).bind('resize', function() {
		if ( $(window).width() < 768 ){
			$("nav#navigation .block-menu").hide();
	  }
	  else{
			$("nav#navigation .block-menu").show();
		}
	});*/ 
  }); 
  

	function menuSmartphone(){	
		//Add a span tag to expand sub-categories
		$('nav#navigation .block-menu ul.menu li.expanded a').each(function() {
			$(this).after('<span></span>');
		});
		// Menu for smartphone
		$("nav#navigation .block-menu").hide();
		$("nav#navigation span.icon-menu").click( function (){
			$("nav#navigation .block-menu").slideToggle();
		});
		$("nav#navigation .content ul.menu li").children("ul.menu").hide();//2nd level
		$("nav#navigation .content ul.menu li.active-trail").children("ul.menu").show();
		$("nav#navigation .content").children("ul.menu").children("li.expanded").children("span").click( function (){
			$(this).parent().children("ul.menu").slideToggle();
		});
		$("nav#navigation .content ul.menu li ul.menu li").children("ul.menu").hide();//3rd level
		$("nav#navigation .content ul.menu li ul.menu li.active-trail").children("ul.menu").show();
		$("nav#navigation .content ul.menu li").children("ul.menu").children("li.expanded").children("span").click( function (){
			$(this).parent().children("ul.menu").slideToggle();
		});
		$("nav#navigation .content ul.menu li ul.menu li ul.menu li").children("ul.menu").hide();//4th level
		$("nav#navigation .content ul.menu li ul.menu li ul.menu li.active-trail").children("ul.menu").show();
		$("nav#navigation .content ul.menu li ul.menu li").children("ul.menu").children("li.expanded").children("span").click( function (){
			$(this).parent().children("ul.menu").slideToggle();
		});
		$("nav#navigation .content ul.menu li ul.menu li ul.menu li ul.menu li").children("ul.menu").hide();//5th level
		$("nav#navigation .content ul.menu li ul.menu li ul.menu li ul.menu li.active-trail").children("ul.menu").show();
		$("nav#navigation .content ul.menu li ul.menu li ul.menu li").children("ul.menu").children("li.expanded").children("span").click( function (){
			$(this).parent().children("ul.menu").slideToggle();
		});
	}

})(jQuery);