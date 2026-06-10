/*---------------------------------------------------------------------
**
**  Fichero:
**    fun_asm.asm  19/10/2022
**
**    (c) Daniel Báscones García
**    Fundamentos de Computadores II
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Fichero de código para la práctica 4_lab
**
**-------------------------------------------------------------------*/
/*---------------------------------------------------------------------
**
**  Fichero:
**    fun_asm.c  19/10/2022
**
**    (c) Daniel Báscones García
**    Fundamentos de Computadores II
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Fichero de código para la práctica 4
**
**-------------------------------------------------------------------*/


//rellenar con directivas .extern y .global
//con las funciones apropiadas

/*
int eucl_dist(int w [], int size) {
	int acc = 0;
	for (int i = 0; i < size; i++) {
		acc += mul(w[i], w[i]);
	}
	return i_sqrt(acc);
}
*/
.global eucl_dist
.global vector_resultado

.extern mul
.extern i_sqrt
.extern cargar

eucl_dist:
	//Apilamos
	addi sp, sp, -24
	sw s1, 20(sp)
	sw s2, 16(sp)
	sw s3, 12(sp)
	sw s4, 8(sp)
	sw s5, 4(sp)
	sw ra, 0(sp)
    //recibo dirección de W en a0, y tamaño N en a1
    li s1, 0 // int acc = 0
    li s2, 0 // int i = 0
    mv s3, a0 // s3 = dirección de W
    mv s4, a1 // s4 = tamaño N
    bucle_eucl:
    bge s2, s4, fin_bucle_eucl //i >= N fin
    slli t0, s2, 2 // t0 = i * 4
    add t0, t0, s3 // t0 = i*4 + dir. W = direccion W[i]
    lw a0, 0(t0) // primer argumento int a de mul
    lw a1, 0(t0) // segundo argumento int b de mul
    call mul //int mul (int a, int b), devuelve resultado en a0
    add s1, s1, a0 //acc += mul(w[i], w[i])
    addi s2, s2, 1 //i += i
    j bucle_eucl
    fin_bucle_eucl:
    mv a0, s1 //Cargamos acc como primer argumento de i_sqrt
    call i_sqrt //El resultado se guarda en a0 por defecto
    //Desapilamos
	lw s1, 20(sp)
	lw s2, 16(sp)
	lw s3, 12(sp)
	lw s4, 8(sp)
	lw s5, 4(sp)
	lw ra, 0(sp)
    addi sp, sp, 24
    ret

vector_resultado:
	//Apilamos
	addi sp, sp, -32
	sw s1, 28(sp) //puntero *vector
	sw s2, 24(sp) //puntero *resultado
	sw s3, 20(sp) //mayor_dist
	sw s4, 16(sp) //size
	sw s5, 12(sp) //valor
	sw s6, 8(sp) //acc
	sw s7, 4(sp) // int i
	sw ra, 0(sp)
	mv s1, a0
	mv s2, a1
	mv s3, a2
	mv s4, a3
	li s7, 0
	for:
	bge s7, s4, fin_bucle
	mv a0, s1
	mv a1, s7
	call cargar
	mv s5, a0

	mv a0, s5
	mv a1, s3
	call mul
	mv s6, a0

	mv a0, s2
	mv a1, s6
	mv a2, s7
	call guardar
	addi s7, s7, 1
	j for
	fin_bucle:
	lw s1, 28(sp) //puntero *vector
	lw s2, 24(sp) //puntero *resultado
	lw s3, 20(sp) //mayor_dist
	lw s4, 16(sp) //size
	lw s5, 12(sp) //valor
	lw s6, 8(sp) //acc
	lw s7, 4(sp) // int i
	lw ra, 0(sp)
	addi sp, sp, 32

    ret
/*
void guardar(char valor, char * ubicación) {
	*ubicación = valor;
}
*/
