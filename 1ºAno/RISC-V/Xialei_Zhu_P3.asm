.extern _stack
.global main
.equ N, 6
.equ e, 2
.equ f, 4

.data
A: .word 3, 5, -1, 9, 7, 4
B: .word 1, -6, 2, 3, 5, 8

.bss
resultado: .space 4

.text
.global main

comparacion:
    addi sp, sp, -28  //reservamos 6*4 bytes de memoria en pila
    sw ra, 24(sp) //Guardamos la dirección de retorno
    sw s0, 20(sp) //Guardamos dir normA
    sw s1, 16(sp) //Guardamos dir normB
    sw s2, 12(sp) //Guardamos valor original 0
    sw s3, 8(sp) //Guardamos valor original 0
    sw s4, 4(sp) //Guardamos valor original 0
    sw s5, 0(sp) //Guardamos valor original 0

//Calculamos normA = dotprodmodif(A, A, N,e)
    la a0, A //a0 = dir puntero A
    la a1, A //a1 = dir puntero A = a0
    li a2, N //a2 = N
    li a3, e
    call dotprodmodif
    mv s0, a0 //Vuelta del dotprodmodif, guardamos normA = a0 = s0

    //Calculamos normB = dotprodmodif(B, B, N,f); copia pega de normA
    la a0, B //a0 será argumento de retorno
    la a1, B //a1 = dir puntero B = a0
    li a2, N  //a2 = N
    li a3, f
    call dotprodmodif
    mv s1, a0 //Vuelta del dotprodmodif, guardamos normB = a0 = s1


    la t1, resultado
    neg s1, s1
    add t0, s0, s1
    sw t0, 0(t1) //Guardamos t0 en res, ya sea 0xa o 0xb
		//desapilamos
    	lw ra, 24(sp)
	    lw s0, 20(sp)
	    lw s1, 16(sp)
	    lw s2, 14(sp)
	    lw s3, 8(sp)
	    lw s4, 4(sp)
	    sw s5, 0(sp) //Guardamos valor original 0
	    addi sp, sp, 28 //-24 + 24 = 0, la pila vuelve a su techo
	    ret //Volvemos a main (hemos restaurado ra)

mul:
    li t0, 0 //int res (local, no la variable global) = t0 = 0

	bucle_mul: //bucle while, calcula res = a + a + a... b veces
		bgez a1, positivo //Checamos si es positivo o negativo b
		neg a1, a1 //Si es negativo le cambiamos el signo
		positivo: //Si es >= a 0 entonces no cambiamos signo
	    ble a1, zero, fin_mul //Si W[i] (b) <= 0 termina el bucle
	    add t0, t0, a0 //res (t0) += V[i]
	    addi a1, a1, -1 //W[i] -= 1
	    j bucle_mul

	fin_mul:
	    mv a0, t0 //Guardamos res en a0 (registro argumento retorno)
	    ret //Volvemos a dotprodmodif

dotprodmodif: //Size = N
    addi sp, sp, -28  //reservamos 6*4 bytes de memoria en pila
    sw ra, 24(sp) //Guardamos la dirección de retorno
    sw s0, 20(sp) //Guardamos dir normA
    sw s1, 16(sp) //Guardamos dir normB
    sw s2, 12(sp) //Guardamos valor original 0
    sw s3, 8(sp) //Guardamos valor original 0
    sw s4, 4(sp) //Guardamos valor original 0
    sw s5, 0(sp) //Guardamos valor original 0

    li s0, 0 //Inicializamos s0 = acc = 0
    li s1, 0 //Inicializamos s1 = int i = 0
    mv s2, a0 //Guardamos en s2 dir puntero A
    mv s3, a1 //Guardamos en s3 dir puntero A
    mv s4, a2 //Guardamos en s4 la constante N
    mv s5, a3

	bucle_dotprodmodif: //Bucle for
	    bge s1, s4, fin_dotprodmodif //Si i > N se termmina bucle
	    slli t0, s1, 2 //Multiplicamos i * 4, para normalizarla a la dirección del array, t0
	    add t1, s2, t0 //t1 = dir V[i] (A[i])
	    lw a0, 0(t1) //a0 = V[i]
	    add t2, s3, t0 //t2 = dir W[i] (A[i])
	    lw a1, 0(t2) //a1 = W[i] (A[i])
	    call mul
	    add a1, a1, a0 //Volvemos de mul, guardamos el retorno (a0) en acc (s0) acc = return res
	    mv a0, s5
	    call mul
	    add s0, s0, a0 //Volvemos de mul, guardamos el retorno (a0) en acc (s0) acc = return res
	    addi s1, s1, 1 //i += 1
	    j bucle_dotprodmodif

	fin_dotprodmodif:
	    mv a0, s0 //Guardamos acc (s0) en a0, registro retorno para main
	    //Desacoplamos la pila
	    lw ra, 24(sp)
	    lw s0, 20(sp)
	    lw s1, 16(sp)
	    lw s2, 14(sp)
	    lw s3, 8(sp)
	    lw s4, 4(sp)
	    sw s5, 0(sp) //Guardamos valor original 0
	    addi sp, sp, 28 //-24 + 24 = 0, la pila vuelve a su techo
	    ret //Volvemos a main (hemos restaurado ra)

main:
	la sp, _stack
	call comparacion
    j fin

fin:
    j fin
.end
