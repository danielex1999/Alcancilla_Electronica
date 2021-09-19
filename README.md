# Alcancilla Electronica
Trabajo realizado en el programa "Arduino"

Los 2 plomos son para prender la maquina, comprenle una especie de tapa, y ajustenlos ahi. No lo olviden uno es + y el
otro es -, no confundirse, la misma tapa dira donde debe ir cada uno, el profe sabe como se llama

una vez con la tapa/adaptador, lo conectan al cargador, ya con eso enchufado funciona la maquina

Hay una moneda base, que sirve de referencia, si hay problemas saquenla y vuelvan a meterla (la
cosa esa que la sujeta, se dezlia horisontalmente para una sola direccion, no requiere mucha
fuerza, encuentren el angulo correcto)

sí acepta monedas de colección, se guia por peso y tamaño

El cable blanco es el cable coin, envia señales. Eso coloquenlo en un pin del arduino (tipo como un led)
sera el que envie la señal de que aumente +1 a la variable que cuenta monedas

El rojo y negro, la verdad no sé si se utilizan. Osea receurdo 2 situaciones
(1) unan ambos a los pines del coin switch, prueben con cual cada uno, si funciona el cable blanco
transmite la señal y cuenta por cada moneda que pasa.

Exacto, jalar del ala,bre para probar no activa la señal coin, si quieren probar necesariamente
debe (1) el apartao estar parado y encendido. (2) pasar la menda

bueno en la segunda seituación, fue que creo que a ultimo momento me di cuenta que la maquina trae un coin
switch interno incorporado, en ese caso el cable rojo y negro, asi como ese alambre ya no sirven

Y bastaria con conectar el cable blanco a un numero del arduino nomas.

PD: no metan monedas pequeñas (10 centimos) estando apagado, porque se pueden quedar trabadas y no se destrabaran
hasta que la maquina se prenda.

SOBRE EL CODIGO

MIREN HAY UN ERROR que no logre solucionar, no spe que debe ocurrir para ocurrir. La variable que cuenta
las monedas deberia empezar con 0 obviamente.

pero ha veces ocurre algo uqe no sé como ocurre, que hace que la al resetear el codigo (osea presionando
el boton), la variable en vez de volver a 0, se queda en 1. Manualmente habra que desconcetar, apagar y prender
para arreglar. O restenle -1 a la variable del codigo, asi se soluciona sin desconcetar o hacer un rest fuerte.
Pero cuando lo vallan a poner en marcha otra vez volvera a 0 y pues, como le restaron uno, aparecera negativo.
Asi que cuidado con el codigo.

(el error puede empeorar, y seguir aumentando en 1, haciendo que la variable de inicio sea 2 o 3 o 4 en vez de 0)
