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
		var path = $("#logo").attr("src");	
		
		var reg = new RegExp("[/]+", "g");		// create a regular expression that looks for every  "/"
		var tableau = path.split(reg); 			// split into an array the url every "/"
		var newPath = tableau[0] + "//" + tableau[1] + "/profiles/openfed/assets/images/openfed_logo.gif"; // create the new url	
		
		$("#logo").attr("src", newPath);
		
		/* Button enabled - disabled 		 
		 * */
		
		// Hide selectbox and replace with div.button
		
		$("#edit-module-list .form-type-checkbox").find("input.form-checkbox").hide(); 
		$("#edit-module-list .form-type-checkbox").append('<div class="button disabled">disabled</div>');
		
		// Change class button to activate/deactivate features	
		
		$("#edit-module-list .form-type-checkbox div.button").click( function() {
			var newclass = ( $(this).hasClass('enabled')) ? "disabled" : "enabled"; // Ternary condition to change the class
			$(this).attr("class", "button "+ newclass); 							// change class with the new one
			$(this).text(newclass); 												// Modifying text in this div
			
			var checkbox = $(this).parent().find("input.form-checkbox");
			
			if(newclass === "enabled"){
				checkbox.attr("checked", "checked");	
			}
			else{
				checkbox.removeAttr("checked");
			}
		});
		
		/* end button
		 * */
	
	});
})(jQuery)
