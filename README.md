
- echo $?: tendria que devolver el output del ultimo comando. No puede expandir del env, tiene que guardar la variable con valor del ultimo comando.
- (ARLEY)si comillas no bien puestas (si no cierran) tiene que mandar error. No salir del ourShell. Aqui no hay que replicar exactamente lo que hace bash.
- (ARLEY)$$
- signales
- Actualizar e env SHLVL cada vez que executamos.
- leaks
- grand probabilidad de tener algun fichero abierto...
- garantizar que top no da seg. fault (despues de tener los signales)
