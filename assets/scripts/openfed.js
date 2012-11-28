/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
	Project name: openFED
	Project url: 
	Version: 0.1
	Author: Blue4You
	Author URI: http://www.blue4you.be/		
*/

(function ($) {
	$(document).ready(function(){
		// Change the logo from themes "seven" by openFED. Can't change directly in the html

		var reg = new RegExp("[/]+", "g");// create a regular expression that looks for every  "/"
		var path = $("#logo").attr("src");	
		var tableau = path.split(reg); // split into an array the url every "/"
		
		var newPath = tableau[0] + "//" + tableau[1] + "/profiles/openfed/assets/images/openfed_logo.png"; // create the new url	
		
		$("#logo").attr("src", newPath);
		
		$("#openfed-functionnalities-form .form-type-checkbox").hover( function () {
			$(this).animate({
				opacity : 0.4s;
				});
		});
		
		// Change class label to activate/deactivate features		
		$("#openfed-functionnalities-form .form-type-checkbox label").click( function() {
			var newclass;			
			newclass = ( $(this).hasClass('enabled')) ? "disabled" : "enabled"; 
			$(this).attr("class", "option "+ newclass);			
		});
		
		
	
	});
})(jQuery)
