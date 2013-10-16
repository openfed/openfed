CONTENTS OF THIS FILE
---------------------

 * Requirements and notes
 * Optional server requirements
 * Installation

REQUIREMENTS AND NOTES
----------------------

Openfed requires:

- PHP 5.3.5 (or greater) (http://www.php.net).
- A PHP memory_limit set to 320M (or higher)
- A PHP max_input_vars set to 5000 (or higher)
- Drush 5.x or higher
- A sites/default/files directory which has to be writable by the web server.

For further information see Drupal's INSTALL.txt file.

OPTIONAL SERVER REQUIREMENTS
----------------------------

- If you want to use OpenFed's Addemar integration, you will have to enable
  SOAP on your webserver.

INSTALLATION
------------

1. Download OpenFed from Drupal.org

   You can obtain the latest Openfed release from http://drupal.org -- the files
   are available in .tar.gz and .zip formats and can be extracted using most
   compression tools.

   To download and extract the files, on a typical Unix/Linux command line, use
   the following commands (assuming you want version x.y of Drupal in .tar.gz
   format):

     wget http://drupal.org/files/projects/openfed-x.y.tar.gz
     tar -zxvf openfed-x.y.tar.gz

   This will create a new directory openfed-x.y/ containing all OpenFed files
   and directories. 

2. Create your files directory at /path/to/your/project/sites/default/files
   and then give the permissions to your webserver's user. You can do it as follow

   You should also have a tmp directory outside the web directory (for instance, /var/tmp)

3. Follow the standard Drupal way to create your site by creating the database
   and running the install script.
