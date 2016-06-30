# Decrypt9
_Aplicación para copiar juegos y descifrar archivos._

## Decrypt9 WIP (trabajo en progreso) por d0k3:

Esta aplicación está basada en el Decrypt9 original de Archshifts, el Decrypt9WIP incluye nuevas funciones. Recuerda que el nombre de los ejecutables para esta aplicación tienen el nombre de «Decrypt9WIP» (no, «Decrypt9»). Las nuevas ocpiones incluidas en esta aplicación serán añadidas en la aplicación original de Archshifts.

Puedes comentar tu opinión sobre este proyecto y proporcionar al desarrollador ideas para la aplicación en [GBAtemp](https://gbatemp.net/threads/download-decrypt9-wip-3dsx-launcher-dat.388831/) (solo en inglés).

## Decrypt9WIP_ES por Player_AAA:

Esto es una traducción al español de la aplicación original creada por d0k3 (y esta está basada en el Decrypt9 de Archshifts). Solo se han editado los menús, modificando las cadenas de texto, el resto del código no ha sido modificado. Intentaré tener esta traducción "a la última".

## ¿Qué puedo hacer con esto?
En esta lista (incompleta) están las principales funciones de esta aplicación, más abajo encontrarás una lista con todas las funciones de esta aplicación.
* Crear XORpads para el descifrado de archivos NCCH ('.3DS').
* Crear XORpads para el descifrado de archivos en la carpeta '/Nintendo 3DS'.
* Crear XORpads para el descifrado de las particiones TWLN y CTRNAND.
* Descifrar Titlekeys, por un archivo o directamente desde la SysNAND y EmuNAND.
* Copiar y restaurar tu SysNand y EmuNand.
* Copiar e inyectar cualquier partición de tu SysNNAD y EmuNAND.
* Copiar e inyectar archivos (ticket.db, ...) de tu SysNAND y EmuNAND.
* Inyectar aplicaciones en la aplicación de 'Salud y Seguridad'.
* Crear y actualizar el archivo 'SeedDB'.
* Descifrar directamente archivos NCCH ('.3DS') y CIA.
* Descifrar directamente archivos desde la carpeta '/Nintendo 3DS/'.
* ... y muchas más.

## Cómo ejecutar esto:
 
Decrypt9WIP_ES puede ser ejecutado de la siguiente manera:
* __A9LH & Brahma__: Copia `Decrypt9.bin` a tu tarjeta SD (donde la pongas dependerá del método que uses), luego usa [Brahma](https://github.com/delebile/Brahma2) o [arm9loaderhax](https://github.com/Plailect/Guide/wiki), para ejecutarlo.

*Si eres un desarrollador y quieres compilar el código fuente de esta traducción, puedes hacerlo con `make`; recuerdas que debes tener instalado [DevKitARM](http://devkitpro.org/wiki/Getting_Started/devkitARM). 

## Carpeta de juego y trabajo:

La mayoría de archivos que obtengas con Decrypt9 serán puestos en la raíz de la SD; así que estás carpetas son casi opcionales. De todos modos, se recomienda usarla e incluso son necesarias para ciertas funciones. Estas son las dos carpetas usadas:
* __`/D9Game/`__: Los archivos NCCH (.3DS), CIA, BOSS, y de la SD (de la carpeta '/Nintendo 3DS/') van aquí.
* __`/Decrypt9/`__: Todo lo que no vaya en la carpeta `/D9Game/` va aquí, además, esta es la carpeta de salida (_output_) por defecto. Si la carpeta `/D9Game/` no existe, los archivos NCCH, CIA, BOSS y de la SD serán procesados aquí.

El descifrado de archivos de juegos (NCCH, CIA, BOSS, SD) necesita una de estas dos carpetas. Los archivos de entrada (_input_) serán buscados primero en la carpeta `/Decrypt9/`, y si no se encuentran, serán buscados en la raíz de la SD.

## Archivos 'de ayuda' (o, en inglés, _support files_):

Dependiendo de la operación, versión del sitema y archivos que vayas a usar, Decrypt9 puede necesitar archivos 'de ayuda' para funcionar correctamente. Estos archivos pueden ser colocados en la raíz de la SD, o en la carpeta de trabajo (`/Decrypt9/`). Estos son los archivos 'de ayuda' que usa Decrypt9:
* __`slot0x05keyY.bin`__: Este archivo se necesitaba para acceder a las opciones que nos ofrecía la partición CTRNAND (básicamente, todo) en la N3DS. En este momento, ya no se usa.
* __`slot0x25keyX.bin`__: El archivo se necesita para descifrar NCCH 7x encriptados, y NCCHs y CIAS si la versión de tu consola es inferior a 7.0.
* __`slot0x18keyX.bin`__: El archivo se necesita para descifrar archivos NCCH de seguridad 3 (o, en inglés, _Secure 3 crypto NCCHs_), y CIAs en O3DS si no tienes A9LH.
* __`slot0x1BkeyX.bin`__: El archivo es necesario para descifrar NCCHs de seguridad 4 (o, en inglés, _Secure 4 crypto NCCHs_) y CIAs.
* __`aeskeydb.bin`__: Esto es una alternativa a los cuatro archivos `slot0x??key?.bin` mencionados anteriormente. Puede conteenr varias claves (_keys_). Se puede crear de los archivos anteriores en Decrypt9 con la función 'Crear Key Database'. 
* __`seeddb.bin`__: Decrypt9 puede crear y actualizar este archivo desde las semillas (_seeds_) que tienes instaladas en tu sistema. Se necesita para descifrar NCCHs con semilla encriptada (_seed crypto NCCHs_) y CIAs. Recuerda que tu `seeddb.bin` debe contener la semilla del juego a descifrar.
* __`otp.bin`__: Este archivo es único e intransferibe, se requiere (además del archiconocido a9lh) para descifrar el sector 0x96 de la N3DS (y O3DS con a9lh instalado). [Esta guía](https://github.com/Plailect/Guide/wiki) te explica cómo el archivo `otp.bin`.
* __`movable.sed`__: Este archivo se puede obtener con Decrypt9. Se necesita para descifrar archivos de otra 3DS, o de otra instalación de tu propia 3DS. No la necesitas para descifrar los archivos de tu SysNAND/EmuNAND.
* __`secret_sector.bin`__: Una copia descifrada, sin modificar (es decir, que has obtenido el archivo ANTES de instalar a9lh) del archivo `sector0x96.bin`. Se requiere para descrifrar la sección, encriptada, de ARM9 en las N3DS. La alternativa a este archivo son dos archivos llamados `slot0x11key95.bin` y `slot0x11key96.bin`.
* __`d9logo.bin`__:  Contiene un logo que se mostrará en la pantalla inferior. Se incluye un `d9logo.bin` por defecto. Puedes crear tu propio `d9logo.bin` usando [ImageMagick](http://www.imagemagick.org/); con este programa convierte una imagen, con una resolucion de 320x240px, a d9logo.bin y con una rotación de 90.

## Controles de Decrypt9

Los controles más importantes se muestran en pantalla, esta es una lista de todos los controles:
* __ABAJO__/__ARRIBA__ - Navegar por los menus, seleccionar opciones...
* __A__ - Entrar en un submenú o confirmar una acción.
* __B__ - Sair de un submenú o cancelar una acción.
* __L/R__ - Cambiar entre submenús (solo funciona en el primer nivel del submenú).
* __X__ - Realizar una captura de pantalla.
* __X + IZQUIERDA/DERECHA__ - Realizar captura de pantalla de todos los submenús y menús.
* __SELECT__ - Desmontar tarjeta SD.
* __START (+ IZQUIERDA)__ - Reiniciar (en este caso, solo tienes que pulsar START) / Poweroff (tienes que pulsar START e izquierda -con la cruceta-).

Hay algunas opciones (por ejemplo, la función de hacer una copia de la NAND), que requieren que elijas un archivo. En estos casos, usa la cruceta y selecciona con A para seleccionar, o B para cancerlar.

## Descripción de las opciones de Decrypt9

Las opciones de Decrypt9 están organizadas en 5 categorías, estas son:

### Opciones de generación de XORpads
Esta categoría incluye todas las opciones que generan XORpads. Los XORpads, por sí mismos, son inútiles, pero con herramientas adicionales, puedes descifrar archivos en tu PC. La mayoría, por no decir todas, las utilidades de los XORpads, ya no son necesarias, ya que Decrypt9 incluye herramientas en las que se puede hacer el mismo trabajo que hacían estas.
* __NCCH Padgen__: Esto genera XORpads para archivos NCCH/NCSD (por ejemplo, '.3DS') desde `ncchinfo.bin`. Puedes generar el archivo `ncchinfo.bin` con el script de Python `ncchinfo_gen.py` (o `ncchinfo_tgen.py` para paquetes de temas) y coloca el archivo en la carpeta de trabajo (`/Decrypt9/`). Los XORpads suelen ser utilizados para convertir del formato `.3DS` a `.CIA`; conque esta opción suele ser utilizado junto con la aplicación de Riku llamada [_3DS Simple CIA Converter_](https://gbatemp.net/threads/release-3ds-simple-cia-converter.384559/). 

    **Importante: según tu tipo de consola, la versión de esta y la encriptación de los archivos, puedes necesitar archivos de ayuda y/o el `seeddb.bin`.**

* __SD Padgen (SDinfo.bin)__: Esto genera XORpads para los archivos instalados en la carpeta `/Nintendo 3DS/` de tu tarjeta SD. Usa el script de Python `sdinfo_gen.py` y colocar el archivo `sdinfo.bin` generado por el script en la carpeta de trabajo (`/Decrypt9/`). Si los archivos  de la SD son de otra NAND, deberás tener el `movable.sed` (se puede obtener con Decrypt9) para descifrar archivos de otra 3DS. Usar esto solo tiene sentido si vas a descifrar archivos de otra 3DS, si no es así, usa las dos opciones mencionadas abajo. Puedes usar la aplicación [padXORer](https://github.com/polaris-/3ds_extract) de Xerpi para aplicar los XORpads.
* __SD Padgen (SysNAND)__: Esta opción, básicamente, es una mejora de la anterior mencionada. La mayoría de usuarios tienen dos carpetas `/Nintendo 3DS/` en su SD, una que pertenece a la SysNand, y otra que pertenece a la EmuNand. Esta opción generará XORpads para contenido cifrado que esté en la carpeta que pertenezca a la SysNand. No modificará nada en tu SysNand, así que no hay peligro al usarla. Una ventana te pedirá que selecciones cuán XORpads quieres generar (usa la cruceta). No se recomienda generar todos de una vez, porque puede llevar a muchos GBs de información y un gran tiempo de espera.
* __SD Padgen (EmuNAND)__: Es la misma función que la anterior, sino que usa la carpeta de la EmuNand. La carpeta de la EmuNand suele ser más pesada que la de la SysNand, así que ten cuidado al seleccionar cuán XORpads generar.
* __CTRNAND Padgen__: Esto genera un XORpad para la partición CTRNAND de la memoria flash de tu 3DS. Usa esto con una copia de la NAND (SysNAND/EmuNAND) y la herramienta [3DSFAT16Tool](https://gbatemp.net/threads/port-release-3dsfat16tool-c-rewrite-by-d0k3.390942/) de d0k3 para descifrar y volver a cifrar la partición CTRNAND en tu PC. Esto es útil para cualquier modificacióin que desees hacer en el sistema de archivos principal de tu 3DS.
* __CTRNAND Padgen (`slot0x4`)__: Esto es una función exclusiva de la N3DS. Hace lo mismo que la función anterior, pero usa el `slot0x04` para generar el XORpad. Los XORpads generados con el `slot0x04` son necesarios para el cifrado y descifrado de la partición CTRNAND de una N3DS en la que se haya hecho un _downgrade_.
* __TWLNAND Padgen__: Esta función genera un XORpad para la partición TWLNAD de la memoria flash de la 3DS. Usa esto con una copia de la NAND (SysNAND/EmuNAND) de tu consola y la herramienta [3DSFAT16Tool](https://gbatemp.net/threads/port-release-3dsfat16tool-c-rewrite-by-d0k3.390942/) de d0k3 para descifrar y cifrar la partición TWLNAND en tu PC. Esto puede ser usado, por ejemplo, para inatalar el exploit ['SudokuHax'](https://gbatemp.net/threads/tutorial-new-installing-sudokuhax-on-3ds-4-x-9-2.388621/).
* __FIRM0FIRM1 Padgen__: Esta función genera un XORpad para las particiones FIRM0 y FIRM1 de la memoria flash de tu 3DS. Usa esto con una copia de la NAND (SysNAND/EmuNAND) y la herramienta [3DSFAT16Tool](https://gbatemp.net/threads/port-release-3dsfat16tool-c-rewrite-by-d0k3.390942/) de d0k3 para cifrar y descifrar las particiones FIRM0/FIRM1 en el PC. Esto es útil, por ejemplo, para instalar manualmente [arm9loaderhax](https://github.com/delebile/arm9loaderhax).

### Opciones de Titlekey
Esta categoría incluye todas las funciones realcionadas con las titlekeys. Los titlekeys descifrados (`decTitleKeys.bin`) son usados para descargar software desde un CDN a través del script de Python `cdn_downoad.py` y la herramienta [PlaiCDN](https://github.com/Plailect/PlaiCDN). Los titlekeys cifrados son usados, para el mismo fin, por [FunKeyCIA](https://github.com/llakssz/FunKeyCIA/). Puedes ver también las titlekeys (cifrados o descifrados) con el script de python `print_tickets_keys.py`.
* __Descifrar un Titlekey (archivo)__: Primero, genera el archivo `encTitleKeys.bin` con el script de Python `dump_ticket_keys.py` y colócalo en la carpeta de trabajo (`/Decrypt9/`). Esta función descifrará el archivo y generará el archivo `decTitleKeys.bin`, que contiene las titlekey descifradas.
* __Descifrar Titlekey (SysNAND)__: Esta función encontrará y descifrará todas las titlekeys de tu SysNAND, sin necesidad de herramientas adicionales. El archivo `decTitleKeys.bin` se gerará en tu tarjeta SD.
* __Descifrar Titlekey (EmuNAND)__: Esta función encontrará y descifrará las titlekeys de tu EmuNAND, sin necesidad de herramientas adicionales. El archivo `decTitleKeys_emu.bin` será generado en la tarjeta SD.
* __Cifrar Titlekey (file)__: Esta función usa el archivo `decTitleKeys.bin` y lo encripta, creando el archivo `encTitleKeys.bin`. Esto es útil para convertir entre los dos formatos, asi estás seguro de usar el formato correcto para la herramienta que desees usar.
* __Realizar copia de Titlekey (SysNAND)__: Esto encontrará las titlekeys instaladas en tu SysNAND y las copiará, sin descifrarlas, al archivo `encTitleKeys.bin`.
* __Realizar copia de Titlekey (EmuNAND)__: Esto encontrará las titlekeys instaladas en tu EmuNAND y las copiará, sin descifrarlas, al archivo `encTitleKeys.bin`.

### Opciones de SysNAND/EmuNAND
Esto son dos categorías distintas en el menú, pero la funcionalidad de cada opción es la misma, solo que afectan a la NAND que quieras (Sys o Emu).Estas categorías incluyen todas las funciones de copiar, inyectar, modificar o extraer información desde/a la SysNAND/EmuNAND. Para las funciones que generan archivos en la SD, el usuario puede seleccionar un nombre para estos en una lista con unos nombres predefinidos. Para que la aplicación sea un poco más segura, las funciones que pueden dañar el sistema -es decir, en las que se modifique la NAND- se debe introducir un patrón de desbloqueo, además, en la pantalla superior se avisa del daño que puede causar usar esa función.
* **Copiar/Restaurar (Sys/Emu)NAND** : Contiene varias opciones para copiar/restaurar la NAND. Estas son las opciones disponibles:
  * __Copia de la NAND__: Copia la NAND a un archivo `.bin`, puedes seleccionar el nombre de este archivo, los nombres más comunes son `NAND.bin` para SysNAND y `EmuNAND.bin` para la EmuNAND. Este archivo es una copia de seguridad de toda tu SysNAND/EmuNAND y se puede usar para restaurar la NAND a un estado anterior.
  * __Copia de la NAND (menor peso)__: Hace lo mismo que la opción anterior, pero solo copia en la copia de seguridad los datos útiles (ya que la anterior opción copia TODA la NAND, y hay muchos datos inservibles que, para ahorrar espacio, pueden ser eliminados).
  * __Restaurar NAND(!)__: Esta opción restaurar la NAND que desees (Sys/Emu) del archivo `.bin` que le propciones (este archivo debe estar en la carpeta `/Decrypt9/` o en la raíz de la SD). Las copias de seguridad serán revisadas antes de restaurar, así hay un riesgo menor de instalar una copia de seguridad corrupta.
  * __NAND Restore (forzado)(!)__: La misma opción que la anterior, pero sin el revisado por una copia de seguridad corrupta. No se recomienda usar esta opción si no sabes lo que haces. Recuerda que si la opción anterior no te permite restaurar la NAND, es por una buena razón.
  * __NAND Restore (manetener a9lh)(!)__: Solo se puede usar esta opción para restaurar la SysNAND, hace lo mismo que la restauración 'estándar', pero esta opción mantiene los archivos de a9lh intactos. Solo usar si tienes a9lh y quieres seguir teniendo el _exploit_ instalado.
  * __Validar copia de la NAND__: Usa esto para verificar las copias de la NAND que tengas en tu SD, si pasa el test, puedes usarlas sin problemas.
* __Realizar copia de una partición__: Esta función te permite copiar y descifrar las particiones de la NAND (TWLN / TWLP / AGBSAVE / FIRM0 / FIRM1 / CTRNAND / Sector0x96). Particiones con un sistema de archivos pueden ser montadas en Windows con [OSFMount](http://www.osforensics.com/tools/mount-disk-images.html). Las particiones que pueden ser copiadas con esta función son:
  * __TWLN__: _TWL-NAND FAT16_ - esta partición hace lo mismo que en la DSi. En esta están guardados los juegos de DSiWare. Esta partición puede ser usada, por ejemplo, para instalar [SudokuHax](https://gbatemp.net/threads/tutorial-new-installing-sudokuhax-on-3ds-4-x-9-2.388621/). 
  * __TWLP__: _TWL-NAND PHOTO FAT12 _ - esta es una partición específica de la Nintendo DSi para guardar fotos.
  * __AGBSAVE__: _AGB_FIRM GBA savegame_ - contiene una copia temoral de los datos de guardado de GBA.
  * __FIRM0__: _Firmware partition_ - se usa para el fines de desarrollo y no debería ser modificada por usuarios.
  * __FIRM1__: _Firmware partition backup_ - suele ser una copia exacta de FIRM0.
  * __CTRNAND__: _CTR-NAND FAT16 File System_ - contiene todos los datos interesantes de tu 3DS. Los títulos instaladas en la NAND residen aquí, y puedes extraer casi cualquier archivo de tu interés de esta partición.
  * __Sector0x96__: _Console-unique encrypted New3DS key-storage_ - contiene las llaves (_keys_) de la N3DS, el aceeso a esta es necesario para la instalación de A9LH.
  * __NAND header__: _NCSD header_ - el _header_ de tu NAND, es único según la consola y contiene los _offsets_ de todas las particines. También contiene la tabla de particiones encriptada TWL MBR.
* __Inyectar una partición(!)__: Esto te permite volver a encriptar e inyectar cualquier partición de la NAND con su respectivo archivo (`TWLN.bin` / `TWLP.bin` / `AGBSAVE.bin` / `FIRM0.bin` / `FIRM1.bin` / `CTRNAND.bin` / `Sector0x96.bin`). Solo usa esto si sabes lo que estás haciendo, y ten cuidado, puedes estropear tu consola.
* __Realizar copia de archivo.__: Esta opción te permite copiar y descifrar varios archivos de la SysNAND y Emunand. Los archivos que se pueden copiar son los siguientes:
  * __ticket.db__: _Contiene las titlekeys de los juegos instalados_ - usa esto con la aplicación de Cearps [FunkyCIA](https://gbatemp.net/threads/release-funkycia2-build-cias-from-your-eshop-content-super-easy-and-fast-2-1-fix.376941/) para descargar juegos (legítimos, que hayas comprado) directamente a tu PC.
  * __title.db__: _Una base de datos de los juegos instalados_ - aparte de fines informativos, no tiene mucha más utilidad para la mayoría de usuarios.
  * __import.db__: _Una base de datos con los títulos que van a ser instalados_ - se puede usar para evitar las actualizaciones de la consola; más información en [este tutorial](https://gbatemp.net/threads/poc-removing-update-nag-on-emunand.399460/).  
  * __certs.db__: _A database of certificates_ - any practical use for this is unknown at the moment.
  * __SecureInfo_A__: _This contains your region and an ASCII serial number_ - this can be used to temporarily change your 3DS region. The dump / inject options in Decrypt9 simplify [the tutorial found here](https://gbatemp.net/threads/release-3ds-nand-secureinfo-tool-for-region-change.383792/).
  * __LocalFriendCodeSeed_B__: _contiene tu FriendCodeSeed_ - en teoría, se puede usar para importar tu lista de amigos a otra 3DS.
  * __movable.sed__: _Contine las llaves (_keys_) para el descifrado de datos de la tarjeta SD_ - Decrypt9 usa este archivo en la función 'Descifrar/Cifrar SD' y en '_SD padgen_'. 
  * __seedsave.bin__: _Contiene las semillas (_seeds_) para el descifrado de _seeds_ cifradas en juegos en sisema con una version superior o igual a 9.6x.- En ese archivo solo se incluyen las semillas para los juegos comprados legalmente. [Usa esta herramienta](https://gbatemp.net/threads/download-seedconv-seeddb-bin-generator-for-use-with-decrypt9.392856/) o el script de Python `seeddb_gen.py` para extraer las seeds y pasarlas al archivo `seeddb.bin` (el archivo que puede leer Decrypt9).
  * __nagsave.bin__: _Contine algunos archivos relacionados con las actualizaciones del sistema_ - con este archivo se pueden bloquear las actualizaciones automáticas; lee [esto](https://gbatemp.net/threads/poc-removing-update-nag-on-emunand.399460/page-5#post-5863332) y los mensajes posteriores para obtener más información. 
  * __nnidsave.bin__: _Contiene los datos de tu NNID_ - puede ser usado para restear/eliminar tu NNID del sistema, sin tener que eliminar otros datos; más información [aquí](https://gbatemp.net/threads/download-decrypt9-open-source-decryption-tools-wip.388831/page-89#post-6000951). 
  * __friendsave.bin__: _Contiene tu lista de amigos_ - puede ser usada para hacer una copia de seguridad y restaurar tu lista de amigos junto con el archivot `LocalFriendCodeSeed_B`. Más información [aquí](http://gbatemp.net/threads/download-decrypt9-open-source-decryption-tools-wip.388831/page-167#post-6294331)
* __Inyectar archivo(!)__: Esta opción te permite encriptar e inyectar varios archivos a la SysNAND y EmuNAND. Para más información, comprueba la lista de arriba.
* __Miscelaneo__: This section contains various features that don't fit into any of the other categories.
  * __Copiar aplicacion 'Salud y Seguridad'__: Te permite realizar una copia, descifrada, de esta aplicación. Puedes usar esta copia inyectar aplicaciones en la aplicación de 'Salud y Seguridad'. Más información [aquí](https://gbatemp.net/threads/release-inject-any-app-into-health-safety-o3ds-n3ds-cfw-only.402236/).
  * __Iyectar aplicación 'Salud y Seguridad'(!)__: Se usa para inyectar cualquier aplicación (siempre que tenga un tamaño menor a la aplicación original). Hay varias comprobaciones de seguridad, y es una utilidad muy segura. Aún así, se advirte al usuario del peligro de esta aplicación. Puedes inyectar la aplicación original de 'Salud y Seguridad' (`hs.app`) o una aplicación personalizada con la herramienta [Universal Inject Generator](https://gbatemp.net/threads/release-inject-any-app-into-health-safety-o3ds-n3ds-cfw-only.402236/). Esta opción detecta todas las aplicaciones que se pueden inyectar y deja elegir al usuario.
  * __Actualizar SeedDB__: Usa esto para crear o actualizar el archivo `seeddb.bin` en tu tarjeta SD. Solo se añadirán nuevas semillas (_seeds_), el resto no se modificarán.
  * __NCCH FIRMs Dump__: Usa esta opción para copiar las particiones  NATIVE_FIRM, SAFE_MODE_FIRM, TWL_FIRM y AGB_FIRM. En las N3DS, la sección ARM9 también será descifrada. Esta opción solos sirve para investigar el sistema.
  * __FIRM ARM9 Decryptor__: Usa esta función para descifrar la sección ARM9 en N3DSes. Esta función solo sirve para investigar el sistema.

###  Opciones de descifrado de contenido
Esta categoría incluye todas las funciones que permiten descifrado (y cifrado) de archivos internos y externos. Los archivos son procesados directamente (las versiones encriptadas son sobrescritas por las descifradas y viceversa, así que ten copias de seguridad). La carpeta de juego estándar es `/D9Game/`, pero si no existe, los archivos serán procesados en la carpeta de trabajo estándar (`/Decrypt9/`).

* __Descifrar NCCH/NCSD__: Usa esto para descifrar los archivos NCCH/NCSD de la carpeta. Los archivos con la extensión .3DS y .APP suelen ser archivos NCCH/NCSD. Un descifrado completo de un archivo .3DS se conoce como _cryptofixing_.
 
    **Importante: Depenndiendo del tipo de 3DS, la versión de esta y los archivos que vayas a descifrar, puedes necesitar archivos de llaves (_key files_) y/o el archivo `seeddb.bin`.**
 
* __Cifrar NCCH/NCSD__: Usa esto para (volver a)cifrar los archivos NCCH/NCSD. El cifrado puede realizarse en cualquier 3DS, desde la menor versión del sistema. En algunas 3DS, los archivos `.3DS` necesitan estar encriptados para funcionar.
* __Descifrar CIA (superficial)__: Usa esto para descifrar todos los CIA de la carpeta, se descifrará la capa titlekey de los CIAs. La capa interna NCHH no se descifrará.
* __Descifrar CIA (completo)__: Usa esto para hacer un descifrado completo de todos los CIAs que estén en la carpeta. Este peroceso también descifra la capa interna NCHH. El descifrado de CIAs completo también se conoce como _cryptofixing_.

    **Importante: Depenndiendo del tipo de 3DS, la versión de esta y los archivos que vayas a descifrar, puedes necesitar archivos de llaves (_key files_) y/o el archivo `seeddb.bin`.**

* __Descifrar CIA (solo CXI)__: Hace lo mismo que la función 'Descifrar CIA (completo)', solo que solo descifra en la capa interna NCCH, solo se descifrará el primer contenido CXI. En algunas 3DS, los CIAs completamente descifrados no funcionan, pero si los descifras con esta función, funcionarán.
* __Cifrar CIA (NCCH)__: Usa esto para cifrar los contenedores NCCH dentro de los archivos CIA en la carpeta. La encriptación NCCH es necesaria para, por ejemplo, hacer que los .CIAs sean instalables.
* __Descifrar BOSS__: Usa esto para descifrar [archivos BOSS](http://3dbrew.org/wiki/SpotPass#Content_Container), que se reciben por Spotpass. Esta oppción descifrará todos los archivos BOSS cifrados (y con un _BOSS Header_ válido) encontrados en la carpeta.
* __Cifrar BOSS__: Usa esto para cifrar [archivos BOSS](http://3dbrew.org/wiki/SpotPass#Content_Container). Esta opción cifrará todos los archivos BOSS descifrados (y con un _BOSS Header_ válido) encontrados en la carpeta.
* __Descifrar/Cifrar SD__: Usa esto para descifrar 'archivos SD'. Los archivos SD son los títulos, archivos extdata y bases de datos encontrados en la carpeta `/Nintendo 3DS/<id0>/<id1>/`. Para que esta opción funciones, tienes que transferir manualmente lo que haya dentro de la carpeta `/Nintendo 3DS/<id0>/<id1>/` a la carpeta de juego/trabajo. Esta opción solo se debería usar para encriptar, ya que para realizar el trabajo de descifrado, es mucho más fácil las dos opciones que se muestran más abjo.
* __Descifrar SD (directorio de la SysNAND)__: Una versión mejorada de la opción mencionada arriba. Permite sleeccionar el contenido de la carpeta `/Nintendo 3DS`/ (la que pertenece a la SysNAND) que será directamente copiada a la carpeta de juego/trabajo.

* __Descifrar SD (directorio de la EmuNAND)__: Hace la mismo que la opción de arriba, solo que usa la carpeta `/Nintendo 3DSp que pertenece a la EmuNAND.

### Opciones de copia de cartuchos
Esta categoría incluye todas las opciones relacionadas con la copia de cartuchos. Los cartuchos se extraen en formato `.3DS`.
* __Copiar cartucho (completo)__: Esta opción copia todo el cartucho, sin modificar nada en este. Para cartuchos de 4GB, el último sector se descarta, porque el sistema de archivos FAT32 no puede soportar la transferencia de archivos de más de 4GB.
* __Copiar cartucho (superficial)__: Hace lo msimo que la opción mencionada más arriba, solo que descarta los archivos 'basura' del cartucho, así puedes ahorrar espacio al acortar el tamaño.
* __Copiar y descifrar cartucho (completo)__: Hace lo mismo que la opción 'Copiar cartucho (completo)', pero descifra el cartucho directamente. Un cartucho descifrado se requiere para emuladores y convertir de `.3DS` a `.CIA`; se recomienda usar la herramienta [3dsconv](https://github.com/ihaveamac/3dsconv) para realizar tal conversión.
* __Copiar y descifrar cartucho (ligero)__: Hace lo msimo que la anteriro opcion, solo que descarta los archivos innecesarios; así obtienes un archivo `.3DS` más ligero.
* **Copiar header privado (_private header_)** : Copia el _private header_ único del cartucho insertado.

### Opciones de mantenimiento
Esta categoría incluye todas las funciones especiual que te permiten testear y controlar la funcionalidad interna de Decrypt9
* __System Info__: Muestra al usuaio informaócin sobre la 3DS y la SD. Se usa está función con fines informativos y para probar si la información está disponible.
* __Crear _Selftest Reference___: Ejecuta esto para generar el _Selftest Reference_, esta opción creará un archivo llamado `d9_selftest.ref` en la raíz de la sd o en la carpeta de trabajo.
* __Ejecutar Selftest__: Ejecuta el _selftest_ (los datos de referencia deben ser creados previamente). Esto creará y actualizará un archivo llamado `d9_selftest.lst` en tu SD. Nota: en O3DS que los tests `ncch_sec3_key`, `ncch_sec4_key` y `ǹand_ctrn_key` fallen, es normal. En 03DS con una versión de la consola igual o menor a 7.0. el test `ncch_7x_key` puede fallar. En N3DS y O3DS el test `ncch_sec4_key` puede fallar (si usas los archivos de ayuda, no debería fallar ningún test).
* __Crear Key Database__: Esto se usa para crear el archivo `askeydb.bin` de los archivos disponibles `slot0x??key?.bin` (es decir, los que tengas en la SD).
* __Descifrar/Cifrar Key Database__: Por defecto, el archivo `aeskeydb.bin` creado en Decrypt9, está cifrado, así que las claves no se pueden visualizar con un editor hexadecimal. Usa esto para descifrar un archivo `askeydb.bin` cifrado o viceversa. Recuerda que Decrypy9 puede leer las llaves (_keys_) de las dos formas.

## Licencia
You may use this under the terms of the GNU General Public License GPL v2 or under the terms of any later revisions of the GPL. Refer to the provided `LICENSE.txt` file for further information. 

Este programa está sujeto a la GPL v2 o a las revisiones de esta, puedes leer en español la licencia leyendo el archivo `LICENCIA DE USO.txt`.

## Créditos de Archshift
* Roxas75 por el método de la inyección de código ARM9
* Cha(N), Kane49, y todos los que contribuyes al FatFS
* Normmatt por el archivo `sdmmc.c` y la infraestructura del proyecto (_Makefile, linker setup, etc_)
* Relys, sbJFn5r por el programa de descifrado.

## Créditos de d0k3
* Todo el mundo mencionado por Archshift más arriba.
* Archshift por empezar este proyecto y por mantener tan bien el proyecto.
* b1l1s, Normmatt por su trabajo 'detrás de las cámaras' y por hacer posible la integración con A9LH.
* patois, delebile, SteveIce10 por Brahma y sus actualizaciones.
* mid-kid por CakeHax y por publicar y mantener freenode #Cakey
* Shadowtrance, dark_samus3, Syphurith, AuroraWright por ser de gran ayuda al desarrollar esto.
* profi200 por sus útiles pistas que hicieron que algunas funcionalidades fueran posibles.
* Datalogger, zoogie, atkfromabove, mixups, key1340, k8099, Al3x_10m, Supster131, stbinan, Wolfvak, Gelex y un montón más de gente de freenode #Cakey y de los foros de GBAtemp por testear la aplicación, su _feedback_ y sus útiles pistas.
* Todo el mundo que me he olvidado poner aquí.
