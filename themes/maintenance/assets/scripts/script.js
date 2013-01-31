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
		// The spacebar is disabled as a pagedown key but can still be used in a different script : http://www.webmasterworld.com/javascript/3224261.htm
		var el = document.getElementById('openfed-functionalities-form');
        if ( el == true  ){
          el.addEventListener('keydown',function(e){if(e.keyCode==32){e.preventDefault();}},true);	
        }
		
		// Change the logo from themes "seven" by the actual logo "openFED" because it can't be change directly in the html
		var path = $("#logo").attr("src");		// take the path of the image called with the id "logo"
		
		var reg = new RegExp("[/]+", "g");		// create a regular expression that looks for every  "/" in the variable "path"
		var tableau = path.split(reg); 			// split into an array the url(path) every "/"
		var newPath = tableau[0] + "//" + tableau[1] + "/profiles/openfed/assets/images/openfed_logo.gif"; // create the new url	
		
		$("#logo").attr("src", newPath);		// assign the newly created path to the image
		
		/* Button enabled - disabled 		 
		 * */
		
		// Hide selectbox and replace with div.button
		
		$("#edit-module-list .form-type-checkbox").find("input.form-checkbox").hide(); 
		$("#edit-module-list .form-type-checkbox").append('<a class="checkbox disabled" href="#">disabled</a>');
		
		// Change class button to activate/deactivate features	
		
		$("#edit-module-list .form-type-checkbox a.checkbox").click( function(e) {
			e.preventDefault(); 	// deactivate links behavior of the the tag "a href"
			$(this).fadeOut("fast", function () {
				var newclass = ( $(this).hasClass('enabled')) ? "disabled" : "enabled"; // Ternary condition to change the class
				$(this).attr("class", "checkbox "+ newclass); 							// change class with the new one
				$(this).text(newclass); 												// Modifying text in this div
							
				var checkbox = $(this).parent().find("input.form-checkbox");
				
				if(newclass === "enabled"){
					checkbox.attr("checked", "checked");	
				}
				else{
					checkbox.removeAttr("checked");
				}
				$(this).fadeIn("fast");
			});	
		});
				
		$("#edit-module-list .form-type-checkbox a.checkbox").keyup( function(e) {
			 if(e.keyCode == 32){// keycode = 32 correspond to the key "Space Bar"
				$(this).fadeOut("fast", function () {
					var newclass = ( $(this).hasClass('enabled')) ? "disabled" : "enabled"; // Ternary condition to change the class
					$(this).attr("class", "checkbox "+ newclass); 							// change class with the new one
					$(this).text(newclass); 												// Modifying text in this div
								
					var checkbox = $(this).parent().find("input.form-checkbox");
					
					if(newclass === "enabled"){
						checkbox.attr("checked", "checked");	
					}
					else{
						checkbox.removeAttr("checked");
					}
					$(this).fadeIn("fast");
				});	
		   	 }
		});
			
		/* end button
		 * */
		/* deactivate links behavior of the the tag "a href"
		$("#content #console a").click( function(e) {
			e.preventDefault(); 	
		});*/
	});
})(jQuery)
