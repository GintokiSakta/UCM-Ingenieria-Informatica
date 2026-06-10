/*---------------------------------------------------------------------
**
**  Fichero:
**    pr2_lab.asm  19/10/2022
**
**    (c) Daniel Báscones García
**    Fundamentos de Computadores II
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Fichero de código para la práctica 2_lab
**
**  Notas de diseño:
**
**-------------------------------------------------------------------*/
.global main
.equ N , 4
.equ INT_MAX , 65536

.data
V: 	 .word 21, -5, 3, -10
.bss
W: 	 .space N * 4
X:   .space N * 4
min: .space 4
ind: .space 4

.text
main :
    la s1, V  //Guardo dirección base de V en s1
    la s2, W  //Guardo dirección base de W en s2
    la s3, X  //Guardo dirección base de X en s3
    la s4, ind
    la s5, min

//Apartado A (revisado por profesor), calcula W
	li t1, N-1 //t1 = i
for:
	bltz t1, partb //Si i < 0 termina el bucle
	slli t2, t1, 2 //t2 ahora es igual a "t1*2"
	add t2, s1, t2 //t2 contiene "s2 + t1*2", justo la dirección buscada, V[i]
	lw t3, 0(t2) //cargo en t3 el valor de V[i]
	slli t2, t1, 2 // Simétrico de V
	add t2, s2, t2 // Simétrico de V
	lw t4, 0(t2) //Simétrico de V, t4 = W[i]
	add t4, t3, t1 //W[i] = V[i] + i
	sw t4, 0(t2) //Guardamos W[i] en su dirección de memoria
	addi t1, t1, -1 //Restamos i -= 1 y repetimos bucle
	j for

partb:
//Apartado B, calcula X, V[index] > W[index]; W[j] > X[j] (no revisado por profesor, no funciona bien)
	li t0, 0 //t0 = j
	li t1, 0 //t1 = i
	li t6, N //t6 = N
forj:
	bge t0, t6, fin //Si j >= N termina el bucle
	li t5, INT_MAX  //t5 = INT_MAX
	sw t5, 0(s5)    //min = t5
	fori:
		bge t1, t6, fini
		slli t2, t1, 2 //t2 ahora es igual a "t1*2"
		add t2, s2, t2 //t2 contiene "s2 + t1*2", justo la dirección buscada, V[i]
		lw t4, 0(t2) //cargo en t4 = V[i]
		addi t1, t1, 1 //Sumamos i += 1
		if:
			bgt t4, t5, fori //Si V[i] > min no se guarda nuevo mínimo
			mv t5, t4  //Guardamos el nuevo mínimo
			sw t5, 0(s5)  //Guardamos en la memoria el valor nuevo de min
			addi t1, t1, -1 //Restamos 1 a i, hemos sumado antes de entrar
			sw t1, 0(s4)  //Guardamos en memoria index = i-1
			addi t1, t1, 1 //Devolvemos el 1, i = i - 1 + 1, antes de volver al bucle
			j fori //Repetimos bucle i
	fini:
	slli t2, t0, 2  // t2 = j (t0) * 2
	add t2, s3, t2  // t2 = t2 + s3 (direcciones de memoria) > t2 = W[j] (dir. memoria)
	lw t4, 0(t2) // t4 = W[j]
	lw t5, 0(s4) // t5 = index
	slli t5, t5, 2 // t5 = direccion de index*2
	add t5, s2, t5  // t5 = direccion de V[index]
	lw t3, 0(t5)  // t3 = V[index]

	li t1, -5
	blt t3, t1, noguardar
	li t1, 20
	bgt t3, t1, noguardar

	mv t4, t3    //W[j] = V[index]
	sw t4, 0(t2) //Guardamos en memoria W[j] (en direccion W[j])
	noguardar:
	li t3, INT_MAX //V[index] = INT_MAX
	sw t3, 0(t5) // Guardamos en memoria V[index] = INT_MAX

	addi t0, t0, 1  //Sumamos j += 1
	li t1, 0  //Reiniciamos el contador del bucle i
	j forj  //Repetimos bucle j
fin:                //fin del programa
    j fin           //salto sobre sí mismo, parando el programa
.end
