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
		// Expand/collapse "url block" to share with the world
		$(".field-name-file-url-persistent a").each(function(){
		  $(this).click(function(e){
			e.preventDefault();
			$(this).parent().find('span.url-file-persistent').slideToggle('fast', function(){
			  $(this).find('span input.url-file-persistent-input').select();
			});
		  });
		});
		 
	// When under 768 px, menu changed in a vertical way with click event enable	
	if ( $(window).width() < 768 ){
		// Call a function that hide/show the active/inactive categories
		menuSmartphone();
		
		//Add a span tag after each "a" tag to will expand sub-categories
		$('nav#navigation ul.menu li.expanded a').each(function() {
			$(this).after('<span></span>');
		});
		// click event enable on the icon-menu
		$("nav#navigation span.icon-menu").click( function (){
			$nav = $("nav#navigation .container").children("ul.menu");// cached this element
			// border of the icon when active/inactive
			if($nav.css("display") == "none"){
				$(this).css({'border-radius' : '5px 5px 0 0','z-index' : '1001','border-bottom' : '1px solid transparent'});
			}
			else{
				$(this).css({'border-radius' : '5px','z-index' : '10','border-bottom' : '1px solid ##a2a2a2'});
			}
			//expand - collapse the menu
			$nav.slideToggle();
		});
		//expand - collapse the menu second level only
		$("nav#navigation .container").children("ul.menu").children("li.expanded").children("span").click( function (){
			$(this).parent().children("ul.menu").slideToggle();
			console.log("test");
		});
		//expand - collapse the menu third level only
		$("nav#navigation ul.menu li").children("ul.menu").children("li.expanded").children("span").click( function (){
			$(this).parent().children("ul.menu").slideToggle();
		});
		//expand - collapse the menu fourth level only
		$("nav#navigation ul.menu li ul.menu li").children("ul.menu").children("li.expanded").children("span").click( function (){
			$(this).parent().children("ul.menu").slideToggle();
		});
		//expand - collapse the menu fifth level only
 		$("nav#navigation ul.menu li ul.menu li ul.menu li").children("ul.menu").children("li.expanded").children("span").click( function (){
			$(this).parent().children("ul.menu").slideToggle();
		});
	  }
	  else{
		$("nav#navigation ul.menu").css("display","block");
	  }
  }); // END document.ready function
  
	// Detect width of the window browser
	$(window).bind('resize', function() {
		if ( $(window).width() < 768 ){
			menuSmartphone();
		}
		else{
			$("nav#navigation ul.menu").css("display","block");
		}
	});
	
	// Function that hide/show the active/inactive categories
	function menuSmartphone(){	
	// Menu for smartphone
		$("nav#navigation ul.menu").hide();
		$("nav#navigation ul.menu li").children("ul.menu").hide();//2nd level
		$("nav#navigation ul.menu li.active-trail").children("ul.menu").show();
		$("nav#navigation ul.menu li ul.menu li").children("ul.menu").hide();//3rd level
		$("nav#navigation ul.menu li ul.menu li.active-trail").children("ul.menu").show();
		$("nav#navigation ul.menu li ul.menu li ul.menu li").children("ul.menu").hide();//4th level
		$("nav#navigation ul.menu li ul.menu li ul.menu li.active-trail").children("ul.menu").show();
		$("nav#navigation ul.menu li ul.menu li ul.menu li ul.menu li").children("ul.menu").hide();//5th level
		$("nav#navigation ul.menu li ul.menu li ul.menu li ul.menu li.active-trail").children("ul.menu").show();
	}
	
})(jQuery);