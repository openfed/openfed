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
- The following directories in sites/default :
  - public (sites/default/public)
  - private (sites/default/private)
  - tmp (sites/default/tmp)

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
   and directories. Then, you will have to build your Drupal installation using
   the drush make command. The usage is as follow :

     drush make build-openfed.make /path/to/your/project

2. Create your files and private directories under
   /path/to/your/project/sites/default and then give the permissions to your
   webserver's user. You can do it as follow :

     cd /path/to/your/project
     mkdir -p sites/default/files sites/default/private
     chown -R www-data sites/default/files sites/default/private

   You should also have a tmp directory outside the web directory (for instance, /var/tmp)

3. Follow the standard Drupal way to create your site by creating the database
   and running the install script.