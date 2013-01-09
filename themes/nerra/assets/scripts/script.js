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
	});
		
})(jQuery);