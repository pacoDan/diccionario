# para ejecutar 
gcc main.c -o programa -lodbc


# para usarlo se instala unixodbc https://www.unixodbc.org/ 
# EXTRA 
Si tienes la fuente de UnixODBC y deseas compilarla e enlazarla con tu programa C en Arch Linux, puedes seguir estos pasos:

Extrae el archivo unixODBC-2.3.11.tar.gz en tu directorio de trabajo. Puedes hacerlo con el siguiente comando:
shell
Copy code
tar -xf unixODBC-2.3.11.tar.gz
Ve al directorio extraído unixODBC-2.3.11:
shell
Copy code
cd unixODBC-2.3.11
Configura la compilación ejecutando el comando ./configure. Esto preparará el entorno y configurará las opciones de compilación:
shell
Copy code
./configure
Compila las fuentes ejecutando el comando make. Esto compilará UnixODBC:
shell
Copy code
make
Instala UnixODBC ejecutando el comando sudo make install. Esto instalará las bibliotecas y archivos necesarios en tu sistema:
shell
Copy code
sudo make install
Una vez instalado UnixODBC, podrás enlazarlo con tu programa C. Asegúrate de incluir las bibliotecas necesarias y enlazar con UnixODBC al compilar tu programa. Puedes usar el siguiente comando de compilación como ejemplo:

shell
Copy code
gcc main.c -o programa -lodbc
Reemplaza main.c con el nombre de tu archivo fuente C y programa con el nombre que desees para el ejecutable resultante.

Recuerda que es posible que también necesites configurar los controladores ODBC específicos para SQL Server. En ese caso, consulta la documentación proporcionada junto con los controladores y sigue las instrucciones para configurar los controladores en UnixODBC.

Es importante tener en cuenta que compilar e instalar software desde la fuente puede requerir dependencias adicionales y puede no ser compatible con las herramientas de gestión de paquetes de la distribución. Siempre es recomendable consultar la documentación proporcionada con la fuente y considerar otras opciones disponibles, como la búsqueda de paquetes precompilados o el uso de alternativas compatibles con tu distribución Linux.




