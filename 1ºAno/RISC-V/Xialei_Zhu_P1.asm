/*---------------------------------------------------------------------
**
**  Fichero:
**    pr1_lab.asm  19/10/2022
**
**    (c) Daniel Báscones García
**    Fundamentos de Computadores II
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Fichero de código para la práctica 1_lab
**
**  Notas de diseño:

**	# define N 10
**	int res = 0;
**	for (int i = 0; i < N ; i ++) {
**		res += i ;
**	}
**-------------------------------------------------------------------*/
.equ N, 9
.data
    res:      .word 0
.bss

.text
.global main
main:
    la t0, res      //Guardar la dirección de la variable en t0
    lw t1, 0(t0)    //Cargar su valor en t1
    li t6, N		//Usamos t6 para comparar (N)
    li t5, -5	//Usamos t5 para comparar (i)
    for:
    bge t5, t6, fin		//Si t5 (i) > t6 (N) entonces termina el bucle
    andi t3, t5, 1		//Máscara, compara a un bit (1) t5 y lo guarda en t3
    bgt t3, zero, if	//Si t3 > 0, es impar, salta y no suma res = res + i
    add t1, t1, t5		//Sumamos res = res + i
    if:
    addi t5, t5, 1		//Sumamos i++
    sw t1, 0(t0)      	//Guardamos t1 en su dirección de memoria original t0
    j for             	//Volvimos al inicio del bucle, debe terminar en res == 45

fin:                //fin del programa
    j fin           //salto sobre sí mismo, parando el programa
.end
