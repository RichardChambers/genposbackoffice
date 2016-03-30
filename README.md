# genposbackoffice 

genposbackoffice is a remote access application for the GenPOS Rel 2.2.1 point of sale
application from Georgia Southern University.

This application is an exploration of the GenPOS PCIF Third Party Toolkit and the API exposed
by the Third Party Toolkit dll.

The source code for this application requires the following components to compile and link:
 - Visual Studio 2005 or later
 - GenPOS PCIF Third Party Toolkit from GenPOS Rel 2.2.1
 - SQLite3 source which is included in the genposbackoffice Github as a directory tree
 
 The purpose of the genposbackoffice remote application is to provide a user friendly application
 to perform basic OAMP actions with a GenPOS terminal cluster from a remote location. These actions
 include:
  - making a back up copy of the provisioning in a terminal cluster
  - modifying the provisioning in a terminal cluster
  - performing operation actions such as End of Day
  - pull operation data such as totals from a terminal cluster